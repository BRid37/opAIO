#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_4317960585787832547);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_8646049298616345457);
void pose_H_mod_fun(double *state, double *out_3862875448409277979);
void pose_f_fun(double *state, double dt, double *out_4189184797940026891);
void pose_F_fun(double *state, double dt, double *out_92299593068743238);
void pose_h_4(double *state, double *unused, double *out_40016825818469097);
void pose_H_4(double *state, double *unused, double *out_7137097527200227232);
void pose_h_10(double *state, double *unused, double *out_8717338601611353402);
void pose_H_10(double *state, double *unused, double *out_3547541820256081924);
void pose_h_13(double *state, double *unused, double *out_3019458539864484205);
void pose_H_13(double *state, double *unused, double *out_3924823701867894431);
void pose_h_14(double *state, double *unused, double *out_925858555095681395);
void pose_H_14(double *state, double *unused, double *out_3173856670860742703);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}