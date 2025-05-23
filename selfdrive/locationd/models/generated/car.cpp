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
void err_fun(double *nom_x, double *delta_x, double *out_8172705352101921443) {
   out_8172705352101921443[0] = delta_x[0] + nom_x[0];
   out_8172705352101921443[1] = delta_x[1] + nom_x[1];
   out_8172705352101921443[2] = delta_x[2] + nom_x[2];
   out_8172705352101921443[3] = delta_x[3] + nom_x[3];
   out_8172705352101921443[4] = delta_x[4] + nom_x[4];
   out_8172705352101921443[5] = delta_x[5] + nom_x[5];
   out_8172705352101921443[6] = delta_x[6] + nom_x[6];
   out_8172705352101921443[7] = delta_x[7] + nom_x[7];
   out_8172705352101921443[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_8557847967279947729) {
   out_8557847967279947729[0] = -nom_x[0] + true_x[0];
   out_8557847967279947729[1] = -nom_x[1] + true_x[1];
   out_8557847967279947729[2] = -nom_x[2] + true_x[2];
   out_8557847967279947729[3] = -nom_x[3] + true_x[3];
   out_8557847967279947729[4] = -nom_x[4] + true_x[4];
   out_8557847967279947729[5] = -nom_x[5] + true_x[5];
   out_8557847967279947729[6] = -nom_x[6] + true_x[6];
   out_8557847967279947729[7] = -nom_x[7] + true_x[7];
   out_8557847967279947729[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_4915597025617505381) {
   out_4915597025617505381[0] = 1.0;
   out_4915597025617505381[1] = 0;
   out_4915597025617505381[2] = 0;
   out_4915597025617505381[3] = 0;
   out_4915597025617505381[4] = 0;
   out_4915597025617505381[5] = 0;
   out_4915597025617505381[6] = 0;
   out_4915597025617505381[7] = 0;
   out_4915597025617505381[8] = 0;
   out_4915597025617505381[9] = 0;
   out_4915597025617505381[10] = 1.0;
   out_4915597025617505381[11] = 0;
   out_4915597025617505381[12] = 0;
   out_4915597025617505381[13] = 0;
   out_4915597025617505381[14] = 0;
   out_4915597025617505381[15] = 0;
   out_4915597025617505381[16] = 0;
   out_4915597025617505381[17] = 0;
   out_4915597025617505381[18] = 0;
   out_4915597025617505381[19] = 0;
   out_4915597025617505381[20] = 1.0;
   out_4915597025617505381[21] = 0;
   out_4915597025617505381[22] = 0;
   out_4915597025617505381[23] = 0;
   out_4915597025617505381[24] = 0;
   out_4915597025617505381[25] = 0;
   out_4915597025617505381[26] = 0;
   out_4915597025617505381[27] = 0;
   out_4915597025617505381[28] = 0;
   out_4915597025617505381[29] = 0;
   out_4915597025617505381[30] = 1.0;
   out_4915597025617505381[31] = 0;
   out_4915597025617505381[32] = 0;
   out_4915597025617505381[33] = 0;
   out_4915597025617505381[34] = 0;
   out_4915597025617505381[35] = 0;
   out_4915597025617505381[36] = 0;
   out_4915597025617505381[37] = 0;
   out_4915597025617505381[38] = 0;
   out_4915597025617505381[39] = 0;
   out_4915597025617505381[40] = 1.0;
   out_4915597025617505381[41] = 0;
   out_4915597025617505381[42] = 0;
   out_4915597025617505381[43] = 0;
   out_4915597025617505381[44] = 0;
   out_4915597025617505381[45] = 0;
   out_4915597025617505381[46] = 0;
   out_4915597025617505381[47] = 0;
   out_4915597025617505381[48] = 0;
   out_4915597025617505381[49] = 0;
   out_4915597025617505381[50] = 1.0;
   out_4915597025617505381[51] = 0;
   out_4915597025617505381[52] = 0;
   out_4915597025617505381[53] = 0;
   out_4915597025617505381[54] = 0;
   out_4915597025617505381[55] = 0;
   out_4915597025617505381[56] = 0;
   out_4915597025617505381[57] = 0;
   out_4915597025617505381[58] = 0;
   out_4915597025617505381[59] = 0;
   out_4915597025617505381[60] = 1.0;
   out_4915597025617505381[61] = 0;
   out_4915597025617505381[62] = 0;
   out_4915597025617505381[63] = 0;
   out_4915597025617505381[64] = 0;
   out_4915597025617505381[65] = 0;
   out_4915597025617505381[66] = 0;
   out_4915597025617505381[67] = 0;
   out_4915597025617505381[68] = 0;
   out_4915597025617505381[69] = 0;
   out_4915597025617505381[70] = 1.0;
   out_4915597025617505381[71] = 0;
   out_4915597025617505381[72] = 0;
   out_4915597025617505381[73] = 0;
   out_4915597025617505381[74] = 0;
   out_4915597025617505381[75] = 0;
   out_4915597025617505381[76] = 0;
   out_4915597025617505381[77] = 0;
   out_4915597025617505381[78] = 0;
   out_4915597025617505381[79] = 0;
   out_4915597025617505381[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_2284630294969925791) {
   out_2284630294969925791[0] = state[0];
   out_2284630294969925791[1] = state[1];
   out_2284630294969925791[2] = state[2];
   out_2284630294969925791[3] = state[3];
   out_2284630294969925791[4] = state[4];
   out_2284630294969925791[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_2284630294969925791[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_2284630294969925791[7] = state[7];
   out_2284630294969925791[8] = state[8];
}
void F_fun(double *state, double dt, double *out_1966764228047419593) {
   out_1966764228047419593[0] = 1;
   out_1966764228047419593[1] = 0;
   out_1966764228047419593[2] = 0;
   out_1966764228047419593[3] = 0;
   out_1966764228047419593[4] = 0;
   out_1966764228047419593[5] = 0;
   out_1966764228047419593[6] = 0;
   out_1966764228047419593[7] = 0;
   out_1966764228047419593[8] = 0;
   out_1966764228047419593[9] = 0;
   out_1966764228047419593[10] = 1;
   out_1966764228047419593[11] = 0;
   out_1966764228047419593[12] = 0;
   out_1966764228047419593[13] = 0;
   out_1966764228047419593[14] = 0;
   out_1966764228047419593[15] = 0;
   out_1966764228047419593[16] = 0;
   out_1966764228047419593[17] = 0;
   out_1966764228047419593[18] = 0;
   out_1966764228047419593[19] = 0;
   out_1966764228047419593[20] = 1;
   out_1966764228047419593[21] = 0;
   out_1966764228047419593[22] = 0;
   out_1966764228047419593[23] = 0;
   out_1966764228047419593[24] = 0;
   out_1966764228047419593[25] = 0;
   out_1966764228047419593[26] = 0;
   out_1966764228047419593[27] = 0;
   out_1966764228047419593[28] = 0;
   out_1966764228047419593[29] = 0;
   out_1966764228047419593[30] = 1;
   out_1966764228047419593[31] = 0;
   out_1966764228047419593[32] = 0;
   out_1966764228047419593[33] = 0;
   out_1966764228047419593[34] = 0;
   out_1966764228047419593[35] = 0;
   out_1966764228047419593[36] = 0;
   out_1966764228047419593[37] = 0;
   out_1966764228047419593[38] = 0;
   out_1966764228047419593[39] = 0;
   out_1966764228047419593[40] = 1;
   out_1966764228047419593[41] = 0;
   out_1966764228047419593[42] = 0;
   out_1966764228047419593[43] = 0;
   out_1966764228047419593[44] = 0;
   out_1966764228047419593[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_1966764228047419593[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_1966764228047419593[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_1966764228047419593[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_1966764228047419593[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_1966764228047419593[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_1966764228047419593[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_1966764228047419593[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_1966764228047419593[53] = -9.8000000000000007*dt;
   out_1966764228047419593[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_1966764228047419593[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_1966764228047419593[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1966764228047419593[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1966764228047419593[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_1966764228047419593[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_1966764228047419593[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_1966764228047419593[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1966764228047419593[62] = 0;
   out_1966764228047419593[63] = 0;
   out_1966764228047419593[64] = 0;
   out_1966764228047419593[65] = 0;
   out_1966764228047419593[66] = 0;
   out_1966764228047419593[67] = 0;
   out_1966764228047419593[68] = 0;
   out_1966764228047419593[69] = 0;
   out_1966764228047419593[70] = 1;
   out_1966764228047419593[71] = 0;
   out_1966764228047419593[72] = 0;
   out_1966764228047419593[73] = 0;
   out_1966764228047419593[74] = 0;
   out_1966764228047419593[75] = 0;
   out_1966764228047419593[76] = 0;
   out_1966764228047419593[77] = 0;
   out_1966764228047419593[78] = 0;
   out_1966764228047419593[79] = 0;
   out_1966764228047419593[80] = 1;
}
void h_25(double *state, double *unused, double *out_2846973816119094272) {
   out_2846973816119094272[0] = state[6];
}
void H_25(double *state, double *unused, double *out_2956384889041926319) {
   out_2956384889041926319[0] = 0;
   out_2956384889041926319[1] = 0;
   out_2956384889041926319[2] = 0;
   out_2956384889041926319[3] = 0;
   out_2956384889041926319[4] = 0;
   out_2956384889041926319[5] = 0;
   out_2956384889041926319[6] = 1;
   out_2956384889041926319[7] = 0;
   out_2956384889041926319[8] = 0;
}
void h_24(double *state, double *unused, double *out_7107415311318387969) {
   out_7107415311318387969[0] = state[4];
   out_7107415311318387969[1] = state[5];
}
void H_24(double *state, double *unused, double *out_8585575939788673348) {
   out_8585575939788673348[0] = 0;
   out_8585575939788673348[1] = 0;
   out_8585575939788673348[2] = 0;
   out_8585575939788673348[3] = 0;
   out_8585575939788673348[4] = 1;
   out_8585575939788673348[5] = 0;
   out_8585575939788673348[6] = 0;
   out_8585575939788673348[7] = 0;
   out_8585575939788673348[8] = 0;
   out_8585575939788673348[9] = 0;
   out_8585575939788673348[10] = 0;
   out_8585575939788673348[11] = 0;
   out_8585575939788673348[12] = 0;
   out_8585575939788673348[13] = 0;
   out_8585575939788673348[14] = 1;
   out_8585575939788673348[15] = 0;
   out_8585575939788673348[16] = 0;
   out_8585575939788673348[17] = 0;
}
void h_30(double *state, double *unused, double *out_4938661812168088629) {
   out_4938661812168088629[0] = state[4];
}
void H_30(double *state, double *unused, double *out_3085723836185166389) {
   out_3085723836185166389[0] = 0;
   out_3085723836185166389[1] = 0;
   out_3085723836185166389[2] = 0;
   out_3085723836185166389[3] = 0;
   out_3085723836185166389[4] = 1;
   out_3085723836185166389[5] = 0;
   out_3085723836185166389[6] = 0;
   out_3085723836185166389[7] = 0;
   out_3085723836185166389[8] = 0;
}
void h_26(double *state, double *unused, double *out_8506408993880617342) {
   out_8506408993880617342[0] = state[7];
}
void H_26(double *state, double *unused, double *out_6697888207915982543) {
   out_6697888207915982543[0] = 0;
   out_6697888207915982543[1] = 0;
   out_6697888207915982543[2] = 0;
   out_6697888207915982543[3] = 0;
   out_6697888207915982543[4] = 0;
   out_6697888207915982543[5] = 0;
   out_6697888207915982543[6] = 0;
   out_6697888207915982543[7] = 1;
   out_6697888207915982543[8] = 0;
}
void h_27(double *state, double *unused, double *out_1578387099179137261) {
   out_1578387099179137261[0] = state[3];
}
void H_27(double *state, double *unused, double *out_5260487147985591300) {
   out_5260487147985591300[0] = 0;
   out_5260487147985591300[1] = 0;
   out_5260487147985591300[2] = 0;
   out_5260487147985591300[3] = 1;
   out_5260487147985591300[4] = 0;
   out_5260487147985591300[5] = 0;
   out_5260487147985591300[6] = 0;
   out_5260487147985591300[7] = 0;
   out_5260487147985591300[8] = 0;
}
void h_29(double *state, double *unused, double *out_5882171665069751064) {
   out_5882171665069751064[0] = state[1];
}
void H_29(double *state, double *unused, double *out_6973849874855142333) {
   out_6973849874855142333[0] = 0;
   out_6973849874855142333[1] = 1;
   out_6973849874855142333[2] = 0;
   out_6973849874855142333[3] = 0;
   out_6973849874855142333[4] = 0;
   out_6973849874855142333[5] = 0;
   out_6973849874855142333[6] = 0;
   out_6973849874855142333[7] = 0;
   out_6973849874855142333[8] = 0;
}
void h_28(double *state, double *unused, double *out_1026018221629560390) {
   out_1026018221629560390[0] = state[0];
}
void H_28(double *state, double *unused, double *out_5010219603289816082) {
   out_5010219603289816082[0] = 1;
   out_5010219603289816082[1] = 0;
   out_5010219603289816082[2] = 0;
   out_5010219603289816082[3] = 0;
   out_5010219603289816082[4] = 0;
   out_5010219603289816082[5] = 0;
   out_5010219603289816082[6] = 0;
   out_5010219603289816082[7] = 0;
   out_5010219603289816082[8] = 0;
}
void h_31(double *state, double *unused, double *out_3266099500130579239) {
   out_3266099500130579239[0] = state[8];
}
void H_31(double *state, double *unused, double *out_2925738927164965891) {
   out_2925738927164965891[0] = 0;
   out_2925738927164965891[1] = 0;
   out_2925738927164965891[2] = 0;
   out_2925738927164965891[3] = 0;
   out_2925738927164965891[4] = 0;
   out_2925738927164965891[5] = 0;
   out_2925738927164965891[6] = 0;
   out_2925738927164965891[7] = 0;
   out_2925738927164965891[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_8172705352101921443) {
  err_fun(nom_x, delta_x, out_8172705352101921443);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8557847967279947729) {
  inv_err_fun(nom_x, true_x, out_8557847967279947729);
}
void car_H_mod_fun(double *state, double *out_4915597025617505381) {
  H_mod_fun(state, out_4915597025617505381);
}
void car_f_fun(double *state, double dt, double *out_2284630294969925791) {
  f_fun(state,  dt, out_2284630294969925791);
}
void car_F_fun(double *state, double dt, double *out_1966764228047419593) {
  F_fun(state,  dt, out_1966764228047419593);
}
void car_h_25(double *state, double *unused, double *out_2846973816119094272) {
  h_25(state, unused, out_2846973816119094272);
}
void car_H_25(double *state, double *unused, double *out_2956384889041926319) {
  H_25(state, unused, out_2956384889041926319);
}
void car_h_24(double *state, double *unused, double *out_7107415311318387969) {
  h_24(state, unused, out_7107415311318387969);
}
void car_H_24(double *state, double *unused, double *out_8585575939788673348) {
  H_24(state, unused, out_8585575939788673348);
}
void car_h_30(double *state, double *unused, double *out_4938661812168088629) {
  h_30(state, unused, out_4938661812168088629);
}
void car_H_30(double *state, double *unused, double *out_3085723836185166389) {
  H_30(state, unused, out_3085723836185166389);
}
void car_h_26(double *state, double *unused, double *out_8506408993880617342) {
  h_26(state, unused, out_8506408993880617342);
}
void car_H_26(double *state, double *unused, double *out_6697888207915982543) {
  H_26(state, unused, out_6697888207915982543);
}
void car_h_27(double *state, double *unused, double *out_1578387099179137261) {
  h_27(state, unused, out_1578387099179137261);
}
void car_H_27(double *state, double *unused, double *out_5260487147985591300) {
  H_27(state, unused, out_5260487147985591300);
}
void car_h_29(double *state, double *unused, double *out_5882171665069751064) {
  h_29(state, unused, out_5882171665069751064);
}
void car_H_29(double *state, double *unused, double *out_6973849874855142333) {
  H_29(state, unused, out_6973849874855142333);
}
void car_h_28(double *state, double *unused, double *out_1026018221629560390) {
  h_28(state, unused, out_1026018221629560390);
}
void car_H_28(double *state, double *unused, double *out_5010219603289816082) {
  H_28(state, unused, out_5010219603289816082);
}
void car_h_31(double *state, double *unused, double *out_3266099500130579239) {
  h_31(state, unused, out_3266099500130579239);
}
void car_H_31(double *state, double *unused, double *out_2925738927164965891) {
  H_31(state, unused, out_2925738927164965891);
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
