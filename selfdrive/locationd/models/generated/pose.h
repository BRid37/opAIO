#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_1454459679057110584);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_8466886164721569510);
void pose_H_mod_fun(double *state, double *out_6891492054151298461);
void pose_f_fun(double *state, double dt, double *out_6198631950895505143);
void pose_F_fun(double *state, double dt, double *out_5188989910390169613);
void pose_h_4(double *state, double *unused, double *out_3185427494971646342);
void pose_H_4(double *state, double *unused, double *out_7645653056206011068);
void pose_h_10(double *state, double *unused, double *out_8120018998606381774);
void pose_H_10(double *state, double *unused, double *out_2849047297491274617);
void pose_h_13(double *state, double *unused, double *out_8173327387295448263);
void pose_H_13(double *state, double *unused, double *out_7588817192171207747);
void pose_h_14(double *state, double *unused, double *out_2707962449685458083);
void pose_H_14(double *state, double *unused, double *out_6837850161164056019);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}