# otisserv - Copyright (c) 2019-, Rick Lan, dragonpilot community, and a number of other of contributors.
# Fleet Manager - [actuallylemoncurd](https://github.com/actuallylemoncurd), [AlexandreSato](https://github.com/alexandreSato), [ntegan1](https://github.com/ntegan1), [royjr](https://github.com/royjr), and [sunnyhaibin] (https://github.com/sunnypilot)
# Almost everything else - ChatGPT
# dirty PR pusher - mike8643
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
import base64
import json
import math
import os
import requests
import subprocess
import traceback

import openpilot.system.sentry as sentry

from datetime import datetime
from pathlib import Path
from typing import List
from urllib.parse import quote

from openpilot.common.params import ParamKeyType
from openpilot.selfdrive.car.toyota.carcontroller import LOCK_CMD, UNLOCK_CMD
from openpilot.system.hardware import HARDWARE, PC
from openpilot.system.hardware.hw import Paths
from openpilot.system.loggerd.uploader import listdir_by_creation
from openpilot.system.loggerd.xattr_cache import getxattr
from panda import Panda
from tools.lib.route import SegmentName

from openpilot.selfdrive.frogpilot.frogpilot_variables import ERROR_LOGS_PATH, EXCLUDED_KEYS, frogpilot_default_params, params, update_frogpilot_toggles

XOR_KEY = "s8#pL3*Xj!aZ@dWq"

pi = 3.1415926535897932384626
x_pi = 3.14159265358979324 * 3000.0 / 180.0
a = 6378245.0
ee = 0.00669342162296594323

PRESERVE_ATTR_NAME = 'user.preserve'
PRESERVE_ATTR_VALUE = b'1'
PRESERVE_COUNT = 5


# path to openpilot screen recordings and error logs
if PC:
  SCREENRECORD_PATH = os.path.join(str(Path.home()), ".comma", "media", "screen_recordings", "")
  ERROR_LOGS_PATH = os.path.join(str(Path.home()), ".comma", "error_logs", "")
  TMUX_LOGS_PATH = os.path.join(str(Path.home()), ".comma", "tmux_logs")
else:
  SCREENRECORD_PATH = "/data/media/screen_recordings/"
  ERROR_LOGS_PATH = ERROR_LOGS_PATH
  TMUX_LOGS_PATH = "/data/tmux_logs/"


def list_files(path): # still used for footage
  return sorted(listdir_by_creation(path), reverse=True)


def list_file(path): # new function for screenrecords/error-logs
  if os.path.exists(path):
    files = os.listdir(path)
    sorted_files = sorted(files, reverse=True)
  else:
    return []  # Return an empty list if there are no files or directory
  return sorted_files


def is_valid_segment(segment):
  try:
    segment_to_segment_name(Paths.log_root(), segment)
    return True
  except AssertionError:
    return False


def segment_to_segment_name(data_dir, segment):
  fake_dongle = "ffffffffffffffff"
  return SegmentName(str(os.path.join(data_dir, fake_dongle + "|" + segment)))


def all_segment_names():
  segments = []
  for segment in listdir_by_creation(Paths.log_root()):
    try:
      segments.append(segment_to_segment_name(Paths.log_root(), segment))
    except AssertionError:
      pass
  return segments


def all_routes():
  segment_names = all_segment_names()
  route_names = [segment_name.route_name for segment_name in segment_names]
  route_times = [route_name.time_str for route_name in route_names]
  unique_routes = list(dict.fromkeys(route_times))
  return sorted(unique_routes, reverse=True)

def preserved_routes():
  dirs = listdir_by_creation(Paths.log_root())
  preserved_segments = get_preserved_segments(dirs)
  return sorted(preserved_segments, reverse=True)

def has_preserve_xattr(d: str) -> bool:
  return getxattr(os.path.join(Paths.log_root(), d), PRESERVE_ATTR_NAME) == PRESERVE_ATTR_VALUE

def get_preserved_segments(dirs_by_creation: List[str]) -> List[str]:
  preserved = []
  for n, d in enumerate(filter(has_preserve_xattr, reversed(dirs_by_creation))):
    if n == PRESERVE_COUNT:
      break
    date_str, _, seg_str = d.rpartition("--")

    # ignore non-segment directories
    if not date_str:
      continue
    try:
      seg_num = int(seg_str)
    except ValueError:
      continue
    # preserve segment and its prior
    preserved.append(d)

  return preserved

def video_to_gif(input_path, output_path, fps=1, duration=6): # not used right now but can if want longer animated gif
  if os.path.exists(output_path):
    return
  command = [
    'ffmpeg', '-y', '-i', input_path,
    '-filter_complex',
    f'fps={fps},scale=240:-1:flags=lanczos,setpts=0.1*PTS,split[s0][s1];[s0]palettegen=max_colors=32[p];[s1][p]paletteuse=dither=bayer',
    '-t', str(duration), output_path
  ]
  subprocess.run(command)
  print(f"GIF file created: {output_path}")

def video_to_img(input_path, output_path, fps=1, duration=6):
  if os.path.exists(output_path):
    return
  subprocess.run(['ffmpeg', '-y', '-i', input_path, '-ss', '5', '-vframes', '1', output_path])
  print(f"GIF file created: {output_path}")

def segments_in_route(route):
  segment_names = [segment_name for segment_name in all_segment_names() if segment_name.time_str == route]
  segments = [segment_name.time_str + "--" + str(segment_name.segment_num) for segment_name in segment_names]
  return segments


def ffmpeg_mp4_concat_wrap_process_builder(file_list, cameratype, chunk_size=1024*512):
  command_line = ["ffmpeg"]
  if not cameratype == "qcamera":
    command_line += ["-f", "hevc"]
  command_line += ["-r", "20"]
  command_line += ["-i", "concat:" + file_list]
  command_line += ["-c", "copy"]
  command_line += ["-map", "0"]
  if not cameratype == "qcamera":
    command_line += ["-vtag", "hvc1"]
  command_line += ["-f", "mp4"]
  command_line += ["-movflags", "empty_moov"]
  command_line += ["-"]
  return subprocess.Popen(
    command_line, stdout=subprocess.PIPE,
    bufsize=chunk_size
  )


def ffmpeg_mp4_wrap_process_builder(filename):
  """Returns a process that will wrap the given filename
     inside a mp4 container, for easier playback by browsers
     and other devices. Primary use case is streaming segment videos
     to the vidserver tool.
     filename is expected to be a pathname to one of the following
       /path/to/a/qcamera.ts
       /path/to/a/dcamera.hevc
       /path/to/a/ecamera.hevc
       /path/to/a/fcamera.hevc
  """
  basename = filename.rsplit("/")[-1]
  extension = basename.rsplit(".")[-1]
  command_line = ["ffmpeg"]
  if extension == "hevc":
    command_line += ["-f", "hevc"]
  command_line += ["-r", "20"]
  command_line += ["-i", filename]
  command_line += ["-c", "copy"]
  command_line += ["-map", "0"]
  if extension == "hevc":
    command_line += ["-vtag", "hvc1"]
  command_line += ["-f", "mp4"]
  command_line += ["-movflags", "empty_moov"]
  command_line += ["-"]
  return subprocess.Popen(
    command_line, stdout=subprocess.PIPE
  )


def ffplay_mp4_wrap_process_builder(file_name):
  command_line = ["ffmpeg"]
  command_line += ["-i", file_name]
  command_line += ["-c", "copy"]
  command_line += ["-map", "0"]
  command_line += ["-f", "mp4"]
  command_line += ["-movflags", "empty_moov"]
  command_line += ["-"]
  return subprocess.Popen(
    command_line, stdout=subprocess.PIPE
  )

def get_nav_active():
  if params.get("NavDestination", encoding='utf8') is not None:
    return True
  else:
    return False

def get_amap_key():
  token = params.get("AMapKey1", encoding='utf8')
  token2 = params.get("AMapKey2", encoding='utf8')
  return (token.strip() if token else None, token2.strip() if token2 else None)

def get_gmap_key():
  token = params.get("GMapKey", encoding='utf8')
  return token.strip() if token else None

def get_public_token():
  token = params.get("MapboxPublicKey", encoding='utf8')
  return token.strip() if token and token.startswith("pk") else None

def get_secret_token():
  token = params.get("MapboxSecretKey", encoding='utf8')
  return token.strip() if token and token.startswith("sk") else None

def get_search_input():
  return params.get_int("SearchInput")

def get_last_lon_lat():
  last_pos = params.get("LastGPSPosition")
  if last_pos:
    l = json.loads(last_pos)
  else:
    return 0.0, 0.0
  return l["longitude"], l["latitude"]

def get_locations():
  data = params.get("ApiCache_NavDestinations", encoding='utf-8')
  return data

def preload_favs():
  try:
    nav_destinations = json.loads(params.get("ApiCache_NavDestinations", encoding='utf8') or "{}")
  except TypeError:
    return (None, None, None, None, None)

  locations = {"home": None, "work": None, "fav1": None, "fav2": None, "fav3": None}

  for item in nav_destinations:
    label = item.get("label")
    if label in locations and locations[label] is None:
      locations[label] = item.get("place_name")

  return tuple(locations.values())

def parse_addr(postvars, lon, lat, valid_addr, token):
  addr = postvars.get("fav_val", [""])
  real_addr = None
  if addr != "favorites":
    try:
      dests = json.loads(params.get("ApiCache_NavDestinations", encoding='utf8') or "{}")
    except TypeError:
      dests = json.loads("[]")
    for item in dests:
      if "label" in item and item["label"] == addr:
        lat, lon, real_addr = item["latitude"], item["longitude"], item["place_name"]
        break
  return (real_addr, lon, lat, real_addr is not None, token)

def search_addr(postvars, lon, lat, valid_addr, token):
  if "addr_val" in postvars:
    addr = postvars.get("addr_val")
    if addr != "":
      # Properly encode the address to handle spaces
      addr_encoded = quote(addr)
      query = f"https://api.mapbox.com/geocoding/v5/mapbox.places/{addr_encoded}.json?access_token={token}&limit=1"
      # focus on place around last gps position
      lngi, lati = get_last_lon_lat()
      query += "&proximity=%s,%s" % (lngi, lati)
      r = requests.get(query)
      if r.status_code != 200:
        return (addr, lon, lat, valid_addr, token)
      j = json.loads(r.text)
      if not j["features"]:
        return (addr, lon, lat, valid_addr, token)
      lon, lat = j["features"][0]["geometry"]["coordinates"]
      valid_addr = True
  return (addr, lon, lat, valid_addr, token)

def set_destination(postvars, valid_addr):
  if postvars.get("latitude") is not None and postvars.get("longitude") is not None:
    postvars["lat"] = postvars.get("latitude")
    postvars["lon"] = postvars.get("longitude")
    postvars["save_type"] = "recent"
    nav_confirmed(postvars)
    valid_addr = True
  else:
    addr = postvars.get("place_name")
    token = get_public_token()
    data, lon, lat, valid_addr, token = search_addr(addr, lon, lat, valid_addr, token)
    postvars["lat"] = lat
    postvars["lon"] = lon
    postvars["save_type"] = "recent"
    nav_confirmed(postvars)
    valid_addr= True
  return postvars, valid_addr

def nav_confirmed(postvars):
  if postvars is not None:
    lat = float(postvars.get("lat"))
    lng = float(postvars.get("lon"))
    save_type = postvars.get("save_type")
    name = postvars.get("name") if postvars.get("name") is not None else ""
    if params.get_int("SearchInput") == 1:
      lng, lat = gcj02towgs84(lng, lat)
    params.put("NavDestination", "{\"latitude\": %f, \"longitude\": %f, \"place_name\": \"%s\"}" % (lat, lng, name))
    if name == "":
      name =  str(lat) + "," + str(lng)
    new_dest = {"latitude": float(lat), "longitude": float(lng), "place_name": name}
    if save_type == "recent":
      new_dest["save_type"] = "recent"
    else:
      new_dest["save_type"] = "favorite"
      new_dest["label"] = save_type
    val = params.get("ApiCache_NavDestinations", encoding='utf8')
    if val is not None:
      val = val.rstrip('\x00')
    dests = [] if val is None else json.loads(val)
    # type idx
    type_label_ids = {"home": None, "work": None, "fav1": None, "fav2": None, "fav3": None, "recent": []}
    idx = 0
    for d in dests:
      if d["save_type"] == "favorite":
        type_label_ids[d["label"]] = idx
      else:
        type_label_ids["recent"].append(idx)
      idx += 1
    if save_type == "recent":
      id = None
      if len(type_label_ids["recent"]) > 10:
        dests.pop(type_label_ids["recent"][-1])
    else:
      id = type_label_ids[save_type]
    if id is None:
      dests.insert(0, new_dest)
    else:
      dests[id] = new_dest
    params.put("ApiCache_NavDestinations", json.dumps(dests).rstrip("\n\r"))

def public_token_input(postvars):
  if postvars is None or "pk_token_val" not in postvars or postvars.get("pk_token_val")[0] == "":
    return postvars
  else:
    token = postvars.get("pk_token_val").strip()
    if "pk." not in token:
      return postvars
    else:
        params.put("MapboxPublicKey", token)
  return token

def app_token_input(postvars):
  if postvars is None or "sk_token_val" not in postvars or postvars.get("sk_token_val")[0] == "":
    return postvars
  else:
    token = postvars.get("sk_token_val").strip()
    if "sk." not in token:
      return postvars
    else:
        params.put("MapboxSecretKey", token)
  return token

def gmap_key_input(postvars):
  if postvars is None or "gmap_key_val" not in postvars or postvars.get("gmap_key_val")[0] == "":
    return postvars
  else:
    token = postvars.get("gmap_key_val").strip()
    params.put("GMapKey", token)
  return token

def amap_key_input(postvars):
  if postvars is None or "amap_key_val" not in postvars or postvars.get("amap_key_val")[0] == "":
    return postvars
  else:
    token = postvars.get("amap_key_val").strip()
    token2 = postvars.get("amap_key_val_2").strip()
    params.put("AMapKey1", token)
    params.put("AMapKey2", token2)
  return token

def gcj02towgs84(lng, lat):
  dlat = transform_lat(lng - 105.0, lat - 35.0)
  dlng = transform_lng(lng - 105.0, lat - 35.0)
  radlat = lat / 180.0 * pi
  magic = math.sin(radlat)
  magic = 1 - ee * magic * magic
  sqrtmagic = math.sqrt(magic)
  dlat = (dlat * 180.0) / ((a * (1 - ee)) / (magic * sqrtmagic) * pi)
  dlng = (dlng * 180.0) / (a / sqrtmagic * math.cos(radlat) * pi)
  mglat = lat + dlat
  mglng = lng + dlng
  return [lng * 2 - mglng, lat * 2 - mglat]

def transform_lat(lng, lat):
  ret = -100.0 + 2.0 * lng + 3.0 * lat + 0.2 * lat * lat + 0.1 * lng * lat + 0.2 * math.sqrt(abs(lng))
  ret += (20.0 * math.sin(6.0 * lng * pi) + 20.0 * math.sin(2.0 * lng * pi)) * 2.0 / 3.0
  ret += (20.0 * math.sin(lat * pi) + 40.0 * math.sin(lat / 3.0 * pi)) * 2.0 / 3.0
  ret += (160.0 * math.sin(lat / 12.0 * pi) + 320 * math.sin(lat * pi / 30.0)) * 2.0 / 3.0
  return ret

def transform_lng(lng, lat):
  ret = 300.0 + lng + 2.0 * lat + 0.1 * lng * lng + 0.1 * lng * lat + 0.1 * math.sqrt(abs(lng))
  ret += (20.0 * math.sin(6.0 * lng * pi) + 20.0 * math.sin(2.0 * lng * pi)) * 2.0 / 3.0
  ret += (20.0 * math.sin(lng * pi) + 40.0 * math.sin(lng / 3.0 * pi)) * 2.0 / 3.0
  ret += (150.0 * math.sin(lng / 12.0 * pi) + 300.0 * math.sin(lng / 30.0 * pi)) * 2.0 / 3.0
  return ret

def xor_encrypt_decrypt(data: str, key: str) -> str:
  return ''.join(chr(ord(c) ^ ord(key[i % len(key)])) for i, c in enumerate(data))

def encode_parameters(params_dict):
  serialized_data = json.dumps(params_dict)
  obfuscated_data = xor_encrypt_decrypt(serialized_data, XOR_KEY)
  encoded_data = base64.b64encode(obfuscated_data.encode('utf-8')).decode('utf-8')
  return encoded_data

def decode_parameters(encoded_string):
  obfuscated_data = base64.b64decode(encoded_string.encode('utf-8')).decode('utf-8')
  decrypted_data = xor_encrypt_decrypt(obfuscated_data, XOR_KEY)
  return json.loads(decrypted_data)

def get_all_toggle_values():
  toggle_values = {}
  for key, _, _ in frogpilot_default_params:
    if key in EXCLUDED_KEYS:
      continue
    raw_value = params.get(key)
    if isinstance(raw_value, bytes):
      value = raw_value.decode('utf-8')
    else:
      value = raw_value or "0"
    toggle_values[key] = value

  return encode_parameters(toggle_values)

def reset_toggle_values():
  params.put_bool("DoToggleReset", True)
  HARDWARE.reboot()

def store_toggle_values(request_data):
  allowed_keys = {key for key, _, _ in frogpilot_default_params}
  allowed_keys -= EXCLUDED_KEYS

  toggle_values = decode_parameters(request_data['data'])
  for key, value in toggle_values.items():
    if key not in allowed_keys:
      continue
    params.put(key, value)

  update_frogpilot_toggles()

def capture_tmux_log():
  os.makedirs(TMUX_LOGS_PATH, exist_ok=True)

  timestamp = datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
  log_filename = f"tmux_log_{timestamp}.txt"
  log_path = os.path.join(TMUX_LOGS_PATH, log_filename)

  try:
    subprocess.run(["tmux", "capture-pane", "-J", "-S", "-"], check=True)
    result = subprocess.run(["tmux", "show-buffer"], capture_output=True, text=True, check=True)

    with open(log_path, "w", encoding="utf-8") as log_file:
      log_file.write(result.stdout)

    subprocess.run(["tmux", "delete-buffer"], check=True)

    return log_filename

  except subprocess.CalledProcessError as e:
    raise Exception(f"Error capturing tmux log: {e}")

def lock_doors():
  try:
    print("Attempting to lock doors...")

    panda = Panda()
    print(f"Panda connected: {panda.get_usb_serial()}")
    print(f"Firmware Version: {panda.get_version()}")
    print(f"Hardware Type: {panda.get_type()}")
    initial_safety = panda.health()["safety_mode"]
    print(f"Initial Safety Mode: {initial_safety}")

    os.system("pkill -STOP -f pandad")

    print("Setting safety mode to SAFETY_TOYOTA...")
    panda.set_safety_mode(panda.SAFETY_TOYOTA)

    new_safety = panda.health()["safety_mode"]
    print(f"Safety Mode after change: {new_safety}")

    if new_safety != panda.SAFETY_TOYOTA:
      print("Failed to set SAFETY_TOYOTA! Aborting.")
      return

    can_health = panda.can_health(0)
    print(f"CAN0 Health: {can_health}")

    print(f"Sending CAN message to lock doors (ID=0x750, CMD={LOCK_CMD.hex()})...")
    panda.can_send(0x750, LOCK_CMD, 0)

    new_can_health = panda.can_health(0)
    print(f"CAN0 Health after send: {new_can_health}")

    final_safety = panda.health()["safety_mode"]
    print(f"Final Safety Mode: {final_safety}")

    print("Sending Panda heartbeat...")
    panda.send_heartbeat()

    print("Closing Panda connection.")
    panda.close()

    print("Lock doors operation completed successfully!")

    print("Starting the pandad process...")
    os.system("pkill -CONT -f pandad")

  except Exception as error:
    print(f"Error in lock_doors(): {error}")
    print(traceback.format_exc())

def unlock_doors():
  try:
    print("Attempting to unlock doors...")

    panda = Panda()
    print(f"Panda connected: {panda.get_usb_serial()}")
    print(f"Firmware Version: {panda.get_version()}")
    print(f"Hardware Type: {panda.get_type()}")
    initial_safety = panda.health()["safety_mode"]
    print(f"Initial Safety Mode: {initial_safety}")

    os.system("pkill -STOP -f pandad")

    print("Setting safety mode to SAFETY_TOYOTA...")
    panda.set_safety_mode(panda.SAFETY_TOYOTA)

    new_safety = panda.health()["safety_mode"]
    print(f"Safety Mode after change: {new_safety}")

    if new_safety != panda.SAFETY_TOYOTA:
      print("Failed to set SAFETY_TOYOTA! Aborting.")
      return

    can_health = panda.can_health(0)
    print(f"CAN0 Health: {can_health}")

    print(f"Sending CAN message to unlock doors (ID=0x750, CMD={UNLOCK_CMD.hex()})...")
    panda.can_send(0x750, UNLOCK_CMD, 0)

    new_can_health = panda.can_health(0)
    print(f"CAN0 Health after send: {new_can_health}")

    final_safety = panda.health()["safety_mode"]
    print(f"Final Safety Mode: {final_safety}")

    print("Sending Panda heartbeat...")
    panda.send_heartbeat()

    print("Closing Panda connection.")
    panda.close()

    print("Unlock doors operation completed successfully!")

    print("Starting the pandad process...")
    os.system("pkill -CONT -f pandad")

  except Exception as error:
    print(f"Error in unlock_doors(): {error}")
    print(traceback.format_exc())

def reboot_device():
  HARDWARE.reboot()
