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
void car_err_fun(double *nom_x, double *delta_x, double *out_5038973705749725969);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_5775683794591023860);
void car_H_mod_fun(double *state, double *out_4926761572782853817);
void car_f_fun(double *state, double dt, double *out_6329062410056106380);
void car_F_fun(double *state, double dt, double *out_922264769340125727);
void car_h_25(double *state, double *unused, double *out_2976232889390128900);
void car_H_25(double *state, double *unused, double *out_8449742222772345494);
void car_h_24(double *state, double *unused, double *out_5313149587106084559);
void car_H_24(double *state, double *unused, double *out_6439076252134882986);
void car_h_30(double *state, double *unused, double *out_8699675957969071780);
void car_H_30(double *state, double *unused, double *out_7478668892429957495);
void car_h_26(double *state, double *unused, double *out_96633506296925360);
void car_H_26(double *state, double *unused, double *out_4708238903898289270);
void car_h_27(double *state, double *unused, double *out_8461316920730961355);
void car_H_27(double *state, double *unused, double *out_5255074821246014278);
void car_h_29(double *state, double *unused, double *out_5887123854699218397);
void car_H_29(double *state, double *unused, double *out_6968437548115565311);
void car_h_28(double *state, double *unused, double *out_3316426857615313818);
void car_H_28(double *state, double *unused, double *out_6395907508524455731);
void car_h_31(double *state, double *unused, double *out_6613682417644151250);
void car_H_31(double *state, double *unused, double *out_8480388184649305922);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}