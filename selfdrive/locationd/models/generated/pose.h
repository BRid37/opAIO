#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_7790108905973441094);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_3044307321253503213);
void pose_H_mod_fun(double *state, double *out_2507391073749515951);
void pose_f_fun(double *state, double dt, double *out_8106374632162380060);
void pose_F_fun(double *state, double dt, double *out_8926088300008410432);
void pose_h_4(double *state, double *unused, double *out_439005716197027433);
void pose_H_4(double *state, double *unused, double *out_6358336940791637735);
void pose_h_10(double *state, double *unused, double *out_7231930289041195534);
void pose_H_10(double *state, double *unused, double *out_584809807697225583);
void pose_h_13(double *state, double *unused, double *out_6287159899549881063);
void pose_H_13(double *state, double *unused, double *out_3146063115459304934);
void pose_h_14(double *state, double *unused, double *out_8265255736014954242);
void pose_H_14(double *state, double *unused, double *out_2395096084452153206);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}