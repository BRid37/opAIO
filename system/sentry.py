"""Install exception handler for process crash."""
import os
import psutil
import sentry_sdk
import traceback
from datetime import datetime
from enum import Enum
from pathlib import Path
from sentry_sdk.integrations.threading import ThreadingIntegration

from openpilot.common.params import Params, ParamKeyType
from openpilot.system.hardware import HARDWARE, PC
from openpilot.common.swaglog import cloudlog
from openpilot.system.version import get_build_metadata, get_version

from openpilot.frogpilot.common.frogpilot_variables import ERROR_LOGS_PATH, params

class SentryProject(Enum):
  # python project
  SELFDRIVE = os.environ.get("SENTRY_DSN", "")
  # native project
  SELFDRIVE_NATIVE = os.environ.get("SENTRY_DSN", "")


def report_tombstone(fn: str, message: str, contents: str) -> None:
  cloudlog.error({'tombstone': message})

  with sentry_sdk.configure_scope() as scope:
    scope.set_extra("tombstone_fn", fn)
    scope.set_extra("tombstone", contents)
    sentry_sdk.capture_message(message=message)
    sentry_sdk.flush()


def capture_exception(*args, **kwargs) -> None:
  exc_text = traceback.format_exc()

  phrases_to_check = [
    "already exists. To overwrite it, set 'overwrite' to True",
    "setup_quectel failed after retry",
  ]

  if any(phrase in exc_text for phrase in phrases_to_check):
    return

  save_exception(exc_text)
  cloudlog.error("crash", exc_info=kwargs.get("exc_info", 1))

  try:
    sentry_sdk.capture_exception(*args, **kwargs)
    sentry_sdk.flush()  # https://github.com/getsentry/sentry-python/issues/291
  except Exception:
    cloudlog.exception("sentry exception")


def capture_memory_log():
  virtual_memory = psutil.virtual_memory()
  total_used = virtual_memory.used
  total_memory = virtual_memory.total

  process_list = []
  for process in psutil.process_iter(['pid', 'username', 'memory_percent', 'cmdline', 'name']):
    try:
      cmdline = process.info.get('cmdline')
      memory_percent = process.info.get('memory_percent', 0)

      if cmdline and len(cmdline) > 0:
        command = " ".join(cmdline)
      else:
        command = process.info.get('name', '')

      process_list.append({
        "pid": process.info['pid'],
        "user": process.info.get('username', ''),
        "memory_usage_percent": memory_percent,
        "command": command
      })
    except (psutil.NoSuchProcess, psutil.AccessDenied):
      continue

  process_list.sort(key=lambda process: process['memory_usage_percent'], reverse=True)
  top_processes = process_list[:5]

  message = (
    f"High memory detected: "
    f"{(total_used / total_memory) * 100:.2f}% of total."
  )

  with sentry_sdk.push_scope() as scope:
    scope.set_extra("total_memory_usage_percent", (total_used / total_memory) * 100)
    scope.set_extra("top_processes", top_processes)
    scope.set_extra("updater_state", params.get("UpdaterState", encoding="utf-8"))
    sentry_sdk.capture_message(message, level="fatal")
    sentry_sdk.flush()


def capture_report(discord_user, report, frogpilot_toggles):
  error_file_path = ERROR_LOGS_PATH / "error.txt"
  error_content = "No error log found."

  if error_file_path.exists():
    error_content = error_file_path.read_text()

  with sentry_sdk.push_scope() as scope:
    scope.set_context("Error Log", {"content": error_content})
    scope.set_context("Toggle Values", frogpilot_toggles)
    sentry_sdk.capture_message(f"{discord_user} submitted report: {report}", level="fatal")
    sentry_sdk.flush()


def set_tag(key: str, value: str) -> None:
  sentry_sdk.set_tag(key, value)


def save_exception(exc_text: str) -> None:
  files = [
    ERROR_LOGS_PATH / datetime.now().strftime("%Y-%m-%d--%H-%M-%S.log"),
    ERROR_LOGS_PATH / "error.txt"
  ]

  for file_path in files:
    if file_path.name == "error.txt":
      lines = exc_text.splitlines()[-10:]
      file_path.write_text("\n".join(lines))
    else:
      file_path.write_text(exc_text)

  print(f"Logged current crash to {[str(file) for file in files]}")


def init(project: SentryProject) -> bool:
  build_metadata = get_build_metadata()
  FrogPilot = "frogai" in build_metadata.openpilot.git_origin.lower()
  if not FrogPilot or PC:
    return False

  short_branch = build_metadata.channel

  if short_branch == "COMMA":
    return
  elif short_branch == "FrogPilot-Development":
    env = "Development"
  elif build_metadata.release_channel:
    env = "Release"
  elif short_branch == "FrogPilot-Testing":
    env = "Testing"
  elif build_metadata.tested_channel:
    env = "Staging"
  else:
    env = short_branch

  params = Params()
  dongle_id = params.get("DongleId", encoding="utf-8")
  installed = params.get("InstallDate", encoding="utf-8")
  updated = params.get("Updated", encoding="utf-8")

  integrations = []
  if project == SentryProject.SELFDRIVE:
    integrations.append(ThreadingIntegration(propagate_hub=True))

  sentry_sdk.init(project.value,
                  default_integrations=False,
                  release=get_version(),
                  integrations=integrations,
                  traces_sample_rate=1.0,
                  max_value_length=8192,
                  environment=env)

  sentry_sdk.set_user({"id": dongle_id})
  sentry_sdk.set_tag("origin", build_metadata.openpilot.git_origin)
  sentry_sdk.set_tag("branch", short_branch)
  sentry_sdk.set_tag("commit", build_metadata.openpilot.git_commit)
  sentry_sdk.set_tag("updated", updated)
  sentry_sdk.set_tag("installed", installed)

  if project == SentryProject.SELFDRIVE:
    sentry_sdk.Hub.current.start_session()

  return True
