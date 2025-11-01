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
void car_err_fun(double *nom_x, double *delta_x, double *out_3141874777791540817);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_6267025797831989014);
void car_H_mod_fun(double *state, double *out_8546251037843938187);
void car_f_fun(double *state, double dt, double *out_4676653304140071128);
void car_F_fun(double *state, double dt, double *out_5759423222948201793);
void car_h_25(double *state, double *unused, double *out_2632078112158128114);
void car_H_25(double *state, double *unused, double *out_6546650973379865818);
void car_h_24(double *state, double *unused, double *out_543072649713852020);
void car_H_24(double *state, double *unused, double *out_2681414212689329407);
void car_h_30(double *state, double *unused, double *out_5929326820163108956);
void car_H_30(double *state, double *unused, double *out_6675989920523105888);
void car_h_26(double *state, double *unused, double *out_7515743985885597015);
void car_H_26(double *state, double *unused, double *out_8158589781455629574);
void car_h_27(double *state, double *unused, double *out_7018356497285426362);
void car_H_27(double *state, double *unused, double *out_8850753232323530799);
void car_h_29(double *state, double *unused, double *out_862909301444766233);
void car_H_29(double *state, double *unused, double *out_7882628114516469784);
void car_h_28(double *state, double *unused, double *out_2016683229624580717);
void car_H_28(double *state, double *unused, double *out_2800229097446939210);
void car_h_31(double *state, double *unused, double *out_8275634652905230363);
void car_H_31(double *state, double *unused, double *out_6516005011502905390);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}