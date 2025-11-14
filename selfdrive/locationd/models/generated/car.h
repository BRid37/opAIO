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
void car_err_fun(double *nom_x, double *delta_x, double *out_7892580644768456538);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_5204839923779822433);
void car_H_mod_fun(double *state, double *out_8344684464375028132);
void car_f_fun(double *state, double dt, double *out_2949132285120758150);
void car_F_fun(double *state, double dt, double *out_3845759010015306785);
void car_h_25(double *state, double *unused, double *out_5895820651173676631);
void car_H_25(double *state, double *unused, double *out_3605036649444493533);
void car_h_24(double *state, double *unused, double *out_482928573552333087);
void car_H_24(double *state, double *unused, double *out_3134579167401154809);
void car_h_30(double *state, double *unused, double *out_2258371122919654281);
void car_H_30(double *state, double *unused, double *out_3475697702301253463);
void car_h_26(double *state, double *unused, double *out_6723598049087186484);
void car_H_26(double *state, double *unused, double *out_136466669429562691);
void car_h_27(double *state, double *unused, double *out_8500225971982374282);
void car_H_27(double *state, double *unused, double *out_1300934390500828552);
void car_h_29(double *state, double *unused, double *out_2743302144741191364);
void car_H_29(double *state, double *unused, double *out_412428336368722481);
void car_h_28(double *state, double *unused, double *out_2511374667298476521);
void car_H_28(double *state, double *unused, double *out_5494827353438253055);
void car_h_31(double *state, double *unused, double *out_4669650771781825800);
void car_H_31(double *state, double *unused, double *out_3635682611321453961);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}