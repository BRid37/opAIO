# PFEIFER - SLC - Modified by FrogAi for FrogPilot
#!/usr/bin/env python3
import json

from openpilot.selfdrive.frogpilot.frogpilot_utilities import calculate_distance_to_point
from openpilot.selfdrive.frogpilot.frogpilot_variables import TO_RADIANS, params, params_memory

class SpeedLimitController:
  def __init__(self):
    self.experimental_mode = False
    self.speed_limit_changed = False

    self.desired_speed_limit = 0
    self.map_speed_limit = 0
    self.speed_limit = 0
    self.upcoming_speed_limit = 0

    self.source = "None"

    self.previous_speed_limit = params.get_float("PreviousSpeedLimit")

  def update(self, dashboard_speed_limit, enabled, navigation_speed_limit, v_cruise, v_ego, frogpilot_toggles):
    self.update_map_speed_limit(v_ego, frogpilot_toggles)
    max_speed_limit = v_cruise if enabled else 0

    self.speed_limit = self.get_speed_limit(dashboard_speed_limit, max_speed_limit, navigation_speed_limit, frogpilot_toggles)
    self.desired_speed_limit = self.get_desired_speed_limit()

    self.experimental_mode = frogpilot_toggles.slc_fallback_experimental_mode and self.speed_limit == 0

  def get_desired_speed_limit(self):
    if self.speed_limit > 1:
      if abs(self.speed_limit - self.previous_speed_limit) > 1:
        params.put_float_nonblocking("PreviousSpeedLimit", self.speed_limit)
        self.previous_speed_limit = self.speed_limit
        self.speed_limit_changed = True
      return self.speed_limit
    else:
      self.speed_limit_changed = False
      return 0

  def update_map_speed_limit(self, v_ego, frogpilot_toggles):
    position = json.loads(params_memory.get("LastGPSPosition") or "{}")
    if not position:
      self.map_speed_limit = 0
      return

    self.map_speed_limit = params_memory.get_float("MapSpeedLimit")

    next_map_speed_limit = json.loads(params_memory.get("NextMapSpeedLimit") or "{}")
    self.upcoming_speed_limit = next_map_speed_limit.get("speedlimit", 0)
    if self.upcoming_speed_limit > 1:
      current_latitude = position.get("latitude")
      current_longitude = position.get("longitude")

      upcoming_latitude = next_map_speed_limit.get("latitude")
      upcoming_longitude = next_map_speed_limit.get("longitude")

      distance_to_upcoming = calculate_distance_to_point(current_latitude * TO_RADIANS, current_longitude * TO_RADIANS, upcoming_latitude * TO_RADIANS, upcoming_longitude * TO_RADIANS)

      if self.previous_speed_limit < self.upcoming_speed_limit:
        max_distance = frogpilot_toggles.map_speed_lookahead_higher * v_ego
      else:
        max_distance = frogpilot_toggles.map_speed_lookahead_lower * v_ego

      if distance_to_upcoming < max_distance:
        self.map_speed_limit = self.upcoming_speed_limit

  def get_offset(self, speed_limit, frogpilot_toggles):
    if frogpilot_toggles.is_metric:
      offset_map = [
        (0, 8.1, frogpilot_toggles.speed_limit_offset1),      # 0–29 km/h
        (8.1, 13.6, frogpilot_toggles.speed_limit_offset2),   # 30–49
        (13.6, 16.4, frogpilot_toggles.speed_limit_offset3),  # 50–59
        (16.4, 21.9, frogpilot_toggles.speed_limit_offset4),  # 60–79
        (21.9, 27.5, frogpilot_toggles.speed_limit_offset5),  # 80–99
        (27.5, 33.1, frogpilot_toggles.speed_limit_offset6),  # 100–119
        (33.1, 38.9, frogpilot_toggles.speed_limit_offset7),  # 120–140
      ]
    else:
      offset_map = [
        (0, 11.2, frogpilot_toggles.speed_limit_offset1),     # 0–24 mph
        (11.2, 15.2, frogpilot_toggles.speed_limit_offset2),  # 25–34
        (15.2, 19.6, frogpilot_toggles.speed_limit_offset3),  # 35–44
        (19.6, 24.1, frogpilot_toggles.speed_limit_offset4),  # 45–54
        (24.1, 28.6, frogpilot_toggles.speed_limit_offset5),  # 55–64
        (28.6, 33.1, frogpilot_toggles.speed_limit_offset6),  # 65–74
        (33.1, 44.2, frogpilot_toggles.speed_limit_offset7),  # 75–99
      ]
    return next((offset for low, high, offset in offset_map if low < speed_limit < high), 0)

  def get_speed_limit(self, dashboard_speed_limit, max_speed_limit, navigation_speed_limit, frogpilot_toggles):
    limits = {
      "Dashboard": dashboard_speed_limit,
      "Map Data": self.map_speed_limit,
      "Navigation": navigation_speed_limit
    }
    filtered_limits = {source: float(limit) for source, limit in limits.items() if limit > 1}

    if filtered_limits:
      if frogpilot_toggles.speed_limit_priority_highest:
        self.source = max(filtered_limits, key=filtered_limits.get)
        return filtered_limits[self.source]

      if frogpilot_toggles.speed_limit_priority_lowest:
        self.source = min(filtered_limits, key=filtered_limits.get)
        return filtered_limits[self.source]

      for priority in [
        frogpilot_toggles.speed_limit_priority1,
        frogpilot_toggles.speed_limit_priority2,
        frogpilot_toggles.speed_limit_priority3
      ]:
        if priority is not None and priority in filtered_limits:
          self.source = priority
          return filtered_limits[priority]

    self.source = "None"

    if frogpilot_toggles.slc_fallback_previous_speed_limit:
      return self.previous_speed_limit

    if frogpilot_toggles.slc_fallback_set_speed:
      return max_speed_limit

    return 0
