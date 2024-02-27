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
void live_H(double *in_vec, double *out_2195801997734315225);
void live_err_fun(double *nom_x, double *delta_x, double *out_7885382450672140263);
void live_inv_err_fun(double *nom_x, double *true_x, double *out_8328284484611196913);
void live_H_mod_fun(double *state, double *out_6275450067896889819);
void live_f_fun(double *state, double dt, double *out_602314135086256032);
void live_F_fun(double *state, double dt, double *out_8785245154925367845);
void live_h_4(double *state, double *unused, double *out_6655938146560302661);
void live_H_4(double *state, double *unused, double *out_4586688220523086789);
void live_h_9(double *state, double *unused, double *out_4124840261630090276);
void live_H_9(double *state, double *unused, double *out_4345498573893496144);
void live_h_10(double *state, double *unused, double *out_3013628431158048691);
void live_H_10(double *state, double *unused, double *out_762581265572162243);
void live_h_12(double *state, double *unused, double *out_5169424638988699366);
void live_H_12(double *state, double *unused, double *out_432768187508875006);
void live_h_35(double *state, double *unused, double *out_7013680659001227585);
void live_H_35(double *state, double *unused, double *out_1220026163150479413);
void live_h_32(double *state, double *unused, double *out_4960927998102533383);
void live_H_32(double *state, double *unused, double *out_4581278209057133145);
void live_h_13(double *state, double *unused, double *out_8317077396153969626);
void live_H_13(double *state, double *unused, double *out_8621376804059329243);
void live_h_14(double *state, double *unused, double *out_4124840261630090276);
void live_H_14(double *state, double *unused, double *out_4345498573893496144);
void live_h_33(double *state, double *unused, double *out_6683315253473899657);
void live_H_33(double *state, double *unused, double *out_1930530841488378191);
void live_predict(double *in_x, double *in_P, double *in_Q, double dt);
}