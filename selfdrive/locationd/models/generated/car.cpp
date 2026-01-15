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
void err_fun(double *nom_x, double *delta_x, double *out_5038973705749725969) {
   out_5038973705749725969[0] = delta_x[0] + nom_x[0];
   out_5038973705749725969[1] = delta_x[1] + nom_x[1];
   out_5038973705749725969[2] = delta_x[2] + nom_x[2];
   out_5038973705749725969[3] = delta_x[3] + nom_x[3];
   out_5038973705749725969[4] = delta_x[4] + nom_x[4];
   out_5038973705749725969[5] = delta_x[5] + nom_x[5];
   out_5038973705749725969[6] = delta_x[6] + nom_x[6];
   out_5038973705749725969[7] = delta_x[7] + nom_x[7];
   out_5038973705749725969[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_5775683794591023860) {
   out_5775683794591023860[0] = -nom_x[0] + true_x[0];
   out_5775683794591023860[1] = -nom_x[1] + true_x[1];
   out_5775683794591023860[2] = -nom_x[2] + true_x[2];
   out_5775683794591023860[3] = -nom_x[3] + true_x[3];
   out_5775683794591023860[4] = -nom_x[4] + true_x[4];
   out_5775683794591023860[5] = -nom_x[5] + true_x[5];
   out_5775683794591023860[6] = -nom_x[6] + true_x[6];
   out_5775683794591023860[7] = -nom_x[7] + true_x[7];
   out_5775683794591023860[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_4926761572782853817) {
   out_4926761572782853817[0] = 1.0;
   out_4926761572782853817[1] = 0.0;
   out_4926761572782853817[2] = 0.0;
   out_4926761572782853817[3] = 0.0;
   out_4926761572782853817[4] = 0.0;
   out_4926761572782853817[5] = 0.0;
   out_4926761572782853817[6] = 0.0;
   out_4926761572782853817[7] = 0.0;
   out_4926761572782853817[8] = 0.0;
   out_4926761572782853817[9] = 0.0;
   out_4926761572782853817[10] = 1.0;
   out_4926761572782853817[11] = 0.0;
   out_4926761572782853817[12] = 0.0;
   out_4926761572782853817[13] = 0.0;
   out_4926761572782853817[14] = 0.0;
   out_4926761572782853817[15] = 0.0;
   out_4926761572782853817[16] = 0.0;
   out_4926761572782853817[17] = 0.0;
   out_4926761572782853817[18] = 0.0;
   out_4926761572782853817[19] = 0.0;
   out_4926761572782853817[20] = 1.0;
   out_4926761572782853817[21] = 0.0;
   out_4926761572782853817[22] = 0.0;
   out_4926761572782853817[23] = 0.0;
   out_4926761572782853817[24] = 0.0;
   out_4926761572782853817[25] = 0.0;
   out_4926761572782853817[26] = 0.0;
   out_4926761572782853817[27] = 0.0;
   out_4926761572782853817[28] = 0.0;
   out_4926761572782853817[29] = 0.0;
   out_4926761572782853817[30] = 1.0;
   out_4926761572782853817[31] = 0.0;
   out_4926761572782853817[32] = 0.0;
   out_4926761572782853817[33] = 0.0;
   out_4926761572782853817[34] = 0.0;
   out_4926761572782853817[35] = 0.0;
   out_4926761572782853817[36] = 0.0;
   out_4926761572782853817[37] = 0.0;
   out_4926761572782853817[38] = 0.0;
   out_4926761572782853817[39] = 0.0;
   out_4926761572782853817[40] = 1.0;
   out_4926761572782853817[41] = 0.0;
   out_4926761572782853817[42] = 0.0;
   out_4926761572782853817[43] = 0.0;
   out_4926761572782853817[44] = 0.0;
   out_4926761572782853817[45] = 0.0;
   out_4926761572782853817[46] = 0.0;
   out_4926761572782853817[47] = 0.0;
   out_4926761572782853817[48] = 0.0;
   out_4926761572782853817[49] = 0.0;
   out_4926761572782853817[50] = 1.0;
   out_4926761572782853817[51] = 0.0;
   out_4926761572782853817[52] = 0.0;
   out_4926761572782853817[53] = 0.0;
   out_4926761572782853817[54] = 0.0;
   out_4926761572782853817[55] = 0.0;
   out_4926761572782853817[56] = 0.0;
   out_4926761572782853817[57] = 0.0;
   out_4926761572782853817[58] = 0.0;
   out_4926761572782853817[59] = 0.0;
   out_4926761572782853817[60] = 1.0;
   out_4926761572782853817[61] = 0.0;
   out_4926761572782853817[62] = 0.0;
   out_4926761572782853817[63] = 0.0;
   out_4926761572782853817[64] = 0.0;
   out_4926761572782853817[65] = 0.0;
   out_4926761572782853817[66] = 0.0;
   out_4926761572782853817[67] = 0.0;
   out_4926761572782853817[68] = 0.0;
   out_4926761572782853817[69] = 0.0;
   out_4926761572782853817[70] = 1.0;
   out_4926761572782853817[71] = 0.0;
   out_4926761572782853817[72] = 0.0;
   out_4926761572782853817[73] = 0.0;
   out_4926761572782853817[74] = 0.0;
   out_4926761572782853817[75] = 0.0;
   out_4926761572782853817[76] = 0.0;
   out_4926761572782853817[77] = 0.0;
   out_4926761572782853817[78] = 0.0;
   out_4926761572782853817[79] = 0.0;
   out_4926761572782853817[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_6329062410056106380) {
   out_6329062410056106380[0] = state[0];
   out_6329062410056106380[1] = state[1];
   out_6329062410056106380[2] = state[2];
   out_6329062410056106380[3] = state[3];
   out_6329062410056106380[4] = state[4];
   out_6329062410056106380[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_6329062410056106380[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_6329062410056106380[7] = state[7];
   out_6329062410056106380[8] = state[8];
}
void F_fun(double *state, double dt, double *out_922264769340125727) {
   out_922264769340125727[0] = 1;
   out_922264769340125727[1] = 0;
   out_922264769340125727[2] = 0;
   out_922264769340125727[3] = 0;
   out_922264769340125727[4] = 0;
   out_922264769340125727[5] = 0;
   out_922264769340125727[6] = 0;
   out_922264769340125727[7] = 0;
   out_922264769340125727[8] = 0;
   out_922264769340125727[9] = 0;
   out_922264769340125727[10] = 1;
   out_922264769340125727[11] = 0;
   out_922264769340125727[12] = 0;
   out_922264769340125727[13] = 0;
   out_922264769340125727[14] = 0;
   out_922264769340125727[15] = 0;
   out_922264769340125727[16] = 0;
   out_922264769340125727[17] = 0;
   out_922264769340125727[18] = 0;
   out_922264769340125727[19] = 0;
   out_922264769340125727[20] = 1;
   out_922264769340125727[21] = 0;
   out_922264769340125727[22] = 0;
   out_922264769340125727[23] = 0;
   out_922264769340125727[24] = 0;
   out_922264769340125727[25] = 0;
   out_922264769340125727[26] = 0;
   out_922264769340125727[27] = 0;
   out_922264769340125727[28] = 0;
   out_922264769340125727[29] = 0;
   out_922264769340125727[30] = 1;
   out_922264769340125727[31] = 0;
   out_922264769340125727[32] = 0;
   out_922264769340125727[33] = 0;
   out_922264769340125727[34] = 0;
   out_922264769340125727[35] = 0;
   out_922264769340125727[36] = 0;
   out_922264769340125727[37] = 0;
   out_922264769340125727[38] = 0;
   out_922264769340125727[39] = 0;
   out_922264769340125727[40] = 1;
   out_922264769340125727[41] = 0;
   out_922264769340125727[42] = 0;
   out_922264769340125727[43] = 0;
   out_922264769340125727[44] = 0;
   out_922264769340125727[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_922264769340125727[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_922264769340125727[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_922264769340125727[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_922264769340125727[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_922264769340125727[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_922264769340125727[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_922264769340125727[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_922264769340125727[53] = -9.8100000000000005*dt;
   out_922264769340125727[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_922264769340125727[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_922264769340125727[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_922264769340125727[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_922264769340125727[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_922264769340125727[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_922264769340125727[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_922264769340125727[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_922264769340125727[62] = 0;
   out_922264769340125727[63] = 0;
   out_922264769340125727[64] = 0;
   out_922264769340125727[65] = 0;
   out_922264769340125727[66] = 0;
   out_922264769340125727[67] = 0;
   out_922264769340125727[68] = 0;
   out_922264769340125727[69] = 0;
   out_922264769340125727[70] = 1;
   out_922264769340125727[71] = 0;
   out_922264769340125727[72] = 0;
   out_922264769340125727[73] = 0;
   out_922264769340125727[74] = 0;
   out_922264769340125727[75] = 0;
   out_922264769340125727[76] = 0;
   out_922264769340125727[77] = 0;
   out_922264769340125727[78] = 0;
   out_922264769340125727[79] = 0;
   out_922264769340125727[80] = 1;
}
void h_25(double *state, double *unused, double *out_2976232889390128900) {
   out_2976232889390128900[0] = state[6];
}
void H_25(double *state, double *unused, double *out_8449742222772345494) {
   out_8449742222772345494[0] = 0;
   out_8449742222772345494[1] = 0;
   out_8449742222772345494[2] = 0;
   out_8449742222772345494[3] = 0;
   out_8449742222772345494[4] = 0;
   out_8449742222772345494[5] = 0;
   out_8449742222772345494[6] = 1;
   out_8449742222772345494[7] = 0;
   out_8449742222772345494[8] = 0;
}
void h_24(double *state, double *unused, double *out_5313149587106084559) {
   out_5313149587106084559[0] = state[4];
   out_5313149587106084559[1] = state[5];
}
void H_24(double *state, double *unused, double *out_6439076252134882986) {
   out_6439076252134882986[0] = 0;
   out_6439076252134882986[1] = 0;
   out_6439076252134882986[2] = 0;
   out_6439076252134882986[3] = 0;
   out_6439076252134882986[4] = 1;
   out_6439076252134882986[5] = 0;
   out_6439076252134882986[6] = 0;
   out_6439076252134882986[7] = 0;
   out_6439076252134882986[8] = 0;
   out_6439076252134882986[9] = 0;
   out_6439076252134882986[10] = 0;
   out_6439076252134882986[11] = 0;
   out_6439076252134882986[12] = 0;
   out_6439076252134882986[13] = 0;
   out_6439076252134882986[14] = 1;
   out_6439076252134882986[15] = 0;
   out_6439076252134882986[16] = 0;
   out_6439076252134882986[17] = 0;
}
void h_30(double *state, double *unused, double *out_8699675957969071780) {
   out_8699675957969071780[0] = state[4];
}
void H_30(double *state, double *unused, double *out_7478668892429957495) {
   out_7478668892429957495[0] = 0;
   out_7478668892429957495[1] = 0;
   out_7478668892429957495[2] = 0;
   out_7478668892429957495[3] = 0;
   out_7478668892429957495[4] = 1;
   out_7478668892429957495[5] = 0;
   out_7478668892429957495[6] = 0;
   out_7478668892429957495[7] = 0;
   out_7478668892429957495[8] = 0;
}
void h_26(double *state, double *unused, double *out_96633506296925360) {
   out_96633506296925360[0] = state[7];
}
void H_26(double *state, double *unused, double *out_4708238903898289270) {
   out_4708238903898289270[0] = 0;
   out_4708238903898289270[1] = 0;
   out_4708238903898289270[2] = 0;
   out_4708238903898289270[3] = 0;
   out_4708238903898289270[4] = 0;
   out_4708238903898289270[5] = 0;
   out_4708238903898289270[6] = 0;
   out_4708238903898289270[7] = 1;
   out_4708238903898289270[8] = 0;
}
void h_27(double *state, double *unused, double *out_8461316920730961355) {
   out_8461316920730961355[0] = state[3];
}
void H_27(double *state, double *unused, double *out_5255074821246014278) {
   out_5255074821246014278[0] = 0;
   out_5255074821246014278[1] = 0;
   out_5255074821246014278[2] = 0;
   out_5255074821246014278[3] = 1;
   out_5255074821246014278[4] = 0;
   out_5255074821246014278[5] = 0;
   out_5255074821246014278[6] = 0;
   out_5255074821246014278[7] = 0;
   out_5255074821246014278[8] = 0;
}
void h_29(double *state, double *unused, double *out_5887123854699218397) {
   out_5887123854699218397[0] = state[1];
}
void H_29(double *state, double *unused, double *out_6968437548115565311) {
   out_6968437548115565311[0] = 0;
   out_6968437548115565311[1] = 1;
   out_6968437548115565311[2] = 0;
   out_6968437548115565311[3] = 0;
   out_6968437548115565311[4] = 0;
   out_6968437548115565311[5] = 0;
   out_6968437548115565311[6] = 0;
   out_6968437548115565311[7] = 0;
   out_6968437548115565311[8] = 0;
}
void h_28(double *state, double *unused, double *out_3316426857615313818) {
   out_3316426857615313818[0] = state[0];
}
void H_28(double *state, double *unused, double *out_6395907508524455731) {
   out_6395907508524455731[0] = 1;
   out_6395907508524455731[1] = 0;
   out_6395907508524455731[2] = 0;
   out_6395907508524455731[3] = 0;
   out_6395907508524455731[4] = 0;
   out_6395907508524455731[5] = 0;
   out_6395907508524455731[6] = 0;
   out_6395907508524455731[7] = 0;
   out_6395907508524455731[8] = 0;
}
void h_31(double *state, double *unused, double *out_6613682417644151250) {
   out_6613682417644151250[0] = state[8];
}
void H_31(double *state, double *unused, double *out_8480388184649305922) {
   out_8480388184649305922[0] = 0;
   out_8480388184649305922[1] = 0;
   out_8480388184649305922[2] = 0;
   out_8480388184649305922[3] = 0;
   out_8480388184649305922[4] = 0;
   out_8480388184649305922[5] = 0;
   out_8480388184649305922[6] = 0;
   out_8480388184649305922[7] = 0;
   out_8480388184649305922[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_5038973705749725969) {
  err_fun(nom_x, delta_x, out_5038973705749725969);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_5775683794591023860) {
  inv_err_fun(nom_x, true_x, out_5775683794591023860);
}
void car_H_mod_fun(double *state, double *out_4926761572782853817) {
  H_mod_fun(state, out_4926761572782853817);
}
void car_f_fun(double *state, double dt, double *out_6329062410056106380) {
  f_fun(state,  dt, out_6329062410056106380);
}
void car_F_fun(double *state, double dt, double *out_922264769340125727) {
  F_fun(state,  dt, out_922264769340125727);
}
void car_h_25(double *state, double *unused, double *out_2976232889390128900) {
  h_25(state, unused, out_2976232889390128900);
}
void car_H_25(double *state, double *unused, double *out_8449742222772345494) {
  H_25(state, unused, out_8449742222772345494);
}
void car_h_24(double *state, double *unused, double *out_5313149587106084559) {
  h_24(state, unused, out_5313149587106084559);
}
void car_H_24(double *state, double *unused, double *out_6439076252134882986) {
  H_24(state, unused, out_6439076252134882986);
}
void car_h_30(double *state, double *unused, double *out_8699675957969071780) {
  h_30(state, unused, out_8699675957969071780);
}
void car_H_30(double *state, double *unused, double *out_7478668892429957495) {
  H_30(state, unused, out_7478668892429957495);
}
void car_h_26(double *state, double *unused, double *out_96633506296925360) {
  h_26(state, unused, out_96633506296925360);
}
void car_H_26(double *state, double *unused, double *out_4708238903898289270) {
  H_26(state, unused, out_4708238903898289270);
}
void car_h_27(double *state, double *unused, double *out_8461316920730961355) {
  h_27(state, unused, out_8461316920730961355);
}
void car_H_27(double *state, double *unused, double *out_5255074821246014278) {
  H_27(state, unused, out_5255074821246014278);
}
void car_h_29(double *state, double *unused, double *out_5887123854699218397) {
  h_29(state, unused, out_5887123854699218397);
}
void car_H_29(double *state, double *unused, double *out_6968437548115565311) {
  H_29(state, unused, out_6968437548115565311);
}
void car_h_28(double *state, double *unused, double *out_3316426857615313818) {
  h_28(state, unused, out_3316426857615313818);
}
void car_H_28(double *state, double *unused, double *out_6395907508524455731) {
  H_28(state, unused, out_6395907508524455731);
}
void car_h_31(double *state, double *unused, double *out_6613682417644151250) {
  h_31(state, unused, out_6613682417644151250);
}
void car_H_31(double *state, double *unused, double *out_8480388184649305922) {
  H_31(state, unused, out_8480388184649305922);
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
