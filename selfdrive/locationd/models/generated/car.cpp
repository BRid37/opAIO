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
void err_fun(double *nom_x, double *delta_x, double *out_278514109382768760) {
   out_278514109382768760[0] = delta_x[0] + nom_x[0];
   out_278514109382768760[1] = delta_x[1] + nom_x[1];
   out_278514109382768760[2] = delta_x[2] + nom_x[2];
   out_278514109382768760[3] = delta_x[3] + nom_x[3];
   out_278514109382768760[4] = delta_x[4] + nom_x[4];
   out_278514109382768760[5] = delta_x[5] + nom_x[5];
   out_278514109382768760[6] = delta_x[6] + nom_x[6];
   out_278514109382768760[7] = delta_x[7] + nom_x[7];
   out_278514109382768760[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_7119409470646650985) {
   out_7119409470646650985[0] = -nom_x[0] + true_x[0];
   out_7119409470646650985[1] = -nom_x[1] + true_x[1];
   out_7119409470646650985[2] = -nom_x[2] + true_x[2];
   out_7119409470646650985[3] = -nom_x[3] + true_x[3];
   out_7119409470646650985[4] = -nom_x[4] + true_x[4];
   out_7119409470646650985[5] = -nom_x[5] + true_x[5];
   out_7119409470646650985[6] = -nom_x[6] + true_x[6];
   out_7119409470646650985[7] = -nom_x[7] + true_x[7];
   out_7119409470646650985[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_2680772634564501341) {
   out_2680772634564501341[0] = 1.0;
   out_2680772634564501341[1] = 0;
   out_2680772634564501341[2] = 0;
   out_2680772634564501341[3] = 0;
   out_2680772634564501341[4] = 0;
   out_2680772634564501341[5] = 0;
   out_2680772634564501341[6] = 0;
   out_2680772634564501341[7] = 0;
   out_2680772634564501341[8] = 0;
   out_2680772634564501341[9] = 0;
   out_2680772634564501341[10] = 1.0;
   out_2680772634564501341[11] = 0;
   out_2680772634564501341[12] = 0;
   out_2680772634564501341[13] = 0;
   out_2680772634564501341[14] = 0;
   out_2680772634564501341[15] = 0;
   out_2680772634564501341[16] = 0;
   out_2680772634564501341[17] = 0;
   out_2680772634564501341[18] = 0;
   out_2680772634564501341[19] = 0;
   out_2680772634564501341[20] = 1.0;
   out_2680772634564501341[21] = 0;
   out_2680772634564501341[22] = 0;
   out_2680772634564501341[23] = 0;
   out_2680772634564501341[24] = 0;
   out_2680772634564501341[25] = 0;
   out_2680772634564501341[26] = 0;
   out_2680772634564501341[27] = 0;
   out_2680772634564501341[28] = 0;
   out_2680772634564501341[29] = 0;
   out_2680772634564501341[30] = 1.0;
   out_2680772634564501341[31] = 0;
   out_2680772634564501341[32] = 0;
   out_2680772634564501341[33] = 0;
   out_2680772634564501341[34] = 0;
   out_2680772634564501341[35] = 0;
   out_2680772634564501341[36] = 0;
   out_2680772634564501341[37] = 0;
   out_2680772634564501341[38] = 0;
   out_2680772634564501341[39] = 0;
   out_2680772634564501341[40] = 1.0;
   out_2680772634564501341[41] = 0;
   out_2680772634564501341[42] = 0;
   out_2680772634564501341[43] = 0;
   out_2680772634564501341[44] = 0;
   out_2680772634564501341[45] = 0;
   out_2680772634564501341[46] = 0;
   out_2680772634564501341[47] = 0;
   out_2680772634564501341[48] = 0;
   out_2680772634564501341[49] = 0;
   out_2680772634564501341[50] = 1.0;
   out_2680772634564501341[51] = 0;
   out_2680772634564501341[52] = 0;
   out_2680772634564501341[53] = 0;
   out_2680772634564501341[54] = 0;
   out_2680772634564501341[55] = 0;
   out_2680772634564501341[56] = 0;
   out_2680772634564501341[57] = 0;
   out_2680772634564501341[58] = 0;
   out_2680772634564501341[59] = 0;
   out_2680772634564501341[60] = 1.0;
   out_2680772634564501341[61] = 0;
   out_2680772634564501341[62] = 0;
   out_2680772634564501341[63] = 0;
   out_2680772634564501341[64] = 0;
   out_2680772634564501341[65] = 0;
   out_2680772634564501341[66] = 0;
   out_2680772634564501341[67] = 0;
   out_2680772634564501341[68] = 0;
   out_2680772634564501341[69] = 0;
   out_2680772634564501341[70] = 1.0;
   out_2680772634564501341[71] = 0;
   out_2680772634564501341[72] = 0;
   out_2680772634564501341[73] = 0;
   out_2680772634564501341[74] = 0;
   out_2680772634564501341[75] = 0;
   out_2680772634564501341[76] = 0;
   out_2680772634564501341[77] = 0;
   out_2680772634564501341[78] = 0;
   out_2680772634564501341[79] = 0;
   out_2680772634564501341[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_9166682367396736219) {
   out_9166682367396736219[0] = state[0];
   out_9166682367396736219[1] = state[1];
   out_9166682367396736219[2] = state[2];
   out_9166682367396736219[3] = state[3];
   out_9166682367396736219[4] = state[4];
   out_9166682367396736219[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_9166682367396736219[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_9166682367396736219[7] = state[7];
   out_9166682367396736219[8] = state[8];
}
void F_fun(double *state, double dt, double *out_786666535844741036) {
   out_786666535844741036[0] = 1;
   out_786666535844741036[1] = 0;
   out_786666535844741036[2] = 0;
   out_786666535844741036[3] = 0;
   out_786666535844741036[4] = 0;
   out_786666535844741036[5] = 0;
   out_786666535844741036[6] = 0;
   out_786666535844741036[7] = 0;
   out_786666535844741036[8] = 0;
   out_786666535844741036[9] = 0;
   out_786666535844741036[10] = 1;
   out_786666535844741036[11] = 0;
   out_786666535844741036[12] = 0;
   out_786666535844741036[13] = 0;
   out_786666535844741036[14] = 0;
   out_786666535844741036[15] = 0;
   out_786666535844741036[16] = 0;
   out_786666535844741036[17] = 0;
   out_786666535844741036[18] = 0;
   out_786666535844741036[19] = 0;
   out_786666535844741036[20] = 1;
   out_786666535844741036[21] = 0;
   out_786666535844741036[22] = 0;
   out_786666535844741036[23] = 0;
   out_786666535844741036[24] = 0;
   out_786666535844741036[25] = 0;
   out_786666535844741036[26] = 0;
   out_786666535844741036[27] = 0;
   out_786666535844741036[28] = 0;
   out_786666535844741036[29] = 0;
   out_786666535844741036[30] = 1;
   out_786666535844741036[31] = 0;
   out_786666535844741036[32] = 0;
   out_786666535844741036[33] = 0;
   out_786666535844741036[34] = 0;
   out_786666535844741036[35] = 0;
   out_786666535844741036[36] = 0;
   out_786666535844741036[37] = 0;
   out_786666535844741036[38] = 0;
   out_786666535844741036[39] = 0;
   out_786666535844741036[40] = 1;
   out_786666535844741036[41] = 0;
   out_786666535844741036[42] = 0;
   out_786666535844741036[43] = 0;
   out_786666535844741036[44] = 0;
   out_786666535844741036[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_786666535844741036[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_786666535844741036[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_786666535844741036[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_786666535844741036[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_786666535844741036[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_786666535844741036[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_786666535844741036[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_786666535844741036[53] = -9.8000000000000007*dt;
   out_786666535844741036[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_786666535844741036[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_786666535844741036[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_786666535844741036[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_786666535844741036[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_786666535844741036[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_786666535844741036[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_786666535844741036[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_786666535844741036[62] = 0;
   out_786666535844741036[63] = 0;
   out_786666535844741036[64] = 0;
   out_786666535844741036[65] = 0;
   out_786666535844741036[66] = 0;
   out_786666535844741036[67] = 0;
   out_786666535844741036[68] = 0;
   out_786666535844741036[69] = 0;
   out_786666535844741036[70] = 1;
   out_786666535844741036[71] = 0;
   out_786666535844741036[72] = 0;
   out_786666535844741036[73] = 0;
   out_786666535844741036[74] = 0;
   out_786666535844741036[75] = 0;
   out_786666535844741036[76] = 0;
   out_786666535844741036[77] = 0;
   out_786666535844741036[78] = 0;
   out_786666535844741036[79] = 0;
   out_786666535844741036[80] = 1;
}
void h_25(double *state, double *unused, double *out_5657746065491102394) {
   out_5657746065491102394[0] = state[6];
}
void H_25(double *state, double *unused, double *out_1711621736218823247) {
   out_1711621736218823247[0] = 0;
   out_1711621736218823247[1] = 0;
   out_1711621736218823247[2] = 0;
   out_1711621736218823247[3] = 0;
   out_1711621736218823247[4] = 0;
   out_1711621736218823247[5] = 0;
   out_1711621736218823247[6] = 1;
   out_1711621736218823247[7] = 0;
   out_1711621736218823247[8] = 0;
}
void h_24(double *state, double *unused, double *out_7488924528864029359) {
   out_7488924528864029359[0] = state[4];
   out_7488924528864029359[1] = state[5];
}
void H_24(double *state, double *unused, double *out_2108267040572682742) {
   out_2108267040572682742[0] = 0;
   out_2108267040572682742[1] = 0;
   out_2108267040572682742[2] = 0;
   out_2108267040572682742[3] = 0;
   out_2108267040572682742[4] = 1;
   out_2108267040572682742[5] = 0;
   out_2108267040572682742[6] = 0;
   out_2108267040572682742[7] = 0;
   out_2108267040572682742[8] = 0;
   out_2108267040572682742[9] = 0;
   out_2108267040572682742[10] = 0;
   out_2108267040572682742[11] = 0;
   out_2108267040572682742[12] = 0;
   out_2108267040572682742[13] = 0;
   out_2108267040572682742[14] = 1;
   out_2108267040572682742[15] = 0;
   out_2108267040572682742[16] = 0;
   out_2108267040572682742[17] = 0;
}
void h_30(double *state, double *unused, double *out_6018162781868098286) {
   out_6018162781868098286[0] = state[4];
}
void H_30(double *state, double *unused, double *out_806711222288425380) {
   out_806711222288425380[0] = 0;
   out_806711222288425380[1] = 0;
   out_806711222288425380[2] = 0;
   out_806711222288425380[3] = 0;
   out_806711222288425380[4] = 1;
   out_806711222288425380[5] = 0;
   out_806711222288425380[6] = 0;
   out_806711222288425380[7] = 0;
   out_806711222288425380[8] = 0;
}
void h_26(double *state, double *unused, double *out_7185906582944240023) {
   out_7185906582944240023[0] = state[7];
}
void H_26(double *state, double *unused, double *out_5453125055092879471) {
   out_5453125055092879471[0] = 0;
   out_5453125055092879471[1] = 0;
   out_5453125055092879471[2] = 0;
   out_5453125055092879471[3] = 0;
   out_5453125055092879471[4] = 0;
   out_5453125055092879471[5] = 0;
   out_5453125055092879471[6] = 0;
   out_5453125055092879471[7] = 1;
   out_5453125055092879471[8] = 0;
}
void h_27(double *state, double *unused, double *out_257884688242759942) {
   out_257884688242759942[0] = state[3];
}
void H_27(double *state, double *unused, double *out_3030305293472368597) {
   out_3030305293472368597[0] = 0;
   out_3030305293472368597[1] = 0;
   out_3030305293472368597[2] = 0;
   out_3030305293472368597[3] = 1;
   out_3030305293472368597[4] = 0;
   out_3030305293472368597[5] = 0;
   out_3030305293472368597[6] = 0;
   out_3030305293472368597[7] = 0;
   out_3030305293472368597[8] = 0;
}
void h_29(double *state, double *unused, double *out_1192746704386123225) {
   out_1192746704386123225[0] = state[1];
}
void H_29(double *state, double *unused, double *out_1316942566602817564) {
   out_1316942566602817564[0] = 0;
   out_1316942566602817564[1] = 1;
   out_1316942566602817564[2] = 0;
   out_1316942566602817564[3] = 0;
   out_1316942566602817564[4] = 0;
   out_1316942566602817564[5] = 0;
   out_1316942566602817564[6] = 0;
   out_1316942566602817564[7] = 0;
   out_1316942566602817564[8] = 0;
}
void h_28(double *state, double *unused, double *out_3663406739054067449) {
   out_3663406739054067449[0] = state[0];
}
void H_28(double *state, double *unused, double *out_3765456450466713010) {
   out_3765456450466713010[0] = 1;
   out_3765456450466713010[1] = 0;
   out_3765456450466713010[2] = 0;
   out_3765456450466713010[3] = 0;
   out_3765456450466713010[4] = 0;
   out_3765456450466713010[5] = 0;
   out_3765456450466713010[6] = 0;
   out_3765456450466713010[7] = 0;
   out_3765456450466713010[8] = 0;
}
void h_31(double *state, double *unused, double *out_8605472055846587355) {
   out_8605472055846587355[0] = state[8];
}
void H_31(double *state, double *unused, double *out_6079333157326230947) {
   out_6079333157326230947[0] = 0;
   out_6079333157326230947[1] = 0;
   out_6079333157326230947[2] = 0;
   out_6079333157326230947[3] = 0;
   out_6079333157326230947[4] = 0;
   out_6079333157326230947[5] = 0;
   out_6079333157326230947[6] = 0;
   out_6079333157326230947[7] = 0;
   out_6079333157326230947[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_278514109382768760) {
  err_fun(nom_x, delta_x, out_278514109382768760);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_7119409470646650985) {
  inv_err_fun(nom_x, true_x, out_7119409470646650985);
}
void car_H_mod_fun(double *state, double *out_2680772634564501341) {
  H_mod_fun(state, out_2680772634564501341);
}
void car_f_fun(double *state, double dt, double *out_9166682367396736219) {
  f_fun(state,  dt, out_9166682367396736219);
}
void car_F_fun(double *state, double dt, double *out_786666535844741036) {
  F_fun(state,  dt, out_786666535844741036);
}
void car_h_25(double *state, double *unused, double *out_5657746065491102394) {
  h_25(state, unused, out_5657746065491102394);
}
void car_H_25(double *state, double *unused, double *out_1711621736218823247) {
  H_25(state, unused, out_1711621736218823247);
}
void car_h_24(double *state, double *unused, double *out_7488924528864029359) {
  h_24(state, unused, out_7488924528864029359);
}
void car_H_24(double *state, double *unused, double *out_2108267040572682742) {
  H_24(state, unused, out_2108267040572682742);
}
void car_h_30(double *state, double *unused, double *out_6018162781868098286) {
  h_30(state, unused, out_6018162781868098286);
}
void car_H_30(double *state, double *unused, double *out_806711222288425380) {
  H_30(state, unused, out_806711222288425380);
}
void car_h_26(double *state, double *unused, double *out_7185906582944240023) {
  h_26(state, unused, out_7185906582944240023);
}
void car_H_26(double *state, double *unused, double *out_5453125055092879471) {
  H_26(state, unused, out_5453125055092879471);
}
void car_h_27(double *state, double *unused, double *out_257884688242759942) {
  h_27(state, unused, out_257884688242759942);
}
void car_H_27(double *state, double *unused, double *out_3030305293472368597) {
  H_27(state, unused, out_3030305293472368597);
}
void car_h_29(double *state, double *unused, double *out_1192746704386123225) {
  h_29(state, unused, out_1192746704386123225);
}
void car_H_29(double *state, double *unused, double *out_1316942566602817564) {
  H_29(state, unused, out_1316942566602817564);
}
void car_h_28(double *state, double *unused, double *out_3663406739054067449) {
  h_28(state, unused, out_3663406739054067449);
}
void car_H_28(double *state, double *unused, double *out_3765456450466713010) {
  H_28(state, unused, out_3765456450466713010);
}
void car_h_31(double *state, double *unused, double *out_8605472055846587355) {
  h_31(state, unused, out_8605472055846587355);
}
void car_H_31(double *state, double *unused, double *out_6079333157326230947) {
  H_31(state, unused, out_6079333157326230947);
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
