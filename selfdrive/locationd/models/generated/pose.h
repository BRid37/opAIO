#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_4442264216625752623);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_8068876060036098661);
void pose_H_mod_fun(double *state, double *out_3914528363574678845);
void pose_f_fun(double *state, double dt, double *out_5861088598759542506);
void pose_F_fun(double *state, double dt, double *out_6415614808115414031);
void pose_h_4(double *state, double *unused, double *out_1046875653712579764);
void pose_H_4(double *state, double *unused, double *out_7188750442365628098);
void pose_h_10(double *state, double *unused, double *out_6939817699329021946);
void pose_H_10(double *state, double *unused, double *out_8722847441151408688);
void pose_h_13(double *state, double *unused, double *out_6853026663320228979);
void pose_H_13(double *state, double *unused, double *out_3976476617033295297);
void pose_h_14(double *state, double *unused, double *out_1334170023894757499);
void pose_H_14(double *state, double *unused, double *out_3225509586026143569);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}