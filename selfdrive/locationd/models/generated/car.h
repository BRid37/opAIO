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
void car_err_fun(double *nom_x, double *delta_x, double *out_6739729583278533622);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_4580221091051696781);
void car_H_mod_fun(double *state, double *out_9179971792990499705);
void car_f_fun(double *state, double dt, double *out_6748960235092935949);
void car_F_fun(double *state, double dt, double *out_2096886756008492430);
void car_h_25(double *state, double *unused, double *out_553976550253322035);
void car_H_25(double *state, double *unused, double *out_7111446507229786949);
void car_h_24(double *state, double *unused, double *out_1175334170647651268);
void car_H_24(double *state, double *unused, double *out_910413827378625523);
void car_h_30(double *state, double *unused, double *out_3501702540608806996);
void car_H_30(double *state, double *unused, double *out_6982107560086546879);
void car_h_26(double *state, double *unused, double *out_7228212129951677070);
void car_H_26(double *state, double *unused, double *out_3369943188355730725);
void car_h_27(double *state, double *unused, double *out_2050428770555375616);
void car_H_27(double *state, double *unused, double *out_4807344248286121968);
void car_h_29(double *state, double *unused, double *out_4105018425285284513);
void car_H_29(double *state, double *unused, double *out_3093981521416570935);
void car_h_28(double *state, double *unused, double *out_7414346131147335235);
void car_H_28(double *state, double *unused, double *out_5057611792981897186);
void car_h_31(double *state, double *unused, double *out_7327296100500727150);
void car_H_31(double *state, double *unused, double *out_7142092469106747377);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}