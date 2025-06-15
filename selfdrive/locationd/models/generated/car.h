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
void car_err_fun(double *nom_x, double *delta_x, double *out_2544821064399858965);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_6367162327906013787);
void car_H_mod_fun(double *state, double *out_2103091097720413186);
void car_f_fun(double *state, double dt, double *out_3409469352841446417);
void car_F_fun(double *state, double dt, double *out_5618527830171991882);
void car_h_25(double *state, double *unused, double *out_2067803326384484466);
void car_H_25(double *state, double *unused, double *out_8600114057610443137);
void car_h_24(double *state, double *unused, double *out_8720211228654265950);
void car_H_24(double *state, double *unused, double *out_4977815151071401627);
void car_h_30(double *state, double *unused, double *out_8431397304686300327);
void car_H_30(double *state, double *unused, double *out_5318933685971500281);
void car_h_26(double *state, double *unused, double *out_3429724037025454682);
void car_H_26(double *state, double *unused, double *out_6105126697225052255);
void car_h_27(double *state, double *unused, double *out_3498297857676025399);
void car_H_27(double *state, double *unused, double *out_7542527757155443498);
void car_h_29(double *state, double *unused, double *out_550571867320540438);
void car_H_29(double *state, double *unused, double *out_5829165030285892465);
void car_h_28(double *state, double *unused, double *out_6310849960945878782);
void car_H_28(double *state, double *unused, double *out_746766013216361891);
void car_h_31(double *state, double *unused, double *out_7739063270606525266);
void car_H_31(double *state, double *unused, double *out_8569468095733482709);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}