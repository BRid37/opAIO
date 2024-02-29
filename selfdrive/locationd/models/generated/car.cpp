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
 *                       Code generated with SymPy 1.12                       *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_2839074644799155373) {
   out_2839074644799155373[0] = delta_x[0] + nom_x[0];
   out_2839074644799155373[1] = delta_x[1] + nom_x[1];
   out_2839074644799155373[2] = delta_x[2] + nom_x[2];
   out_2839074644799155373[3] = delta_x[3] + nom_x[3];
   out_2839074644799155373[4] = delta_x[4] + nom_x[4];
   out_2839074644799155373[5] = delta_x[5] + nom_x[5];
   out_2839074644799155373[6] = delta_x[6] + nom_x[6];
   out_2839074644799155373[7] = delta_x[7] + nom_x[7];
   out_2839074644799155373[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_2832413412600408261) {
   out_2832413412600408261[0] = -nom_x[0] + true_x[0];
   out_2832413412600408261[1] = -nom_x[1] + true_x[1];
   out_2832413412600408261[2] = -nom_x[2] + true_x[2];
   out_2832413412600408261[3] = -nom_x[3] + true_x[3];
   out_2832413412600408261[4] = -nom_x[4] + true_x[4];
   out_2832413412600408261[5] = -nom_x[5] + true_x[5];
   out_2832413412600408261[6] = -nom_x[6] + true_x[6];
   out_2832413412600408261[7] = -nom_x[7] + true_x[7];
   out_2832413412600408261[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_2434754126251583803) {
   out_2434754126251583803[0] = 1.0;
   out_2434754126251583803[1] = 0;
   out_2434754126251583803[2] = 0;
   out_2434754126251583803[3] = 0;
   out_2434754126251583803[4] = 0;
   out_2434754126251583803[5] = 0;
   out_2434754126251583803[6] = 0;
   out_2434754126251583803[7] = 0;
   out_2434754126251583803[8] = 0;
   out_2434754126251583803[9] = 0;
   out_2434754126251583803[10] = 1.0;
   out_2434754126251583803[11] = 0;
   out_2434754126251583803[12] = 0;
   out_2434754126251583803[13] = 0;
   out_2434754126251583803[14] = 0;
   out_2434754126251583803[15] = 0;
   out_2434754126251583803[16] = 0;
   out_2434754126251583803[17] = 0;
   out_2434754126251583803[18] = 0;
   out_2434754126251583803[19] = 0;
   out_2434754126251583803[20] = 1.0;
   out_2434754126251583803[21] = 0;
   out_2434754126251583803[22] = 0;
   out_2434754126251583803[23] = 0;
   out_2434754126251583803[24] = 0;
   out_2434754126251583803[25] = 0;
   out_2434754126251583803[26] = 0;
   out_2434754126251583803[27] = 0;
   out_2434754126251583803[28] = 0;
   out_2434754126251583803[29] = 0;
   out_2434754126251583803[30] = 1.0;
   out_2434754126251583803[31] = 0;
   out_2434754126251583803[32] = 0;
   out_2434754126251583803[33] = 0;
   out_2434754126251583803[34] = 0;
   out_2434754126251583803[35] = 0;
   out_2434754126251583803[36] = 0;
   out_2434754126251583803[37] = 0;
   out_2434754126251583803[38] = 0;
   out_2434754126251583803[39] = 0;
   out_2434754126251583803[40] = 1.0;
   out_2434754126251583803[41] = 0;
   out_2434754126251583803[42] = 0;
   out_2434754126251583803[43] = 0;
   out_2434754126251583803[44] = 0;
   out_2434754126251583803[45] = 0;
   out_2434754126251583803[46] = 0;
   out_2434754126251583803[47] = 0;
   out_2434754126251583803[48] = 0;
   out_2434754126251583803[49] = 0;
   out_2434754126251583803[50] = 1.0;
   out_2434754126251583803[51] = 0;
   out_2434754126251583803[52] = 0;
   out_2434754126251583803[53] = 0;
   out_2434754126251583803[54] = 0;
   out_2434754126251583803[55] = 0;
   out_2434754126251583803[56] = 0;
   out_2434754126251583803[57] = 0;
   out_2434754126251583803[58] = 0;
   out_2434754126251583803[59] = 0;
   out_2434754126251583803[60] = 1.0;
   out_2434754126251583803[61] = 0;
   out_2434754126251583803[62] = 0;
   out_2434754126251583803[63] = 0;
   out_2434754126251583803[64] = 0;
   out_2434754126251583803[65] = 0;
   out_2434754126251583803[66] = 0;
   out_2434754126251583803[67] = 0;
   out_2434754126251583803[68] = 0;
   out_2434754126251583803[69] = 0;
   out_2434754126251583803[70] = 1.0;
   out_2434754126251583803[71] = 0;
   out_2434754126251583803[72] = 0;
   out_2434754126251583803[73] = 0;
   out_2434754126251583803[74] = 0;
   out_2434754126251583803[75] = 0;
   out_2434754126251583803[76] = 0;
   out_2434754126251583803[77] = 0;
   out_2434754126251583803[78] = 0;
   out_2434754126251583803[79] = 0;
   out_2434754126251583803[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_3191743563366687036) {
   out_3191743563366687036[0] = state[0];
   out_3191743563366687036[1] = state[1];
   out_3191743563366687036[2] = state[2];
   out_3191743563366687036[3] = state[3];
   out_3191743563366687036[4] = state[4];
   out_3191743563366687036[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_3191743563366687036[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_3191743563366687036[7] = state[7];
   out_3191743563366687036[8] = state[8];
}
void F_fun(double *state, double dt, double *out_3866238660743559275) {
   out_3866238660743559275[0] = 1;
   out_3866238660743559275[1] = 0;
   out_3866238660743559275[2] = 0;
   out_3866238660743559275[3] = 0;
   out_3866238660743559275[4] = 0;
   out_3866238660743559275[5] = 0;
   out_3866238660743559275[6] = 0;
   out_3866238660743559275[7] = 0;
   out_3866238660743559275[8] = 0;
   out_3866238660743559275[9] = 0;
   out_3866238660743559275[10] = 1;
   out_3866238660743559275[11] = 0;
   out_3866238660743559275[12] = 0;
   out_3866238660743559275[13] = 0;
   out_3866238660743559275[14] = 0;
   out_3866238660743559275[15] = 0;
   out_3866238660743559275[16] = 0;
   out_3866238660743559275[17] = 0;
   out_3866238660743559275[18] = 0;
   out_3866238660743559275[19] = 0;
   out_3866238660743559275[20] = 1;
   out_3866238660743559275[21] = 0;
   out_3866238660743559275[22] = 0;
   out_3866238660743559275[23] = 0;
   out_3866238660743559275[24] = 0;
   out_3866238660743559275[25] = 0;
   out_3866238660743559275[26] = 0;
   out_3866238660743559275[27] = 0;
   out_3866238660743559275[28] = 0;
   out_3866238660743559275[29] = 0;
   out_3866238660743559275[30] = 1;
   out_3866238660743559275[31] = 0;
   out_3866238660743559275[32] = 0;
   out_3866238660743559275[33] = 0;
   out_3866238660743559275[34] = 0;
   out_3866238660743559275[35] = 0;
   out_3866238660743559275[36] = 0;
   out_3866238660743559275[37] = 0;
   out_3866238660743559275[38] = 0;
   out_3866238660743559275[39] = 0;
   out_3866238660743559275[40] = 1;
   out_3866238660743559275[41] = 0;
   out_3866238660743559275[42] = 0;
   out_3866238660743559275[43] = 0;
   out_3866238660743559275[44] = 0;
   out_3866238660743559275[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_3866238660743559275[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_3866238660743559275[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_3866238660743559275[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_3866238660743559275[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_3866238660743559275[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_3866238660743559275[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_3866238660743559275[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_3866238660743559275[53] = -9.8000000000000007*dt;
   out_3866238660743559275[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_3866238660743559275[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_3866238660743559275[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3866238660743559275[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3866238660743559275[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_3866238660743559275[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_3866238660743559275[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_3866238660743559275[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3866238660743559275[62] = 0;
   out_3866238660743559275[63] = 0;
   out_3866238660743559275[64] = 0;
   out_3866238660743559275[65] = 0;
   out_3866238660743559275[66] = 0;
   out_3866238660743559275[67] = 0;
   out_3866238660743559275[68] = 0;
   out_3866238660743559275[69] = 0;
   out_3866238660743559275[70] = 1;
   out_3866238660743559275[71] = 0;
   out_3866238660743559275[72] = 0;
   out_3866238660743559275[73] = 0;
   out_3866238660743559275[74] = 0;
   out_3866238660743559275[75] = 0;
   out_3866238660743559275[76] = 0;
   out_3866238660743559275[77] = 0;
   out_3866238660743559275[78] = 0;
   out_3866238660743559275[79] = 0;
   out_3866238660743559275[80] = 1;
}
void h_25(double *state, double *unused, double *out_7618328033706461649) {
   out_7618328033706461649[0] = state[6];
}
void H_25(double *state, double *unused, double *out_3381267097997126629) {
   out_3381267097997126629[0] = 0;
   out_3381267097997126629[1] = 0;
   out_3381267097997126629[2] = 0;
   out_3381267097997126629[3] = 0;
   out_3381267097997126629[4] = 0;
   out_3381267097997126629[5] = 0;
   out_3381267097997126629[6] = 1;
   out_3381267097997126629[7] = 0;
   out_3381267097997126629[8] = 0;
}
void h_24(double *state, double *unused, double *out_1309502016488901519) {
   out_1309502016488901519[0] = state[4];
   out_1309502016488901519[1] = state[5];
}
void H_24(double *state, double *unused, double *out_2251733942599321359) {
   out_2251733942599321359[0] = 0;
   out_2251733942599321359[1] = 0;
   out_2251733942599321359[2] = 0;
   out_2251733942599321359[3] = 0;
   out_2251733942599321359[4] = 1;
   out_2251733942599321359[5] = 0;
   out_2251733942599321359[6] = 0;
   out_2251733942599321359[7] = 0;
   out_2251733942599321359[8] = 0;
   out_2251733942599321359[9] = 0;
   out_2251733942599321359[10] = 0;
   out_2251733942599321359[11] = 0;
   out_2251733942599321359[12] = 0;
   out_2251733942599321359[13] = 0;
   out_2251733942599321359[14] = 1;
   out_2251733942599321359[15] = 0;
   out_2251733942599321359[16] = 0;
   out_2251733942599321359[17] = 0;
}
void h_30(double *state, double *unused, double *out_5049370252009797283) {
   out_5049370252009797283[0] = state[4];
}
void H_30(double *state, double *unused, double *out_1146429232130481569) {
   out_1146429232130481569[0] = 0;
   out_1146429232130481569[1] = 0;
   out_1146429232130481569[2] = 0;
   out_1146429232130481569[3] = 0;
   out_1146429232130481569[4] = 1;
   out_1146429232130481569[5] = 0;
   out_1146429232130481569[6] = 0;
   out_1146429232130481569[7] = 0;
   out_1146429232130481569[8] = 0;
}
void h_26(double *state, double *unused, double *out_86990254328504051) {
   out_86990254328504051[0] = state[7];
}
void H_26(double *state, double *unused, double *out_360236220876929595) {
   out_360236220876929595[0] = 0;
   out_360236220876929595[1] = 0;
   out_360236220876929595[2] = 0;
   out_360236220876929595[3] = 0;
   out_360236220876929595[4] = 0;
   out_360236220876929595[5] = 0;
   out_360236220876929595[6] = 0;
   out_360236220876929595[7] = 1;
   out_360236220876929595[8] = 0;
}
void h_27(double *state, double *unused, double *out_2616654766045616004) {
   out_2616654766045616004[0] = state[3];
}
void H_27(double *state, double *unused, double *out_1077164839053461648) {
   out_1077164839053461648[0] = 0;
   out_1077164839053461648[1] = 0;
   out_1077164839053461648[2] = 0;
   out_1077164839053461648[3] = 1;
   out_1077164839053461648[4] = 0;
   out_1077164839053461648[5] = 0;
   out_1077164839053461648[6] = 0;
   out_1077164839053461648[7] = 0;
   out_1077164839053461648[8] = 0;
}
void h_29(double *state, double *unused, double *out_4067286158674499171) {
   out_4067286158674499171[0] = state[1];
}
void H_29(double *state, double *unused, double *out_636197887816089385) {
   out_636197887816089385[0] = 0;
   out_636197887816089385[1] = 1;
   out_636197887816089385[2] = 0;
   out_636197887816089385[3] = 0;
   out_636197887816089385[4] = 0;
   out_636197887816089385[5] = 0;
   out_636197887816089385[6] = 0;
   out_636197887816089385[7] = 0;
   out_636197887816089385[8] = 0;
}
void h_28(double *state, double *unused, double *out_8374639680039353960) {
   out_8374639680039353960[0] = state[0];
}
void H_28(double *state, double *unused, double *out_5718596904885619959) {
   out_5718596904885619959[0] = 1;
   out_5718596904885619959[1] = 0;
   out_5718596904885619959[2] = 0;
   out_5718596904885619959[3] = 0;
   out_5718596904885619959[4] = 0;
   out_5718596904885619959[5] = 0;
   out_5718596904885619959[6] = 0;
   out_5718596904885619959[7] = 0;
   out_5718596904885619959[8] = 0;
}
void h_31(double *state, double *unused, double *out_6966732563574588315) {
   out_6966732563574588315[0] = state[8];
}
void H_31(double *state, double *unused, double *out_986444323110281071) {
   out_986444323110281071[0] = 0;
   out_986444323110281071[1] = 0;
   out_986444323110281071[2] = 0;
   out_986444323110281071[3] = 0;
   out_986444323110281071[4] = 0;
   out_986444323110281071[5] = 0;
   out_986444323110281071[6] = 0;
   out_986444323110281071[7] = 0;
   out_986444323110281071[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_2839074644799155373) {
  err_fun(nom_x, delta_x, out_2839074644799155373);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_2832413412600408261) {
  inv_err_fun(nom_x, true_x, out_2832413412600408261);
}
void car_H_mod_fun(double *state, double *out_2434754126251583803) {
  H_mod_fun(state, out_2434754126251583803);
}
void car_f_fun(double *state, double dt, double *out_3191743563366687036) {
  f_fun(state,  dt, out_3191743563366687036);
}
void car_F_fun(double *state, double dt, double *out_3866238660743559275) {
  F_fun(state,  dt, out_3866238660743559275);
}
void car_h_25(double *state, double *unused, double *out_7618328033706461649) {
  h_25(state, unused, out_7618328033706461649);
}
void car_H_25(double *state, double *unused, double *out_3381267097997126629) {
  H_25(state, unused, out_3381267097997126629);
}
void car_h_24(double *state, double *unused, double *out_1309502016488901519) {
  h_24(state, unused, out_1309502016488901519);
}
void car_H_24(double *state, double *unused, double *out_2251733942599321359) {
  H_24(state, unused, out_2251733942599321359);
}
void car_h_30(double *state, double *unused, double *out_5049370252009797283) {
  h_30(state, unused, out_5049370252009797283);
}
void car_H_30(double *state, double *unused, double *out_1146429232130481569) {
  H_30(state, unused, out_1146429232130481569);
}
void car_h_26(double *state, double *unused, double *out_86990254328504051) {
  h_26(state, unused, out_86990254328504051);
}
void car_H_26(double *state, double *unused, double *out_360236220876929595) {
  H_26(state, unused, out_360236220876929595);
}
void car_h_27(double *state, double *unused, double *out_2616654766045616004) {
  h_27(state, unused, out_2616654766045616004);
}
void car_H_27(double *state, double *unused, double *out_1077164839053461648) {
  H_27(state, unused, out_1077164839053461648);
}
void car_h_29(double *state, double *unused, double *out_4067286158674499171) {
  h_29(state, unused, out_4067286158674499171);
}
void car_H_29(double *state, double *unused, double *out_636197887816089385) {
  H_29(state, unused, out_636197887816089385);
}
void car_h_28(double *state, double *unused, double *out_8374639680039353960) {
  h_28(state, unused, out_8374639680039353960);
}
void car_H_28(double *state, double *unused, double *out_5718596904885619959) {
  H_28(state, unused, out_5718596904885619959);
}
void car_h_31(double *state, double *unused, double *out_6966732563574588315) {
  h_31(state, unused, out_6966732563574588315);
}
void car_H_31(double *state, double *unused, double *out_986444323110281071) {
  H_31(state, unused, out_986444323110281071);
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
