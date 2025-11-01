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
void live_H(double *in_vec, double *out_5502701555042538961);
void live_err_fun(double *nom_x, double *delta_x, double *out_137593102895844821);
void live_inv_err_fun(double *nom_x, double *true_x, double *out_4850106976963470914);
void live_H_mod_fun(double *state, double *out_8139048272057916544);
void live_f_fun(double *state, double dt, double *out_6705201773034606897);
void live_F_fun(double *state, double dt, double *out_4382539786688493844);
void live_h_4(double *state, double *unused, double *out_6295920157539101728);
void live_H_4(double *state, double *unused, double *out_6580843008519953105);
void live_h_9(double *state, double *unused, double *out_8976327083223584744);
void live_H_9(double *state, double *unused, double *out_6822032655149543750);
void live_h_10(double *state, double *unused, double *out_1998429403900924886);
void live_H_10(double *state, double *unused, double *out_2664004392150245590);
void live_h_12(double *state, double *unused, double *out_7018166226068267501);
void live_H_12(double *state, double *unused, double *out_6846444657157636716);
void live_h_35(double *state, double *unused, double *out_3498413995582333652);
void live_H_35(double *state, double *unused, double *out_8499239007816991135);
void live_h_32(double *state, double *unused, double *out_2426629480225487796);
void live_H_32(double *state, double *unused, double *out_3032640562198444125);
void live_h_13(double *state, double *unused, double *out_5180901663871748497);
void live_H_13(double *state, double *unused, double *out_2427562214110613682);
void live_h_14(double *state, double *unused, double *out_8976327083223584744);
void live_H_14(double *state, double *unused, double *out_6822032655149543750);
void live_h_33(double *state, double *unused, double *out_7972119317558266476);
void live_H_33(double *state, double *unused, double *out_5348682003178133531);
void live_predict(double *in_x, double *in_P, double *in_Q, double dt);
}