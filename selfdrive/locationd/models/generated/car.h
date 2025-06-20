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
void car_err_fun(double *nom_x, double *delta_x, double *out_6231474097932119358);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8658353309641893703);
void car_H_mod_fun(double *state, double *out_5523145543669707057);
void car_f_fun(double *state, double dt, double *out_6690793444903813550);
void car_F_fun(double *state, double dt, double *out_6579261019638953676);
void car_h_25(double *state, double *unused, double *out_7306685628894564884);
void car_H_25(double *state, double *unused, double *out_973877416220322894);
void car_h_24(double *state, double *unused, double *out_52094312227393299);
void car_H_24(double *state, double *unused, double *out_7174910096071484320);
void car_h_30(double *state, double *unused, double *out_7581879691179070773);
void car_H_30(double *state, double *unused, double *out_1103216363363562964);
void car_h_26(double *state, double *unused, double *out_2580206423518225128);
void car_H_26(double *state, double *unused, double *out_4715380735094379118);
void car_h_27(double *state, double *unused, double *out_6138385177154141087);
void car_H_27(double *state, double *unused, double *out_3277979675163987875);
void car_h_29(double *state, double *unused, double *out_7589016569783024254);
void car_H_29(double *state, double *unused, double *out_4991342402033538908);
void car_h_28(double *state, double *unused, double *out_35865741420946697);
void car_H_28(double *state, double *unused, double *out_8373002654606482134);
void car_h_31(double *state, double *unused, double *out_3669236100640542534);
void car_H_31(double *state, double *unused, double *out_943231454343362466);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}