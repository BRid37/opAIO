#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_529622895560387506);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_5635522996089764755);
void pose_H_mod_fun(double *state, double *out_3534116985585266661);
void pose_f_fun(double *state, double dt, double *out_4412251706839144439);
void pose_F_fun(double *state, double dt, double *out_1358445773394405128);
void pose_h_4(double *state, double *unused, double *out_5199898530632523440);
void pose_H_4(double *state, double *unused, double *out_1714418259678969800);
void pose_h_10(double *state, double *unused, double *out_2062123331753171462);
void pose_H_10(double *state, double *unused, double *out_2475279207439212631);
void pose_h_13(double *state, double *unused, double *out_6998539107268807122);
void pose_H_13(double *state, double *unused, double *out_9121694605713880887);
void pose_h_14(double *state, double *unused, double *out_1892429868369893879);
void pose_H_14(double *state, double *unused, double *out_5677659116018454329);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}