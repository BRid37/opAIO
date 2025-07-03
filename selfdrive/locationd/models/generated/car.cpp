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
void err_fun(double *nom_x, double *delta_x, double *out_3125624708001984387) {
   out_3125624708001984387[0] = delta_x[0] + nom_x[0];
   out_3125624708001984387[1] = delta_x[1] + nom_x[1];
   out_3125624708001984387[2] = delta_x[2] + nom_x[2];
   out_3125624708001984387[3] = delta_x[3] + nom_x[3];
   out_3125624708001984387[4] = delta_x[4] + nom_x[4];
   out_3125624708001984387[5] = delta_x[5] + nom_x[5];
   out_3125624708001984387[6] = delta_x[6] + nom_x[6];
   out_3125624708001984387[7] = delta_x[7] + nom_x[7];
   out_3125624708001984387[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_5907949049256047287) {
   out_5907949049256047287[0] = -nom_x[0] + true_x[0];
   out_5907949049256047287[1] = -nom_x[1] + true_x[1];
   out_5907949049256047287[2] = -nom_x[2] + true_x[2];
   out_5907949049256047287[3] = -nom_x[3] + true_x[3];
   out_5907949049256047287[4] = -nom_x[4] + true_x[4];
   out_5907949049256047287[5] = -nom_x[5] + true_x[5];
   out_5907949049256047287[6] = -nom_x[6] + true_x[6];
   out_5907949049256047287[7] = -nom_x[7] + true_x[7];
   out_5907949049256047287[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_654657047716516532) {
   out_654657047716516532[0] = 1.0;
   out_654657047716516532[1] = 0;
   out_654657047716516532[2] = 0;
   out_654657047716516532[3] = 0;
   out_654657047716516532[4] = 0;
   out_654657047716516532[5] = 0;
   out_654657047716516532[6] = 0;
   out_654657047716516532[7] = 0;
   out_654657047716516532[8] = 0;
   out_654657047716516532[9] = 0;
   out_654657047716516532[10] = 1.0;
   out_654657047716516532[11] = 0;
   out_654657047716516532[12] = 0;
   out_654657047716516532[13] = 0;
   out_654657047716516532[14] = 0;
   out_654657047716516532[15] = 0;
   out_654657047716516532[16] = 0;
   out_654657047716516532[17] = 0;
   out_654657047716516532[18] = 0;
   out_654657047716516532[19] = 0;
   out_654657047716516532[20] = 1.0;
   out_654657047716516532[21] = 0;
   out_654657047716516532[22] = 0;
   out_654657047716516532[23] = 0;
   out_654657047716516532[24] = 0;
   out_654657047716516532[25] = 0;
   out_654657047716516532[26] = 0;
   out_654657047716516532[27] = 0;
   out_654657047716516532[28] = 0;
   out_654657047716516532[29] = 0;
   out_654657047716516532[30] = 1.0;
   out_654657047716516532[31] = 0;
   out_654657047716516532[32] = 0;
   out_654657047716516532[33] = 0;
   out_654657047716516532[34] = 0;
   out_654657047716516532[35] = 0;
   out_654657047716516532[36] = 0;
   out_654657047716516532[37] = 0;
   out_654657047716516532[38] = 0;
   out_654657047716516532[39] = 0;
   out_654657047716516532[40] = 1.0;
   out_654657047716516532[41] = 0;
   out_654657047716516532[42] = 0;
   out_654657047716516532[43] = 0;
   out_654657047716516532[44] = 0;
   out_654657047716516532[45] = 0;
   out_654657047716516532[46] = 0;
   out_654657047716516532[47] = 0;
   out_654657047716516532[48] = 0;
   out_654657047716516532[49] = 0;
   out_654657047716516532[50] = 1.0;
   out_654657047716516532[51] = 0;
   out_654657047716516532[52] = 0;
   out_654657047716516532[53] = 0;
   out_654657047716516532[54] = 0;
   out_654657047716516532[55] = 0;
   out_654657047716516532[56] = 0;
   out_654657047716516532[57] = 0;
   out_654657047716516532[58] = 0;
   out_654657047716516532[59] = 0;
   out_654657047716516532[60] = 1.0;
   out_654657047716516532[61] = 0;
   out_654657047716516532[62] = 0;
   out_654657047716516532[63] = 0;
   out_654657047716516532[64] = 0;
   out_654657047716516532[65] = 0;
   out_654657047716516532[66] = 0;
   out_654657047716516532[67] = 0;
   out_654657047716516532[68] = 0;
   out_654657047716516532[69] = 0;
   out_654657047716516532[70] = 1.0;
   out_654657047716516532[71] = 0;
   out_654657047716516532[72] = 0;
   out_654657047716516532[73] = 0;
   out_654657047716516532[74] = 0;
   out_654657047716516532[75] = 0;
   out_654657047716516532[76] = 0;
   out_654657047716516532[77] = 0;
   out_654657047716516532[78] = 0;
   out_654657047716516532[79] = 0;
   out_654657047716516532[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_9134634088613244631) {
   out_9134634088613244631[0] = state[0];
   out_9134634088613244631[1] = state[1];
   out_9134634088613244631[2] = state[2];
   out_9134634088613244631[3] = state[3];
   out_9134634088613244631[4] = state[4];
   out_9134634088613244631[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_9134634088613244631[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_9134634088613244631[7] = state[7];
   out_9134634088613244631[8] = state[8];
}
void F_fun(double *state, double dt, double *out_8308809229269946909) {
   out_8308809229269946909[0] = 1;
   out_8308809229269946909[1] = 0;
   out_8308809229269946909[2] = 0;
   out_8308809229269946909[3] = 0;
   out_8308809229269946909[4] = 0;
   out_8308809229269946909[5] = 0;
   out_8308809229269946909[6] = 0;
   out_8308809229269946909[7] = 0;
   out_8308809229269946909[8] = 0;
   out_8308809229269946909[9] = 0;
   out_8308809229269946909[10] = 1;
   out_8308809229269946909[11] = 0;
   out_8308809229269946909[12] = 0;
   out_8308809229269946909[13] = 0;
   out_8308809229269946909[14] = 0;
   out_8308809229269946909[15] = 0;
   out_8308809229269946909[16] = 0;
   out_8308809229269946909[17] = 0;
   out_8308809229269946909[18] = 0;
   out_8308809229269946909[19] = 0;
   out_8308809229269946909[20] = 1;
   out_8308809229269946909[21] = 0;
   out_8308809229269946909[22] = 0;
   out_8308809229269946909[23] = 0;
   out_8308809229269946909[24] = 0;
   out_8308809229269946909[25] = 0;
   out_8308809229269946909[26] = 0;
   out_8308809229269946909[27] = 0;
   out_8308809229269946909[28] = 0;
   out_8308809229269946909[29] = 0;
   out_8308809229269946909[30] = 1;
   out_8308809229269946909[31] = 0;
   out_8308809229269946909[32] = 0;
   out_8308809229269946909[33] = 0;
   out_8308809229269946909[34] = 0;
   out_8308809229269946909[35] = 0;
   out_8308809229269946909[36] = 0;
   out_8308809229269946909[37] = 0;
   out_8308809229269946909[38] = 0;
   out_8308809229269946909[39] = 0;
   out_8308809229269946909[40] = 1;
   out_8308809229269946909[41] = 0;
   out_8308809229269946909[42] = 0;
   out_8308809229269946909[43] = 0;
   out_8308809229269946909[44] = 0;
   out_8308809229269946909[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_8308809229269946909[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_8308809229269946909[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_8308809229269946909[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_8308809229269946909[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_8308809229269946909[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_8308809229269946909[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_8308809229269946909[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_8308809229269946909[53] = -9.8000000000000007*dt;
   out_8308809229269946909[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_8308809229269946909[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_8308809229269946909[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8308809229269946909[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8308809229269946909[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_8308809229269946909[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_8308809229269946909[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_8308809229269946909[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8308809229269946909[62] = 0;
   out_8308809229269946909[63] = 0;
   out_8308809229269946909[64] = 0;
   out_8308809229269946909[65] = 0;
   out_8308809229269946909[66] = 0;
   out_8308809229269946909[67] = 0;
   out_8308809229269946909[68] = 0;
   out_8308809229269946909[69] = 0;
   out_8308809229269946909[70] = 1;
   out_8308809229269946909[71] = 0;
   out_8308809229269946909[72] = 0;
   out_8308809229269946909[73] = 0;
   out_8308809229269946909[74] = 0;
   out_8308809229269946909[75] = 0;
   out_8308809229269946909[76] = 0;
   out_8308809229269946909[77] = 0;
   out_8308809229269946909[78] = 0;
   out_8308809229269946909[79] = 0;
   out_8308809229269946909[80] = 1;
}
void h_25(double *state, double *unused, double *out_6050901741265612756) {
   out_6050901741265612756[0] = state[6];
}
void H_25(double *state, double *unused, double *out_5374276558103580597) {
   out_5374276558103580597[0] = 0;
   out_5374276558103580597[1] = 0;
   out_5374276558103580597[2] = 0;
   out_5374276558103580597[3] = 0;
   out_5374276558103580597[4] = 0;
   out_5374276558103580597[5] = 0;
   out_5374276558103580597[6] = 1;
   out_5374276558103580597[7] = 0;
   out_5374276558103580597[8] = 0;
}
void h_24(double *state, double *unused, double *out_9042342215772409693) {
   out_9042342215772409693[0] = state[4];
   out_9042342215772409693[1] = state[5];
}
void H_24(double *state, double *unused, double *out_4977631253749721102) {
   out_4977631253749721102[0] = 0;
   out_4977631253749721102[1] = 0;
   out_4977631253749721102[2] = 0;
   out_4977631253749721102[3] = 0;
   out_4977631253749721102[4] = 1;
   out_4977631253749721102[5] = 0;
   out_4977631253749721102[6] = 0;
   out_4977631253749721102[7] = 0;
   out_4977631253749721102[8] = 0;
   out_4977631253749721102[9] = 0;
   out_4977631253749721102[10] = 0;
   out_4977631253749721102[11] = 0;
   out_4977631253749721102[12] = 0;
   out_4977631253749721102[13] = 0;
   out_4977631253749721102[14] = 1;
   out_4977631253749721102[15] = 0;
   out_4977631253749721102[16] = 0;
   out_4977631253749721102[17] = 0;
}
void h_30(double *state, double *unused, double *out_2413452213011590406) {
   out_2413452213011590406[0] = state[4];
}
void H_30(double *state, double *unused, double *out_6155777174114354264) {
   out_6155777174114354264[0] = 0;
   out_6155777174114354264[1] = 0;
   out_6155777174114354264[2] = 0;
   out_6155777174114354264[3] = 0;
   out_6155777174114354264[4] = 1;
   out_6155777174114354264[5] = 0;
   out_6155777174114354264[6] = 0;
   out_6155777174114354264[7] = 0;
   out_6155777174114354264[8] = 0;
}
void h_26(double *state, double *unused, double *out_623333838432742279) {
   out_623333838432742279[0] = state[7];
}
void H_26(double *state, double *unused, double *out_1632773239229524373) {
   out_1632773239229524373[0] = 0;
   out_1632773239229524373[1] = 0;
   out_1632773239229524373[2] = 0;
   out_1632773239229524373[3] = 0;
   out_1632773239229524373[4] = 0;
   out_1632773239229524373[5] = 0;
   out_1632773239229524373[6] = 0;
   out_1632773239229524373[7] = 1;
   out_1632773239229524373[8] = 0;
}
void h_27(double *state, double *unused, double *out_3990185512799712207) {
   out_3990185512799712207[0] = state[3];
}
void H_27(double *state, double *unused, double *out_8330540485914779175) {
   out_8330540485914779175[0] = 0;
   out_8330540485914779175[1] = 0;
   out_8330540485914779175[2] = 0;
   out_8330540485914779175[3] = 1;
   out_8330540485914779175[4] = 0;
   out_8330540485914779175[5] = 0;
   out_8330540485914779175[6] = 0;
   out_8330540485914779175[7] = 0;
   out_8330540485914779175[8] = 0;
}
void h_29(double *state, double *unused, double *out_8812493730425439552) {
   out_8812493730425439552[0] = state[1];
}
void H_29(double *state, double *unused, double *out_8402840860925221408) {
   out_8402840860925221408[0] = 0;
   out_8402840860925221408[1] = 1;
   out_8402840860925221408[2] = 0;
   out_8402840860925221408[3] = 0;
   out_8402840860925221408[4] = 0;
   out_8402840860925221408[5] = 0;
   out_8402840860925221408[6] = 0;
   out_8402840860925221408[7] = 0;
   out_8402840860925221408[8] = 0;
}
void h_28(double *state, double *unused, double *out_8415546428097943740) {
   out_8415546428097943740[0] = state[0];
}
void H_28(double *state, double *unused, double *out_3320441843855690834) {
   out_3320441843855690834[0] = 1;
   out_3320441843855690834[1] = 0;
   out_3320441843855690834[2] = 0;
   out_3320441843855690834[3] = 0;
   out_3320441843855690834[4] = 0;
   out_3320441843855690834[5] = 0;
   out_3320441843855690834[6] = 0;
   out_3320441843855690834[7] = 0;
   out_3320441843855690834[8] = 0;
}
void h_31(double *state, double *unused, double *out_5808014405967643697) {
   out_5808014405967643697[0] = state[8];
}
void H_31(double *state, double *unused, double *out_5404922519980541025) {
   out_5404922519980541025[0] = 0;
   out_5404922519980541025[1] = 0;
   out_5404922519980541025[2] = 0;
   out_5404922519980541025[3] = 0;
   out_5404922519980541025[4] = 0;
   out_5404922519980541025[5] = 0;
   out_5404922519980541025[6] = 0;
   out_5404922519980541025[7] = 0;
   out_5404922519980541025[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_3125624708001984387) {
  err_fun(nom_x, delta_x, out_3125624708001984387);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_5907949049256047287) {
  inv_err_fun(nom_x, true_x, out_5907949049256047287);
}
void car_H_mod_fun(double *state, double *out_654657047716516532) {
  H_mod_fun(state, out_654657047716516532);
}
void car_f_fun(double *state, double dt, double *out_9134634088613244631) {
  f_fun(state,  dt, out_9134634088613244631);
}
void car_F_fun(double *state, double dt, double *out_8308809229269946909) {
  F_fun(state,  dt, out_8308809229269946909);
}
void car_h_25(double *state, double *unused, double *out_6050901741265612756) {
  h_25(state, unused, out_6050901741265612756);
}
void car_H_25(double *state, double *unused, double *out_5374276558103580597) {
  H_25(state, unused, out_5374276558103580597);
}
void car_h_24(double *state, double *unused, double *out_9042342215772409693) {
  h_24(state, unused, out_9042342215772409693);
}
void car_H_24(double *state, double *unused, double *out_4977631253749721102) {
  H_24(state, unused, out_4977631253749721102);
}
void car_h_30(double *state, double *unused, double *out_2413452213011590406) {
  h_30(state, unused, out_2413452213011590406);
}
void car_H_30(double *state, double *unused, double *out_6155777174114354264) {
  H_30(state, unused, out_6155777174114354264);
}
void car_h_26(double *state, double *unused, double *out_623333838432742279) {
  h_26(state, unused, out_623333838432742279);
}
void car_H_26(double *state, double *unused, double *out_1632773239229524373) {
  H_26(state, unused, out_1632773239229524373);
}
void car_h_27(double *state, double *unused, double *out_3990185512799712207) {
  h_27(state, unused, out_3990185512799712207);
}
void car_H_27(double *state, double *unused, double *out_8330540485914779175) {
  H_27(state, unused, out_8330540485914779175);
}
void car_h_29(double *state, double *unused, double *out_8812493730425439552) {
  h_29(state, unused, out_8812493730425439552);
}
void car_H_29(double *state, double *unused, double *out_8402840860925221408) {
  H_29(state, unused, out_8402840860925221408);
}
void car_h_28(double *state, double *unused, double *out_8415546428097943740) {
  h_28(state, unused, out_8415546428097943740);
}
void car_H_28(double *state, double *unused, double *out_3320441843855690834) {
  H_28(state, unused, out_3320441843855690834);
}
void car_h_31(double *state, double *unused, double *out_5808014405967643697) {
  h_31(state, unused, out_5808014405967643697);
}
void car_H_31(double *state, double *unused, double *out_5404922519980541025) {
  H_31(state, unused, out_5404922519980541025);
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
