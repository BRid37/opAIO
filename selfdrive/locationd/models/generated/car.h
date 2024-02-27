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
void car_err_fun(double *nom_x, double *delta_x, double *out_34046400755081495);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_850021188600913070);
void car_H_mod_fun(double *state, double *out_8260196495078253117);
void car_f_fun(double *state, double dt, double *out_6467803478925835161);
void car_F_fun(double *state, double dt, double *out_4289396415692727330);
void car_h_25(double *state, double *unused, double *out_6872809012467904931);
void car_H_25(double *state, double *unused, double *out_3228619721580075227);
void car_h_24(double *state, double *unused, double *out_5437912013156096213);
void car_H_24(double *state, double *unused, double *out_7975129048546584261);
void car_h_30(double *state, double *unused, double *out_1767068464250636953);
void car_H_30(double *state, double *unused, double *out_3688070619911541528);
void car_h_26(double *state, double *unused, double *out_4042597281863689087);
void car_H_26(double *state, double *unused, double *out_6970123040454131451);
void car_h_27(double *state, double *unused, double *out_3456535722818834915);
void car_H_27(double *state, double *unused, double *out_1513307308111116617);
void car_h_29(double *state, double *unused, double *out_8022893186209684207);
void car_H_29(double *state, double *unused, double *out_200055418758434416);
void car_h_28(double *state, double *unused, double *out_8458208990479680560);
void car_H_28(double *state, double *unused, double *out_5282454435827964990);
void car_h_31(double *state, double *unused, double *out_1008463638286144254);
void car_H_31(double *state, double *unused, double *out_3197973759703114799);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}