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
void car_err_fun(double *nom_x, double *delta_x, double *out_6783467077667434630);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_1548798352077342066);
void car_H_mod_fun(double *state, double *out_9027514241624118734);
void car_f_fun(double *state, double dt, double *out_2940164949098632235);
void car_F_fun(double *state, double dt, double *out_7550368536012780688);
void car_h_25(double *state, double *unused, double *out_7957612541418705405);
void car_H_25(double *state, double *unused, double *out_677145842797290289);
void car_h_24(double *state, double *unused, double *out_8831627388895325945);
void car_H_24(double *state, double *unused, double *out_2902853626776158851);
void car_h_30(double *state, double *unused, double *out_7499411179260143743);
void car_H_30(double *state, double *unused, double *out_7593836184288907044);
void car_h_26(double *state, double *unused, double *out_6896095294583666226);
void car_H_26(double *state, double *unused, double *out_3064357476076765935);
void car_h_27(double *state, double *unused, double *out_5487458264630000566);
void car_H_27(double *state, double *unused, double *out_5419072872488482133);
void car_h_29(double *state, double *unused, double *out_1625774788201498914);
void car_H_29(double *state, double *unused, double *out_8104067528603299228);
void car_h_28(double *state, double *unused, double *out_6430968117531663001);
void car_H_28(double *state, double *unused, double *out_3021668511533768654);
void car_h_31(double *state, double *unused, double *out_2725866275470173770);
void car_H_31(double *state, double *unused, double *out_707791804674250717);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}