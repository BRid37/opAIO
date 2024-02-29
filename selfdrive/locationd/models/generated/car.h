#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_err_fun(double *nom_x, double *delta_x, double *out_2839074644799155373);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_2832413412600408261);
void car_H_mod_fun(double *state, double *out_2434754126251583803);
void car_f_fun(double *state, double dt, double *out_3191743563366687036);
void car_F_fun(double *state, double dt, double *out_3866238660743559275);
void car_h_25(double *state, double *unused, double *out_7618328033706461649);
void car_H_25(double *state, double *unused, double *out_3381267097997126629);
void car_h_24(double *state, double *unused, double *out_1309502016488901519);
void car_H_24(double *state, double *unused, double *out_2251733942599321359);
void car_h_30(double *state, double *unused, double *out_5049370252009797283);
void car_H_30(double *state, double *unused, double *out_1146429232130481569);
void car_h_26(double *state, double *unused, double *out_86990254328504051);
void car_H_26(double *state, double *unused, double *out_360236220876929595);
void car_h_27(double *state, double *unused, double *out_2616654766045616004);
void car_H_27(double *state, double *unused, double *out_1077164839053461648);
void car_h_29(double *state, double *unused, double *out_4067286158674499171);
void car_H_29(double *state, double *unused, double *out_636197887816089385);
void car_h_28(double *state, double *unused, double *out_8374639680039353960);
void car_H_28(double *state, double *unused, double *out_5718596904885619959);
void car_h_31(double *state, double *unused, double *out_6966732563574588315);
void car_H_31(double *state, double *unused, double *out_986444323110281071);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}