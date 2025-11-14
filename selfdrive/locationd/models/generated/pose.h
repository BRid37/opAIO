#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_2671738792046849383);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_424188773766453759);
void pose_H_mod_fun(double *state, double *out_7263482371397085867);
void pose_f_fun(double *state, double dt, double *out_5712205142337176613);
void pose_F_fun(double *state, double dt, double *out_3453992788886440929);
void pose_h_4(double *state, double *unused, double *out_2219177127358835334);
void pose_H_4(double *state, double *unused, double *out_3491675161553178295);
void pose_h_10(double *state, double *unused, double *out_587419100042313946);
void pose_H_10(double *state, double *unused, double *out_7812932492250781234);
void pose_h_13(double *state, double *unused, double *out_7036493165250912321);
void pose_H_13(double *state, double *unused, double *out_4118956046763522634);
void pose_h_14(double *state, double *unused, double *out_5223014531241664562);
void pose_H_14(double *state, double *unused, double *out_6574463593848550591);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}