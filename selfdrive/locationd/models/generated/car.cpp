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
void err_fun(double *nom_x, double *delta_x, double *out_34046400755081495) {
   out_34046400755081495[0] = delta_x[0] + nom_x[0];
   out_34046400755081495[1] = delta_x[1] + nom_x[1];
   out_34046400755081495[2] = delta_x[2] + nom_x[2];
   out_34046400755081495[3] = delta_x[3] + nom_x[3];
   out_34046400755081495[4] = delta_x[4] + nom_x[4];
   out_34046400755081495[5] = delta_x[5] + nom_x[5];
   out_34046400755081495[6] = delta_x[6] + nom_x[6];
   out_34046400755081495[7] = delta_x[7] + nom_x[7];
   out_34046400755081495[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_850021188600913070) {
   out_850021188600913070[0] = -nom_x[0] + true_x[0];
   out_850021188600913070[1] = -nom_x[1] + true_x[1];
   out_850021188600913070[2] = -nom_x[2] + true_x[2];
   out_850021188600913070[3] = -nom_x[3] + true_x[3];
   out_850021188600913070[4] = -nom_x[4] + true_x[4];
   out_850021188600913070[5] = -nom_x[5] + true_x[5];
   out_850021188600913070[6] = -nom_x[6] + true_x[6];
   out_850021188600913070[7] = -nom_x[7] + true_x[7];
   out_850021188600913070[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_8260196495078253117) {
   out_8260196495078253117[0] = 1.0;
   out_8260196495078253117[1] = 0;
   out_8260196495078253117[2] = 0;
   out_8260196495078253117[3] = 0;
   out_8260196495078253117[4] = 0;
   out_8260196495078253117[5] = 0;
   out_8260196495078253117[6] = 0;
   out_8260196495078253117[7] = 0;
   out_8260196495078253117[8] = 0;
   out_8260196495078253117[9] = 0;
   out_8260196495078253117[10] = 1.0;
   out_8260196495078253117[11] = 0;
   out_8260196495078253117[12] = 0;
   out_8260196495078253117[13] = 0;
   out_8260196495078253117[14] = 0;
   out_8260196495078253117[15] = 0;
   out_8260196495078253117[16] = 0;
   out_8260196495078253117[17] = 0;
   out_8260196495078253117[18] = 0;
   out_8260196495078253117[19] = 0;
   out_8260196495078253117[20] = 1.0;
   out_8260196495078253117[21] = 0;
   out_8260196495078253117[22] = 0;
   out_8260196495078253117[23] = 0;
   out_8260196495078253117[24] = 0;
   out_8260196495078253117[25] = 0;
   out_8260196495078253117[26] = 0;
   out_8260196495078253117[27] = 0;
   out_8260196495078253117[28] = 0;
   out_8260196495078253117[29] = 0;
   out_8260196495078253117[30] = 1.0;
   out_8260196495078253117[31] = 0;
   out_8260196495078253117[32] = 0;
   out_8260196495078253117[33] = 0;
   out_8260196495078253117[34] = 0;
   out_8260196495078253117[35] = 0;
   out_8260196495078253117[36] = 0;
   out_8260196495078253117[37] = 0;
   out_8260196495078253117[38] = 0;
   out_8260196495078253117[39] = 0;
   out_8260196495078253117[40] = 1.0;
   out_8260196495078253117[41] = 0;
   out_8260196495078253117[42] = 0;
   out_8260196495078253117[43] = 0;
   out_8260196495078253117[44] = 0;
   out_8260196495078253117[45] = 0;
   out_8260196495078253117[46] = 0;
   out_8260196495078253117[47] = 0;
   out_8260196495078253117[48] = 0;
   out_8260196495078253117[49] = 0;
   out_8260196495078253117[50] = 1.0;
   out_8260196495078253117[51] = 0;
   out_8260196495078253117[52] = 0;
   out_8260196495078253117[53] = 0;
   out_8260196495078253117[54] = 0;
   out_8260196495078253117[55] = 0;
   out_8260196495078253117[56] = 0;
   out_8260196495078253117[57] = 0;
   out_8260196495078253117[58] = 0;
   out_8260196495078253117[59] = 0;
   out_8260196495078253117[60] = 1.0;
   out_8260196495078253117[61] = 0;
   out_8260196495078253117[62] = 0;
   out_8260196495078253117[63] = 0;
   out_8260196495078253117[64] = 0;
   out_8260196495078253117[65] = 0;
   out_8260196495078253117[66] = 0;
   out_8260196495078253117[67] = 0;
   out_8260196495078253117[68] = 0;
   out_8260196495078253117[69] = 0;
   out_8260196495078253117[70] = 1.0;
   out_8260196495078253117[71] = 0;
   out_8260196495078253117[72] = 0;
   out_8260196495078253117[73] = 0;
   out_8260196495078253117[74] = 0;
   out_8260196495078253117[75] = 0;
   out_8260196495078253117[76] = 0;
   out_8260196495078253117[77] = 0;
   out_8260196495078253117[78] = 0;
   out_8260196495078253117[79] = 0;
   out_8260196495078253117[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_6467803478925835161) {
   out_6467803478925835161[0] = state[0];
   out_6467803478925835161[1] = state[1];
   out_6467803478925835161[2] = state[2];
   out_6467803478925835161[3] = state[3];
   out_6467803478925835161[4] = state[4];
   out_6467803478925835161[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_6467803478925835161[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_6467803478925835161[7] = state[7];
   out_6467803478925835161[8] = state[8];
}
void F_fun(double *state, double dt, double *out_4289396415692727330) {
   out_4289396415692727330[0] = 1;
   out_4289396415692727330[1] = 0;
   out_4289396415692727330[2] = 0;
   out_4289396415692727330[3] = 0;
   out_4289396415692727330[4] = 0;
   out_4289396415692727330[5] = 0;
   out_4289396415692727330[6] = 0;
   out_4289396415692727330[7] = 0;
   out_4289396415692727330[8] = 0;
   out_4289396415692727330[9] = 0;
   out_4289396415692727330[10] = 1;
   out_4289396415692727330[11] = 0;
   out_4289396415692727330[12] = 0;
   out_4289396415692727330[13] = 0;
   out_4289396415692727330[14] = 0;
   out_4289396415692727330[15] = 0;
   out_4289396415692727330[16] = 0;
   out_4289396415692727330[17] = 0;
   out_4289396415692727330[18] = 0;
   out_4289396415692727330[19] = 0;
   out_4289396415692727330[20] = 1;
   out_4289396415692727330[21] = 0;
   out_4289396415692727330[22] = 0;
   out_4289396415692727330[23] = 0;
   out_4289396415692727330[24] = 0;
   out_4289396415692727330[25] = 0;
   out_4289396415692727330[26] = 0;
   out_4289396415692727330[27] = 0;
   out_4289396415692727330[28] = 0;
   out_4289396415692727330[29] = 0;
   out_4289396415692727330[30] = 1;
   out_4289396415692727330[31] = 0;
   out_4289396415692727330[32] = 0;
   out_4289396415692727330[33] = 0;
   out_4289396415692727330[34] = 0;
   out_4289396415692727330[35] = 0;
   out_4289396415692727330[36] = 0;
   out_4289396415692727330[37] = 0;
   out_4289396415692727330[38] = 0;
   out_4289396415692727330[39] = 0;
   out_4289396415692727330[40] = 1;
   out_4289396415692727330[41] = 0;
   out_4289396415692727330[42] = 0;
   out_4289396415692727330[43] = 0;
   out_4289396415692727330[44] = 0;
   out_4289396415692727330[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_4289396415692727330[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_4289396415692727330[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_4289396415692727330[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_4289396415692727330[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_4289396415692727330[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_4289396415692727330[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_4289396415692727330[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_4289396415692727330[53] = -9.8000000000000007*dt;
   out_4289396415692727330[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_4289396415692727330[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_4289396415692727330[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4289396415692727330[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4289396415692727330[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_4289396415692727330[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_4289396415692727330[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_4289396415692727330[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4289396415692727330[62] = 0;
   out_4289396415692727330[63] = 0;
   out_4289396415692727330[64] = 0;
   out_4289396415692727330[65] = 0;
   out_4289396415692727330[66] = 0;
   out_4289396415692727330[67] = 0;
   out_4289396415692727330[68] = 0;
   out_4289396415692727330[69] = 0;
   out_4289396415692727330[70] = 1;
   out_4289396415692727330[71] = 0;
   out_4289396415692727330[72] = 0;
   out_4289396415692727330[73] = 0;
   out_4289396415692727330[74] = 0;
   out_4289396415692727330[75] = 0;
   out_4289396415692727330[76] = 0;
   out_4289396415692727330[77] = 0;
   out_4289396415692727330[78] = 0;
   out_4289396415692727330[79] = 0;
   out_4289396415692727330[80] = 1;
}
void h_25(double *state, double *unused, double *out_6872809012467904931) {
   out_6872809012467904931[0] = state[6];
}
void H_25(double *state, double *unused, double *out_3228619721580075227) {
   out_3228619721580075227[0] = 0;
   out_3228619721580075227[1] = 0;
   out_3228619721580075227[2] = 0;
   out_3228619721580075227[3] = 0;
   out_3228619721580075227[4] = 0;
   out_3228619721580075227[5] = 0;
   out_3228619721580075227[6] = 1;
   out_3228619721580075227[7] = 0;
   out_3228619721580075227[8] = 0;
}
void h_24(double *state, double *unused, double *out_5437912013156096213) {
   out_5437912013156096213[0] = state[4];
   out_5437912013156096213[1] = state[5];
}
void H_24(double *state, double *unused, double *out_7975129048546584261) {
   out_7975129048546584261[0] = 0;
   out_7975129048546584261[1] = 0;
   out_7975129048546584261[2] = 0;
   out_7975129048546584261[3] = 0;
   out_7975129048546584261[4] = 1;
   out_7975129048546584261[5] = 0;
   out_7975129048546584261[6] = 0;
   out_7975129048546584261[7] = 0;
   out_7975129048546584261[8] = 0;
   out_7975129048546584261[9] = 0;
   out_7975129048546584261[10] = 0;
   out_7975129048546584261[11] = 0;
   out_7975129048546584261[12] = 0;
   out_7975129048546584261[13] = 0;
   out_7975129048546584261[14] = 1;
   out_7975129048546584261[15] = 0;
   out_7975129048546584261[16] = 0;
   out_7975129048546584261[17] = 0;
}
void h_30(double *state, double *unused, double *out_1767068464250636953) {
   out_1767068464250636953[0] = state[4];
}
void H_30(double *state, double *unused, double *out_3688070619911541528) {
   out_3688070619911541528[0] = 0;
   out_3688070619911541528[1] = 0;
   out_3688070619911541528[2] = 0;
   out_3688070619911541528[3] = 0;
   out_3688070619911541528[4] = 1;
   out_3688070619911541528[5] = 0;
   out_3688070619911541528[6] = 0;
   out_3688070619911541528[7] = 0;
   out_3688070619911541528[8] = 0;
}
void h_26(double *state, double *unused, double *out_4042597281863689087) {
   out_4042597281863689087[0] = state[7];
}
void H_26(double *state, double *unused, double *out_6970123040454131451) {
   out_6970123040454131451[0] = 0;
   out_6970123040454131451[1] = 0;
   out_6970123040454131451[2] = 0;
   out_6970123040454131451[3] = 0;
   out_6970123040454131451[4] = 0;
   out_6970123040454131451[5] = 0;
   out_6970123040454131451[6] = 0;
   out_6970123040454131451[7] = 1;
   out_6970123040454131451[8] = 0;
}
void h_27(double *state, double *unused, double *out_3456535722818834915) {
   out_3456535722818834915[0] = state[3];
}
void H_27(double *state, double *unused, double *out_1513307308111116617) {
   out_1513307308111116617[0] = 0;
   out_1513307308111116617[1] = 0;
   out_1513307308111116617[2] = 0;
   out_1513307308111116617[3] = 1;
   out_1513307308111116617[4] = 0;
   out_1513307308111116617[5] = 0;
   out_1513307308111116617[6] = 0;
   out_1513307308111116617[7] = 0;
   out_1513307308111116617[8] = 0;
}
void h_29(double *state, double *unused, double *out_8022893186209684207) {
   out_8022893186209684207[0] = state[1];
}
void H_29(double *state, double *unused, double *out_200055418758434416) {
   out_200055418758434416[0] = 0;
   out_200055418758434416[1] = 1;
   out_200055418758434416[2] = 0;
   out_200055418758434416[3] = 0;
   out_200055418758434416[4] = 0;
   out_200055418758434416[5] = 0;
   out_200055418758434416[6] = 0;
   out_200055418758434416[7] = 0;
   out_200055418758434416[8] = 0;
}
void h_28(double *state, double *unused, double *out_8458208990479680560) {
   out_8458208990479680560[0] = state[0];
}
void H_28(double *state, double *unused, double *out_5282454435827964990) {
   out_5282454435827964990[0] = 1;
   out_5282454435827964990[1] = 0;
   out_5282454435827964990[2] = 0;
   out_5282454435827964990[3] = 0;
   out_5282454435827964990[4] = 0;
   out_5282454435827964990[5] = 0;
   out_5282454435827964990[6] = 0;
   out_5282454435827964990[7] = 0;
   out_5282454435827964990[8] = 0;
}
void h_31(double *state, double *unused, double *out_1008463638286144254) {
   out_1008463638286144254[0] = state[8];
}
void H_31(double *state, double *unused, double *out_3197973759703114799) {
   out_3197973759703114799[0] = 0;
   out_3197973759703114799[1] = 0;
   out_3197973759703114799[2] = 0;
   out_3197973759703114799[3] = 0;
   out_3197973759703114799[4] = 0;
   out_3197973759703114799[5] = 0;
   out_3197973759703114799[6] = 0;
   out_3197973759703114799[7] = 0;
   out_3197973759703114799[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_34046400755081495) {
  err_fun(nom_x, delta_x, out_34046400755081495);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_850021188600913070) {
  inv_err_fun(nom_x, true_x, out_850021188600913070);
}
void car_H_mod_fun(double *state, double *out_8260196495078253117) {
  H_mod_fun(state, out_8260196495078253117);
}
void car_f_fun(double *state, double dt, double *out_6467803478925835161) {
  f_fun(state,  dt, out_6467803478925835161);
}
void car_F_fun(double *state, double dt, double *out_4289396415692727330) {
  F_fun(state,  dt, out_4289396415692727330);
}
void car_h_25(double *state, double *unused, double *out_6872809012467904931) {
  h_25(state, unused, out_6872809012467904931);
}
void car_H_25(double *state, double *unused, double *out_3228619721580075227) {
  H_25(state, unused, out_3228619721580075227);
}
void car_h_24(double *state, double *unused, double *out_5437912013156096213) {
  h_24(state, unused, out_5437912013156096213);
}
void car_H_24(double *state, double *unused, double *out_7975129048546584261) {
  H_24(state, unused, out_7975129048546584261);
}
void car_h_30(double *state, double *unused, double *out_1767068464250636953) {
  h_30(state, unused, out_1767068464250636953);
}
void car_H_30(double *state, double *unused, double *out_3688070619911541528) {
  H_30(state, unused, out_3688070619911541528);
}
void car_h_26(double *state, double *unused, double *out_4042597281863689087) {
  h_26(state, unused, out_4042597281863689087);
}
void car_H_26(double *state, double *unused, double *out_6970123040454131451) {
  H_26(state, unused, out_6970123040454131451);
}
void car_h_27(double *state, double *unused, double *out_3456535722818834915) {
  h_27(state, unused, out_3456535722818834915);
}
void car_H_27(double *state, double *unused, double *out_1513307308111116617) {
  H_27(state, unused, out_1513307308111116617);
}
void car_h_29(double *state, double *unused, double *out_8022893186209684207) {
  h_29(state, unused, out_8022893186209684207);
}
void car_H_29(double *state, double *unused, double *out_200055418758434416) {
  H_29(state, unused, out_200055418758434416);
}
void car_h_28(double *state, double *unused, double *out_8458208990479680560) {
  h_28(state, unused, out_8458208990479680560);
}
void car_H_28(double *state, double *unused, double *out_5282454435827964990) {
  H_28(state, unused, out_5282454435827964990);
}
void car_h_31(double *state, double *unused, double *out_1008463638286144254) {
  h_31(state, unused, out_1008463638286144254);
}
void car_H_31(double *state, double *unused, double *out_3197973759703114799) {
  H_31(state, unused, out_3197973759703114799);
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
