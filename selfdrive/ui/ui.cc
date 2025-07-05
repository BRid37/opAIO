#include "selfdrive/ui/ui.h"

#include <algorithm>
#include <cassert>
#include <cmath>

#include <QtConcurrent>

#include "common/transformations/orientation.hpp"
#include "common/params.h"
#include "common/swaglog.h"
#include "common/util.h"
#include "common/watchdog.h"
#include "system/hardware/hw.h"

#define BACKLIGHT_DT 0.05
#define BACKLIGHT_TS 10.00

// Projects a point in car to space to the corresponding point in full frame
// image space.
static bool calib_frame_to_full_frame(const UIState *s, float in_x, float in_y, float in_z, QPointF *out) {
  const float margin = 500.0f;
  const QRectF clip_region{-margin, -margin, s->fb_w + 2 * margin, s->fb_h + 2 * margin};

  const vec3 pt = (vec3){{in_x, in_y, in_z}};
  const vec3 Ep = matvecmul3(s->scene.wide_cam ? s->scene.view_from_wide_calib : s->scene.view_from_calib, pt);
  const vec3 KEp = matvecmul3(s->scene.wide_cam ? ECAM_INTRINSIC_MATRIX : FCAM_INTRINSIC_MATRIX, Ep);

  // Project.
  QPointF point = s->car_space_transform.map(QPointF{KEp.v[0] / KEp.v[2], KEp.v[1] / KEp.v[2]});
  if (clip_region.contains(point)) {
    *out = point;
    return true;
  }
  return false;
}

int get_path_length_idx(const cereal::XYZTData::Reader &line, const float path_height) {
  const auto line_x = line.getX();
  int max_idx = 0;
  for (int i = 1; i < line_x.size() && line_x[i] <= path_height; ++i) {
    max_idx = i;
  }
  return max_idx;
}

void update_leads(UIState *s, const cereal::RadarState::Reader &radar_state, const cereal::XYZTData::Reader &line) {
  for (int i = 0; i < 4; ++i) {
    auto lead_data = (i == 0) ? radar_state.getLeadOne() : (i == 1) ? radar_state.getLeadTwo() : (i == 2) ? radar_state.getLeadLeft() : radar_state.getLeadRight();
    if (lead_data.getStatus()) {
      float z = line.getZ()[get_path_length_idx(line, lead_data.getDRel())];
      calib_frame_to_full_frame(s, lead_data.getDRel(), -lead_data.getYRel(), z + 1.22, &s->scene.lead_vertices[i]);
    }
  }
}

void update_radar_tracks(capnp::List<cereal::LiveTracks>::Reader &tracks_msg, cereal::XYZTData::Reader line, const UIState &s, const SubMaster &sm) {
  FrogPilotUIState *fs = frogpilotUIState();
  FrogPilotUIScene &frogpilot_scene = fs->frogpilot_scene;

  frogpilot_scene.live_radar_tracks.clear();

  float path_offset_z = sm["liveCalibration"].getLiveCalibration().getHeight()[0];

  std::size_t num_tracks = tracks_msg.size();
  frogpilot_scene.live_radar_tracks.reserve(num_tracks);

  for (std::size_t i = 0; i < num_tracks; i++) {
    cereal::LiveTracks::Reader track_msg = tracks_msg[i];

    float dRel = track_msg.getDRel();
    float yRel = track_msg.getYRel();
    float z = line.getZ()[get_path_length_idx(line, dRel)];

    QPointF calibrated_point;
    if (calib_frame_to_full_frame(&s, dRel, -yRel, z + path_offset_z, &calibrated_point)) {
      RadarTrackData track;
      track.calibrated_point = calibrated_point;
      frogpilot_scene.live_radar_tracks.push_back(track);
    }
  }
}

void update_line_data(const UIState *s, const cereal::XYZTData::Reader &line,
                      float y_off, float z_off, QPolygonF *pvd, int max_idx, bool allow_invert=true) {
  const auto line_x = line.getX(), line_y = line.getY(), line_z = line.getZ();
  QPointF left, right;
  pvd->clear();
  for (int i = 0; i <= max_idx; i++) {
    // highly negative x positions  are drawn above the frame and cause flickering, clip to zy plane of camera
    if (line_x[i] < 0) continue;

    bool l = calib_frame_to_full_frame(s, line_x[i], line_y[i] - y_off, line_z[i] + z_off, &left);
    bool r = calib_frame_to_full_frame(s, line_x[i], line_y[i] + y_off, line_z[i] + z_off, &right);
    if (l && r) {
      // For wider lines the drawn polygon will "invert" when going over a hill and cause artifacts
      if (!allow_invert && pvd->size() && left.y() > pvd->back().y()) {
        continue;
      }
      pvd->push_back(left);
      pvd->push_front(right);
    }
  }
}

void update_model(UIState *s, FrogPilotUIState *fs,
                  const cereal::ModelDataV2::Reader &model,
                  const cereal::UiPlan::Reader &plan,
                  const QJsonObject &frogpilot_toggles) {
  UIScene &scene = s->scene;
  FrogPilotUIScene &frogpilot_scene = fs->frogpilot_scene;
  frogpilot_scene.model_length = model.getPosition().getX()[33 - 1];
  auto plan_position = plan.getPosition();
  if (plan_position.getX().size() < model.getPosition().getX().size()) {
    plan_position = model.getPosition();
  }
  float max_distance = frogpilot_toggles.value("unlimited_road_ui_length").toBool() ? *(plan_position.getX().end() - 1) :
                       std::clamp(*(plan_position.getX().end() - 1),
                                  MIN_DRAW_DISTANCE, MAX_DRAW_DISTANCE);

  // update lane lines
  const auto lane_lines = model.getLaneLines();
  const auto lane_line_probs = model.getLaneLineProbs();
  int max_idx = get_path_length_idx(lane_lines[0], max_distance);
  for (int i = 0; i < std::size(scene.lane_line_vertices); i++) {
    scene.lane_line_probs[i] = lane_line_probs[i];
    update_line_data(s, lane_lines[i], frogpilot_toggles.value("model_ui").toBool() ? frogpilot_toggles.value("lane_line_width").toDouble() : 0.025 * scene.lane_line_probs[i], 0, &scene.lane_line_vertices[i], max_idx);
  }

  // update road edges
  const auto road_edges = model.getRoadEdges();
  const auto road_edge_stds = model.getRoadEdgeStds();
  for (int i = 0; i < std::size(scene.road_edge_vertices); i++) {
    scene.road_edge_stds[i] = road_edge_stds[i];
    update_line_data(s, road_edges[i], frogpilot_toggles.value("model_ui").toBool() ? frogpilot_toggles.value("road_edge_width").toDouble() : 0.025, 0, &scene.road_edge_vertices[i], max_idx);
  }

  // update path
  float path_width = frogpilot_toggles.value("path_width").toDouble();
  if (frogpilot_toggles.value("dynamic_path_width").toBool()) {
    path_width *= s->status == STATUS_ENGAGED ? 1.0f : s->status == STATUS_ALWAYS_ON_LATERAL_ACTIVE ? 0.75f : 0.50f;
  }

  auto lead_one = (*s->sm)["radarState"].getRadarState().getLeadOne();
  if (lead_one.getStatus()) {
    const float lead_d = lead_one.getDRel() * 2.;
    max_distance = std::clamp((float)(lead_d - fmin(lead_d * 0.35, 10.)), 0.0f, max_distance);
  }
  max_idx = get_path_length_idx(plan_position, max_distance);
  update_line_data(s, plan_position, frogpilot_toggles.value("model_ui").toBool() ? path_width * (1 - (frogpilot_toggles.value("path_edge_width").toDouble() / 100.0f)) : 0.9, 1.22, &scene.track_vertices, max_idx, false);

  // Update path edges
  update_line_data(s, plan_position, frogpilot_toggles.value("model_ui").toBool() ? path_width : 0, 1.22, &frogpilot_scene.track_edge_vertices, max_idx, false);

  // Update adjacent lanes
  update_line_data(s, lane_lines[4], frogpilot_scene.lane_width_left / 2.0f, 0, &frogpilot_scene.track_adjacent_vertices[0], max_idx, false);
  update_line_data(s, lane_lines[5], frogpilot_scene.lane_width_right / 2.0f, 0, &frogpilot_scene.track_adjacent_vertices[1], max_idx, false);

  frogpilot_scene.model_length = model.getPosition().getX()[33 - 1];
}

void update_dmonitoring(UIState *s, const cereal::DriverStateV2::Reader &driverstate, float dm_fade_state, bool is_rhd) {
  UIScene &scene = s->scene;
  const auto driver_orient = is_rhd ? driverstate.getRightDriverData().getFaceOrientation() : driverstate.getLeftDriverData().getFaceOrientation();
  for (int i = 0; i < std::size(scene.driver_pose_vals); i++) {
    float v_this = (i == 0 ? (driver_orient[i] < 0 ? 0.7 : 0.9) : 0.4) * driver_orient[i];
    scene.driver_pose_diff[i] = fabs(scene.driver_pose_vals[i] - v_this);
    scene.driver_pose_vals[i] = 0.8 * v_this + (1 - 0.8) * scene.driver_pose_vals[i];
    scene.driver_pose_sins[i] = sinf(scene.driver_pose_vals[i]*(1.0-dm_fade_state));
    scene.driver_pose_coss[i] = cosf(scene.driver_pose_vals[i]*(1.0-dm_fade_state));
  }

  auto [sin_y, sin_x, sin_z] = scene.driver_pose_sins;
  auto [cos_y, cos_x, cos_z] = scene.driver_pose_coss;

  const mat3 r_xyz = (mat3){{
    cos_x * cos_z,
    cos_x * sin_z,
    -sin_x,

    -sin_y * sin_x * cos_z - cos_y * sin_z,
    -sin_y * sin_x * sin_z + cos_y * cos_z,
    -sin_y * cos_x,

    cos_y * sin_x * cos_z - sin_y * sin_z,
    cos_y * sin_x * sin_z + sin_y * cos_z,
    cos_y * cos_x,
  }};

  // transform vertices
  for (int kpi = 0; kpi < std::size(default_face_kpts_3d); kpi++) {
    vec3 kpt_this = matvecmul3(r_xyz, default_face_kpts_3d[kpi]);
    scene.face_kpts_draw[kpi] = (vec3){{kpt_this.v[0], kpt_this.v[1], (float)(kpt_this.v[2] * (1.0-dm_fade_state) + 8 * dm_fade_state)}};
  }
}

static void update_sockets(UIState *s) {
  s->sm->update(0);
}

static void update_state(UIState *s, FrogPilotUIState *fs) {
  SubMaster &sm = *(s->sm);
  UIScene &scene = s->scene;

  if (sm.updated("liveCalibration")) {
    auto live_calib = sm["liveCalibration"].getLiveCalibration();
    auto rpy_list = live_calib.getRpyCalib();
    auto wfde_list = live_calib.getWideFromDeviceEuler();
    Eigen::Vector3d rpy;
    Eigen::Vector3d wfde;
    if (rpy_list.size() == 3) rpy << rpy_list[0], rpy_list[1], rpy_list[2];
    if (wfde_list.size() == 3) wfde << wfde_list[0], wfde_list[1], wfde_list[2];
    Eigen::Matrix3d device_from_calib = euler2rot(rpy);
    Eigen::Matrix3d wide_from_device = euler2rot(wfde);
    Eigen::Matrix3d view_from_device;
    view_from_device << 0, 1, 0,
                        0, 0, 1,
                        1, 0, 0;
    Eigen::Matrix3d view_from_calib = view_from_device * device_from_calib;
    Eigen::Matrix3d view_from_wide_calib = view_from_device * wide_from_device * device_from_calib;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        scene.view_from_calib.v[i*3 + j] = view_from_calib(i, j);
        scene.view_from_wide_calib.v[i*3 + j] = view_from_wide_calib(i, j);
      }
    }
    scene.calibration_valid = live_calib.getCalStatus() == cereal::LiveCalibrationData::Status::CALIBRATED;
    scene.calibration_wide_valid = wfde_list.size() == 3;
  }
  if (sm.updated("pandaStates")) {
    auto pandaStates = sm["pandaStates"].getPandaStates();
    if (pandaStates.size() > 0) {
      scene.pandaType = pandaStates[0].getPandaType();

      if (scene.pandaType != cereal::PandaState::PandaType::UNKNOWN) {
        scene.ignition = false;
        for (const auto& pandaState : pandaStates) {
          scene.ignition |= pandaState.getIgnitionLine() || pandaState.getIgnitionCan();
        }
      }
    }
  } else if ((s->sm->frame - s->sm->rcv_frame("pandaStates")) > 5*UI_FREQ) {
    scene.pandaType = cereal::PandaState::PandaType::UNKNOWN;
  }
  if (sm.updated("carParams")) {
    scene.longitudinal_control = sm["carParams"].getCarParams().getOpenpilotLongitudinalControl();
  }
  if (sm.updated("wideRoadCameraState")) {
    auto cam_state = sm["wideRoadCameraState"].getWideRoadCameraState();
    float scale = (cam_state.getSensor() == cereal::FrameData::ImageSensor::AR0231) ? 6.0f : 1.0f;
    scene.light_sensor = std::max(100.0f - scale * cam_state.getExposureValPercent(), 0.0f);
  } else if (!sm.allAliveAndValid({"wideRoadCameraState"})) {
    scene.light_sensor = -1;
  }
  scene.started = sm["deviceState"].getDeviceState().getStarted() && scene.ignition;
  if (scene.started) {
    fs->frogpilot_scene.started_timer += 1;
  }
  scene.started |= fs->frogpilot_toggles.value("force_onroad").toBool();
  scene.started &= !fs->frogpilot_toggles.value("force_offroad").toBool();

  scene.world_objects_visible = scene.world_objects_visible ||
                                (scene.started &&
                                 sm.rcv_frame("liveCalibration") > scene.started_frame &&
                                 sm.rcv_frame("modelV2") > scene.started_frame &&
                                 sm.rcv_frame("uiPlan") > scene.started_frame);
}

void ui_update_params(UIState *s) {
  auto params = Params();
  s->scene.is_metric = params.getBool("IsMetric");
  s->scene.map_on_left = params.getBool("NavSettingLeftSide");
}

void UIState::updateStatus(FrogPilotUIState *fs) {
  FrogPilotUIScene &frogpilot_scene = fs->frogpilot_scene;
  QJsonObject &frogpilot_toggles = fs->frogpilot_toggles;

  if (scene.started && sm->updated("controlsState")) {
    auto controls_state = (*sm)["controlsState"].getControlsState();
    auto state = controls_state.getState();

    const UIStatus previous_status = status;

    if (state == cereal::ControlsState::OpenpilotState::PRE_ENABLED || state == cereal::ControlsState::OpenpilotState::OVERRIDING) {
      status = STATUS_OVERRIDE;
    } else if (frogpilot_scene.always_on_lateral_active) {
      status = STATUS_ALWAYS_ON_LATERAL_ACTIVE;
    } else if (frogpilot_scene.traffic_mode_enabled && controls_state.getEnabled()) {
      status = STATUS_TRAFFIC_MODE_ENABLED;
    } else {
      status = controls_state.getEnabled() ? STATUS_ENGAGED : STATUS_DISENGAGED;
    }

    fs->frogpilot_scene.wake_up_screen = controls_state.getAlertStatus() != cereal::ControlsState::AlertStatus::NORMAL || (status != previous_status && status != STATUS_OVERRIDE);
  }

  // Handle onroad/offroad transition
  if (scene.started != started_prev || sm->frame == 1) {
    if (scene.started) {
      status = STATUS_DISENGAGED;
      scene.started_frame = sm->frame;
    } else if (frogpilot_scene.started_timer > 15*60*UI_FREQ && frogpilot_toggles.value("model_randomizer").toBool()) {
      emit fs->reviewModel();
    }
    started_prev = scene.started;
    scene.world_objects_visible = false;
    emit offroadTransition(!scene.started);

    fs->frogpilot_scene.started_timer = 0;

    if (frogpilot_toggles.value("tethering_config").toInt() == 2) {
      fs->wifi->setTetheringEnabled(scene.started);
    }
  }
}

UIState::UIState(QObject *parent) : QObject(parent) {
  sm = std::make_unique<SubMaster, const std::initializer_list<const char *>>({
    "modelV2", "controlsState", "liveCalibration", "radarState", "deviceState",
    "pandaStates", "carParams", "driverMonitoringState", "carState", "liveLocationKalman", "driverStateV2",
    "wideRoadCameraState", "managerState", "navInstruction", "navRoute", "uiPlan", "clocks",
  });

  Params params;
  language = QString::fromStdString(params.get("LanguageSetting"));
  auto prime_value = params.get("PrimeType");
  if (!prime_value.empty()) {
    prime_type = static_cast<PrimeType>(std::atoi(prime_value.c_str()));
  }

  // update timer
  timer = new QTimer(this);
  QObject::connect(timer, &QTimer::timeout, this, &UIState::update);
  timer->start(1000 / UI_FREQ);
}

void UIState::update() {
  update_sockets(this);
  update_state(this, frogpilotUIState());
  updateStatus(frogpilotUIState());

  if (sm->frame % UI_FREQ == 0) {
    watchdog_kick(nanos_since_boot());
  }
  emit uiUpdate(*this, *frogpilotUIState());

  // Update the FrogPilot UI
  FrogPilotUIState *fs = frogpilotUIState();
  FrogPilotUIScene &frogpilot_scene = fs->frogpilot_scene;
  QJsonObject &frogpilot_toggles = fs->frogpilot_toggles;

  fs->update();

  if (frogpilot_scene.downloading_update || frogpilot_scene.frogpilot_panel_active) {
    device()->resetInteractiveTimeout(frogpilot_toggles.value("screen_timeout").toInt(), frogpilot_toggles.value("screen_timeout_onroad").toInt());
  }
}

void UIState::setPrimeType(PrimeType type) {
  if (type != prime_type) {
    bool prev_prime = hasPrime();

    prime_type = type;
    Params().put("PrimeType", std::to_string(prime_type));
    emit primeTypeChanged(prime_type);

    bool prime = hasPrime();
    if (prev_prime != prime) {
      emit primeChanged(prime);
    }
  }
}

Device::Device(QObject *parent) : brightness_filter(BACKLIGHT_OFFROAD, BACKLIGHT_TS, BACKLIGHT_DT), QObject(parent) {
  setAwake(true);
  resetInteractiveTimeout();

  QObject::connect(uiState(), &UIState::uiUpdate, this, &Device::update);
}

void Device::update(const UIState &s, const FrogPilotUIState &fs) {
  updateBrightness(s, fs);
  updateWakefulness(s, fs);
}

void Device::setAwake(bool on) {
  if (on != awake) {
    awake = on;
    Hardware::set_display_power(awake);
    LOGD("setting display power %d", awake);
    emit displayPowerChanged(awake);
  }
}

void Device::resetInteractiveTimeout(int timeout, int timeout_onroad) {
  if (timeout == -1) {
    timeout = (ignition_on ? 10 : 30);
  }
  interactive_timeout = timeout * UI_FREQ;
}

void Device::updateBrightness(const UIState &s, const FrogPilotUIState &fs) {
  const FrogPilotUIScene &frogpilot_scene = fs.frogpilot_scene;
  const QJsonObject &frogpilot_toggles = fs.frogpilot_toggles;

  float clipped_brightness = offroad_brightness;
  if (s.scene.started && s.scene.light_sensor >= 0) {
    clipped_brightness = s.scene.light_sensor;

    // CIE 1931 - https://www.photonstophotos.net/GeneralTopics/Exposure/Psychometric_Lightness_and_Gamma.htm
    if (clipped_brightness <= 8) {
      clipped_brightness = (clipped_brightness / 903.3);
    } else {
      clipped_brightness = std::pow((clipped_brightness + 16.0) / 116.0, 3.0);
    }

    // Scale back to 10% to 100%
    clipped_brightness = std::clamp(100.0f * clipped_brightness, 10.0f, 100.0f);
  }

  int brightness = brightness_filter.update(clipped_brightness);
  if (!awake) {
    brightness = 0;
  } else if (s.scene.started && frogpilot_toggles.value("force_onroad").toBool()) {
    brightness = 100;
  } else if (s.scene.started && frogpilot_toggles.value("standby_mode").toBool() && !frogpilot_scene.wake_up_screen && interactive_timeout == 0) {
    brightness = 0;
  } else if (s.scene.started && frogpilot_toggles.value("screen_brightness_onroad").toInt() != 101) {
    brightness = interactive_timeout > 0 ? fmax(5, frogpilot_toggles.value("screen_brightness_onroad").toInt()) : frogpilot_toggles.value("screen_brightness_onroad").toInt();
  } else if (frogpilot_toggles.value("screen_brightness").toInt() != 101) {
    brightness = frogpilot_toggles.value("screen_brightness").toInt();
  }

  if (brightness != last_brightness) {
    if (!brightness_future.isRunning()) {
      brightness_future = QtConcurrent::run(Hardware::set_brightness, brightness);
      last_brightness = brightness;
    }
  }
}

void Device::updateWakefulness(const UIState &s, const FrogPilotUIState &fs) {
  const FrogPilotUIScene &frogpilot_scene = fs.frogpilot_scene;
  const QJsonObject &frogpilot_toggles = fs.frogpilot_toggles;

  bool ignition_state_changed = s.scene.ignition != ignition_on;
  ignition_on = s.scene.ignition;

  if (ignition_on && frogpilot_toggles.value("standby_mode").toBool()) {
    if (frogpilot_scene.wake_up_screen) {
      resetInteractiveTimeout(frogpilot_toggles.value("screen_timeout").toInt(), frogpilot_toggles.value("screen_timeout_onroad").toInt());
    }
  }

  if (ignition_state_changed) {
    if (ignition_on && frogpilot_toggles.value("screen_brightness_onroad").toInt() == 0 && !frogpilot_toggles.value("standby_mode").toBool()) {
      resetInteractiveTimeout(0, 0);
    } else {
      resetInteractiveTimeout(frogpilot_toggles.value("screen_timeout").toInt(), frogpilot_toggles.value("screen_timeout_onroad").toInt());
    }
  } else if (interactive_timeout > 0 && --interactive_timeout == 0) {
    emit interactiveTimeout();
  }

  setAwake(s.scene.started || interactive_timeout > 0);
}

UIState *uiState() {
  static UIState ui_state;
  return &ui_state;
}

Device *device() {
  static Device _device;
  return &_device;
}
