#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_2544821064399858965) {
   out_2544821064399858965[0] = delta_x[0] + nom_x[0];
   out_2544821064399858965[1] = delta_x[1] + nom_x[1];
   out_2544821064399858965[2] = delta_x[2] + nom_x[2];
   out_2544821064399858965[3] = delta_x[3] + nom_x[3];
   out_2544821064399858965[4] = delta_x[4] + nom_x[4];
   out_2544821064399858965[5] = delta_x[5] + nom_x[5];
   out_2544821064399858965[6] = delta_x[6] + nom_x[6];
   out_2544821064399858965[7] = delta_x[7] + nom_x[7];
   out_2544821064399858965[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_6367162327906013787) {
   out_6367162327906013787[0] = -nom_x[0] + true_x[0];
   out_6367162327906013787[1] = -nom_x[1] + true_x[1];
   out_6367162327906013787[2] = -nom_x[2] + true_x[2];
   out_6367162327906013787[3] = -nom_x[3] + true_x[3];
   out_6367162327906013787[4] = -nom_x[4] + true_x[4];
   out_6367162327906013787[5] = -nom_x[5] + true_x[5];
   out_6367162327906013787[6] = -nom_x[6] + true_x[6];
   out_6367162327906013787[7] = -nom_x[7] + true_x[7];
   out_6367162327906013787[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_2103091097720413186) {
   out_2103091097720413186[0] = 1.0;
   out_2103091097720413186[1] = 0.0;
   out_2103091097720413186[2] = 0.0;
   out_2103091097720413186[3] = 0.0;
   out_2103091097720413186[4] = 0.0;
   out_2103091097720413186[5] = 0.0;
   out_2103091097720413186[6] = 0.0;
   out_2103091097720413186[7] = 0.0;
   out_2103091097720413186[8] = 0.0;
   out_2103091097720413186[9] = 0.0;
   out_2103091097720413186[10] = 1.0;
   out_2103091097720413186[11] = 0.0;
   out_2103091097720413186[12] = 0.0;
   out_2103091097720413186[13] = 0.0;
   out_2103091097720413186[14] = 0.0;
   out_2103091097720413186[15] = 0.0;
   out_2103091097720413186[16] = 0.0;
   out_2103091097720413186[17] = 0.0;
   out_2103091097720413186[18] = 0.0;
   out_2103091097720413186[19] = 0.0;
   out_2103091097720413186[20] = 1.0;
   out_2103091097720413186[21] = 0.0;
   out_2103091097720413186[22] = 0.0;
   out_2103091097720413186[23] = 0.0;
   out_2103091097720413186[24] = 0.0;
   out_2103091097720413186[25] = 0.0;
   out_2103091097720413186[26] = 0.0;
   out_2103091097720413186[27] = 0.0;
   out_2103091097720413186[28] = 0.0;
   out_2103091097720413186[29] = 0.0;
   out_2103091097720413186[30] = 1.0;
   out_2103091097720413186[31] = 0.0;
   out_2103091097720413186[32] = 0.0;
   out_2103091097720413186[33] = 0.0;
   out_2103091097720413186[34] = 0.0;
   out_2103091097720413186[35] = 0.0;
   out_2103091097720413186[36] = 0.0;
   out_2103091097720413186[37] = 0.0;
   out_2103091097720413186[38] = 0.0;
   out_2103091097720413186[39] = 0.0;
   out_2103091097720413186[40] = 1.0;
   out_2103091097720413186[41] = 0.0;
   out_2103091097720413186[42] = 0.0;
   out_2103091097720413186[43] = 0.0;
   out_2103091097720413186[44] = 0.0;
   out_2103091097720413186[45] = 0.0;
   out_2103091097720413186[46] = 0.0;
   out_2103091097720413186[47] = 0.0;
   out_2103091097720413186[48] = 0.0;
   out_2103091097720413186[49] = 0.0;
   out_2103091097720413186[50] = 1.0;
   out_2103091097720413186[51] = 0.0;
   out_2103091097720413186[52] = 0.0;
   out_2103091097720413186[53] = 0.0;
   out_2103091097720413186[54] = 0.0;
   out_2103091097720413186[55] = 0.0;
   out_2103091097720413186[56] = 0.0;
   out_2103091097720413186[57] = 0.0;
   out_2103091097720413186[58] = 0.0;
   out_2103091097720413186[59] = 0.0;
   out_2103091097720413186[60] = 1.0;
   out_2103091097720413186[61] = 0.0;
   out_2103091097720413186[62] = 0.0;
   out_2103091097720413186[63] = 0.0;
   out_2103091097720413186[64] = 0.0;
   out_2103091097720413186[65] = 0.0;
   out_2103091097720413186[66] = 0.0;
   out_2103091097720413186[67] = 0.0;
   out_2103091097720413186[68] = 0.0;
   out_2103091097720413186[69] = 0.0;
   out_2103091097720413186[70] = 1.0;
   out_2103091097720413186[71] = 0.0;
   out_2103091097720413186[72] = 0.0;
   out_2103091097720413186[73] = 0.0;
   out_2103091097720413186[74] = 0.0;
   out_2103091097720413186[75] = 0.0;
   out_2103091097720413186[76] = 0.0;
   out_2103091097720413186[77] = 0.0;
   out_2103091097720413186[78] = 0.0;
   out_2103091097720413186[79] = 0.0;
   out_2103091097720413186[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_3409469352841446417) {
   out_3409469352841446417[0] = state[0];
   out_3409469352841446417[1] = state[1];
   out_3409469352841446417[2] = state[2];
   out_3409469352841446417[3] = state[3];
   out_3409469352841446417[4] = state[4];
   out_3409469352841446417[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_3409469352841446417[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_3409469352841446417[7] = state[7];
   out_3409469352841446417[8] = state[8];
}
void F_fun(double *state, double dt, double *out_5618527830171991882) {
   out_5618527830171991882[0] = 1;
   out_5618527830171991882[1] = 0;
   out_5618527830171991882[2] = 0;
   out_5618527830171991882[3] = 0;
   out_5618527830171991882[4] = 0;
   out_5618527830171991882[5] = 0;
   out_5618527830171991882[6] = 0;
   out_5618527830171991882[7] = 0;
   out_5618527830171991882[8] = 0;
   out_5618527830171991882[9] = 0;
   out_5618527830171991882[10] = 1;
   out_5618527830171991882[11] = 0;
   out_5618527830171991882[12] = 0;
   out_5618527830171991882[13] = 0;
   out_5618527830171991882[14] = 0;
   out_5618527830171991882[15] = 0;
   out_5618527830171991882[16] = 0;
   out_5618527830171991882[17] = 0;
   out_5618527830171991882[18] = 0;
   out_5618527830171991882[19] = 0;
   out_5618527830171991882[20] = 1;
   out_5618527830171991882[21] = 0;
   out_5618527830171991882[22] = 0;
   out_5618527830171991882[23] = 0;
   out_5618527830171991882[24] = 0;
   out_5618527830171991882[25] = 0;
   out_5618527830171991882[26] = 0;
   out_5618527830171991882[27] = 0;
   out_5618527830171991882[28] = 0;
   out_5618527830171991882[29] = 0;
   out_5618527830171991882[30] = 1;
   out_5618527830171991882[31] = 0;
   out_5618527830171991882[32] = 0;
   out_5618527830171991882[33] = 0;
   out_5618527830171991882[34] = 0;
   out_5618527830171991882[35] = 0;
   out_5618527830171991882[36] = 0;
   out_5618527830171991882[37] = 0;
   out_5618527830171991882[38] = 0;
   out_5618527830171991882[39] = 0;
   out_5618527830171991882[40] = 1;
   out_5618527830171991882[41] = 0;
   out_5618527830171991882[42] = 0;
   out_5618527830171991882[43] = 0;
   out_5618527830171991882[44] = 0;
   out_5618527830171991882[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_5618527830171991882[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_5618527830171991882[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_5618527830171991882[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_5618527830171991882[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_5618527830171991882[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_5618527830171991882[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_5618527830171991882[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_5618527830171991882[53] = -9.8000000000000007*dt;
   out_5618527830171991882[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_5618527830171991882[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_5618527830171991882[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_5618527830171991882[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_5618527830171991882[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_5618527830171991882[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_5618527830171991882[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_5618527830171991882[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_5618527830171991882[62] = 0;
   out_5618527830171991882[63] = 0;
   out_5618527830171991882[64] = 0;
   out_5618527830171991882[65] = 0;
   out_5618527830171991882[66] = 0;
   out_5618527830171991882[67] = 0;
   out_5618527830171991882[68] = 0;
   out_5618527830171991882[69] = 0;
   out_5618527830171991882[70] = 1;
   out_5618527830171991882[71] = 0;
   out_5618527830171991882[72] = 0;
   out_5618527830171991882[73] = 0;
   out_5618527830171991882[74] = 0;
   out_5618527830171991882[75] = 0;
   out_5618527830171991882[76] = 0;
   out_5618527830171991882[77] = 0;
   out_5618527830171991882[78] = 0;
   out_5618527830171991882[79] = 0;
   out_5618527830171991882[80] = 1;
}
void h_25(double *state, double *unused, double *out_2067803326384484466) {
   out_2067803326384484466[0] = state[6];
}
void H_25(double *state, double *unused, double *out_8600114057610443137) {
   out_8600114057610443137[0] = 0;
   out_8600114057610443137[1] = 0;
   out_8600114057610443137[2] = 0;
   out_8600114057610443137[3] = 0;
   out_8600114057610443137[4] = 0;
   out_8600114057610443137[5] = 0;
   out_8600114057610443137[6] = 1;
   out_8600114057610443137[7] = 0;
   out_8600114057610443137[8] = 0;
}
void h_24(double *state, double *unused, double *out_8720211228654265950) {
   out_8720211228654265950[0] = state[4];
   out_8720211228654265950[1] = state[5];
}
void H_24(double *state, double *unused, double *out_4977815151071401627) {
   out_4977815151071401627[0] = 0;
   out_4977815151071401627[1] = 0;
   out_4977815151071401627[2] = 0;
   out_4977815151071401627[3] = 0;
   out_4977815151071401627[4] = 1;
   out_4977815151071401627[5] = 0;
   out_4977815151071401627[6] = 0;
   out_4977815151071401627[7] = 0;
   out_4977815151071401627[8] = 0;
   out_4977815151071401627[9] = 0;
   out_4977815151071401627[10] = 0;
   out_4977815151071401627[11] = 0;
   out_4977815151071401627[12] = 0;
   out_4977815151071401627[13] = 0;
   out_4977815151071401627[14] = 1;
   out_4977815151071401627[15] = 0;
   out_4977815151071401627[16] = 0;
   out_4977815151071401627[17] = 0;
}
void h_30(double *state, double *unused, double *out_8431397304686300327) {
   out_8431397304686300327[0] = state[4];
}
void H_30(double *state, double *unused, double *out_5318933685971500281) {
   out_5318933685971500281[0] = 0;
   out_5318933685971500281[1] = 0;
   out_5318933685971500281[2] = 0;
   out_5318933685971500281[3] = 0;
   out_5318933685971500281[4] = 1;
   out_5318933685971500281[5] = 0;
   out_5318933685971500281[6] = 0;
   out_5318933685971500281[7] = 0;
   out_5318933685971500281[8] = 0;
}
void h_26(double *state, double *unused, double *out_3429724037025454682) {
   out_3429724037025454682[0] = state[7];
}
void H_26(double *state, double *unused, double *out_6105126697225052255) {
   out_6105126697225052255[0] = 0;
   out_6105126697225052255[1] = 0;
   out_6105126697225052255[2] = 0;
   out_6105126697225052255[3] = 0;
   out_6105126697225052255[4] = 0;
   out_6105126697225052255[5] = 0;
   out_6105126697225052255[6] = 0;
   out_6105126697225052255[7] = 1;
   out_6105126697225052255[8] = 0;
}
void h_27(double *state, double *unused, double *out_3498297857676025399) {
   out_3498297857676025399[0] = state[3];
}
void H_27(double *state, double *unused, double *out_7542527757155443498) {
   out_7542527757155443498[0] = 0;
   out_7542527757155443498[1] = 0;
   out_7542527757155443498[2] = 0;
   out_7542527757155443498[3] = 1;
   out_7542527757155443498[4] = 0;
   out_7542527757155443498[5] = 0;
   out_7542527757155443498[6] = 0;
   out_7542527757155443498[7] = 0;
   out_7542527757155443498[8] = 0;
}
void h_29(double *state, double *unused, double *out_550571867320540438) {
   out_550571867320540438[0] = state[1];
}
void H_29(double *state, double *unused, double *out_5829165030285892465) {
   out_5829165030285892465[0] = 0;
   out_5829165030285892465[1] = 1;
   out_5829165030285892465[2] = 0;
   out_5829165030285892465[3] = 0;
   out_5829165030285892465[4] = 0;
   out_5829165030285892465[5] = 0;
   out_5829165030285892465[6] = 0;
   out_5829165030285892465[7] = 0;
   out_5829165030285892465[8] = 0;
}
void h_28(double *state, double *unused, double *out_6310849960945878782) {
   out_6310849960945878782[0] = state[0];
}
void H_28(double *state, double *unused, double *out_746766013216361891) {
   out_746766013216361891[0] = 1;
   out_746766013216361891[1] = 0;
   out_746766013216361891[2] = 0;
   out_746766013216361891[3] = 0;
   out_746766013216361891[4] = 0;
   out_746766013216361891[5] = 0;
   out_746766013216361891[6] = 0;
   out_746766013216361891[7] = 0;
   out_746766013216361891[8] = 0;
}
void h_31(double *state, double *unused, double *out_7739063270606525266) {
   out_7739063270606525266[0] = state[8];
}
void H_31(double *state, double *unused, double *out_8569468095733482709) {
   out_8569468095733482709[0] = 0;
   out_8569468095733482709[1] = 0;
   out_8569468095733482709[2] = 0;
   out_8569468095733482709[3] = 0;
   out_8569468095733482709[4] = 0;
   out_8569468095733482709[5] = 0;
   out_8569468095733482709[6] = 0;
   out_8569468095733482709[7] = 0;
   out_8569468095733482709[8] = 1;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_2544821064399858965) {
  err_fun(nom_x, delta_x, out_2544821064399858965);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_6367162327906013787) {
  inv_err_fun(nom_x, true_x, out_6367162327906013787);
}
void car_H_mod_fun(double *state, double *out_2103091097720413186) {
  H_mod_fun(state, out_2103091097720413186);
}
void car_f_fun(double *state, double dt, double *out_3409469352841446417) {
  f_fun(state,  dt, out_3409469352841446417);
}
void car_F_fun(double *state, double dt, double *out_5618527830171991882) {
  F_fun(state,  dt, out_5618527830171991882);
}
void car_h_25(double *state, double *unused, double *out_2067803326384484466) {
  h_25(state, unused, out_2067803326384484466);
}
void car_H_25(double *state, double *unused, double *out_8600114057610443137) {
  H_25(state, unused, out_8600114057610443137);
}
void car_h_24(double *state, double *unused, double *out_8720211228654265950) {
  h_24(state, unused, out_8720211228654265950);
}
void car_H_24(double *state, double *unused, double *out_4977815151071401627) {
  H_24(state, unused, out_4977815151071401627);
}
void car_h_30(double *state, double *unused, double *out_8431397304686300327) {
  h_30(state, unused, out_8431397304686300327);
}
void car_H_30(double *state, double *unused, double *out_5318933685971500281) {
  H_30(state, unused, out_5318933685971500281);
}
void car_h_26(double *state, double *unused, double *out_3429724037025454682) {
  h_26(state, unused, out_3429724037025454682);
}
void car_H_26(double *state, double *unused, double *out_6105126697225052255) {
  H_26(state, unused, out_6105126697225052255);
}
void car_h_27(double *state, double *unused, double *out_3498297857676025399) {
  h_27(state, unused, out_3498297857676025399);
}
void car_H_27(double *state, double *unused, double *out_7542527757155443498) {
  H_27(state, unused, out_7542527757155443498);
}
void car_h_29(double *state, double *unused, double *out_550571867320540438) {
  h_29(state, unused, out_550571867320540438);
}
void car_H_29(double *state, double *unused, double *out_5829165030285892465) {
  H_29(state, unused, out_5829165030285892465);
}
void car_h_28(double *state, double *unused, double *out_6310849960945878782) {
  h_28(state, unused, out_6310849960945878782);
}
void car_H_28(double *state, double *unused, double *out_746766013216361891) {
  H_28(state, unused, out_746766013216361891);
}
void car_h_31(double *state, double *unused, double *out_7739063270606525266) {
  h_31(state, unused, out_7739063270606525266);
}
void car_H_31(double *state, double *unused, double *out_8569468095733482709) {
  H_31(state, unused, out_8569468095733482709);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_lib_init(car)
