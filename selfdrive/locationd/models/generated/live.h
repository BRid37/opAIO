#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void live_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_9(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_12(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_35(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_32(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_33(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_H(double *in_vec, double *out_555920766853113330);
void live_err_fun(double *nom_x, double *delta_x, double *out_2289805703380240820);
void live_inv_err_fun(double *nom_x, double *true_x, double *out_1768766727819692339);
void live_H_mod_fun(double *state, double *out_230355854465288429);
void live_f_fun(double *state, double dt, double *out_7553074372073391373);
void live_F_fun(double *state, double dt, double *out_2530825727336270814);
void live_h_4(double *state, double *unused, double *out_7454641892853015266);
void live_H_4(double *state, double *unused, double *out_5393262002326411523);
void live_h_9(double *state, double *unused, double *out_5986509466495433561);
void live_H_9(double *state, double *unused, double *out_8896314335028362610);
void live_h_10(double *state, double *unused, double *out_8065441711506535109);
void live_H_10(double *state, double *unused, double *out_5357319222954812274);
void live_h_12(double *state, double *unused, double *out_8381920569000431131);
void live_H_12(double *state, double *unused, double *out_4772162977278817856);
void live_h_35(double *state, double *unused, double *out_5064657568800652175);
void live_H_35(double *state, double *unused, double *out_2026599944953804147);
void live_h_32(double *state, double *unused, double *out_312854888681221563);
void live_H_32(double *state, double *unused, double *out_6367604720686911035);
void live_h_13(double *state, double *unused, double *out_6714267379198233586);
void live_H_13(double *state, double *unused, double *out_6226310291469191509);
void live_h_14(double *state, double *unused, double *out_5986509466495433561);
void live_H_14(double *state, double *unused, double *out_8896314335028362610);
void live_h_33(double *state, double *unused, double *out_2521557960636214487);
void live_H_33(double *state, double *unused, double *out_1123957059685053457);
void live_predict(double *in_x, double *in_P, double *in_Q, double dt);
}