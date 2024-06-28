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
void err_fun(double *nom_x, double *delta_x, double *out_6616974218141628763) {
   out_6616974218141628763[0] = delta_x[0] + nom_x[0];
   out_6616974218141628763[1] = delta_x[1] + nom_x[1];
   out_6616974218141628763[2] = delta_x[2] + nom_x[2];
   out_6616974218141628763[3] = delta_x[3] + nom_x[3];
   out_6616974218141628763[4] = delta_x[4] + nom_x[4];
   out_6616974218141628763[5] = delta_x[5] + nom_x[5];
   out_6616974218141628763[6] = delta_x[6] + nom_x[6];
   out_6616974218141628763[7] = delta_x[7] + nom_x[7];
   out_6616974218141628763[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_603616978303022192) {
   out_603616978303022192[0] = -nom_x[0] + true_x[0];
   out_603616978303022192[1] = -nom_x[1] + true_x[1];
   out_603616978303022192[2] = -nom_x[2] + true_x[2];
   out_603616978303022192[3] = -nom_x[3] + true_x[3];
   out_603616978303022192[4] = -nom_x[4] + true_x[4];
   out_603616978303022192[5] = -nom_x[5] + true_x[5];
   out_603616978303022192[6] = -nom_x[6] + true_x[6];
   out_603616978303022192[7] = -nom_x[7] + true_x[7];
   out_603616978303022192[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_5084198424536638935) {
   out_5084198424536638935[0] = 1.0;
   out_5084198424536638935[1] = 0;
   out_5084198424536638935[2] = 0;
   out_5084198424536638935[3] = 0;
   out_5084198424536638935[4] = 0;
   out_5084198424536638935[5] = 0;
   out_5084198424536638935[6] = 0;
   out_5084198424536638935[7] = 0;
   out_5084198424536638935[8] = 0;
   out_5084198424536638935[9] = 0;
   out_5084198424536638935[10] = 1.0;
   out_5084198424536638935[11] = 0;
   out_5084198424536638935[12] = 0;
   out_5084198424536638935[13] = 0;
   out_5084198424536638935[14] = 0;
   out_5084198424536638935[15] = 0;
   out_5084198424536638935[16] = 0;
   out_5084198424536638935[17] = 0;
   out_5084198424536638935[18] = 0;
   out_5084198424536638935[19] = 0;
   out_5084198424536638935[20] = 1.0;
   out_5084198424536638935[21] = 0;
   out_5084198424536638935[22] = 0;
   out_5084198424536638935[23] = 0;
   out_5084198424536638935[24] = 0;
   out_5084198424536638935[25] = 0;
   out_5084198424536638935[26] = 0;
   out_5084198424536638935[27] = 0;
   out_5084198424536638935[28] = 0;
   out_5084198424536638935[29] = 0;
   out_5084198424536638935[30] = 1.0;
   out_5084198424536638935[31] = 0;
   out_5084198424536638935[32] = 0;
   out_5084198424536638935[33] = 0;
   out_5084198424536638935[34] = 0;
   out_5084198424536638935[35] = 0;
   out_5084198424536638935[36] = 0;
   out_5084198424536638935[37] = 0;
   out_5084198424536638935[38] = 0;
   out_5084198424536638935[39] = 0;
   out_5084198424536638935[40] = 1.0;
   out_5084198424536638935[41] = 0;
   out_5084198424536638935[42] = 0;
   out_5084198424536638935[43] = 0;
   out_5084198424536638935[44] = 0;
   out_5084198424536638935[45] = 0;
   out_5084198424536638935[46] = 0;
   out_5084198424536638935[47] = 0;
   out_5084198424536638935[48] = 0;
   out_5084198424536638935[49] = 0;
   out_5084198424536638935[50] = 1.0;
   out_5084198424536638935[51] = 0;
   out_5084198424536638935[52] = 0;
   out_5084198424536638935[53] = 0;
   out_5084198424536638935[54] = 0;
   out_5084198424536638935[55] = 0;
   out_5084198424536638935[56] = 0;
   out_5084198424536638935[57] = 0;
   out_5084198424536638935[58] = 0;
   out_5084198424536638935[59] = 0;
   out_5084198424536638935[60] = 1.0;
   out_5084198424536638935[61] = 0;
   out_5084198424536638935[62] = 0;
   out_5084198424536638935[63] = 0;
   out_5084198424536638935[64] = 0;
   out_5084198424536638935[65] = 0;
   out_5084198424536638935[66] = 0;
   out_5084198424536638935[67] = 0;
   out_5084198424536638935[68] = 0;
   out_5084198424536638935[69] = 0;
   out_5084198424536638935[70] = 1.0;
   out_5084198424536638935[71] = 0;
   out_5084198424536638935[72] = 0;
   out_5084198424536638935[73] = 0;
   out_5084198424536638935[74] = 0;
   out_5084198424536638935[75] = 0;
   out_5084198424536638935[76] = 0;
   out_5084198424536638935[77] = 0;
   out_5084198424536638935[78] = 0;
   out_5084198424536638935[79] = 0;
   out_5084198424536638935[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_2958089901796743382) {
   out_2958089901796743382[0] = state[0];
   out_2958089901796743382[1] = state[1];
   out_2958089901796743382[2] = state[2];
   out_2958089901796743382[3] = state[3];
   out_2958089901796743382[4] = state[4];
   out_2958089901796743382[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_2958089901796743382[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_2958089901796743382[7] = state[7];
   out_2958089901796743382[8] = state[8];
}
void F_fun(double *state, double dt, double *out_5971980461163695508) {
   out_5971980461163695508[0] = 1;
   out_5971980461163695508[1] = 0;
   out_5971980461163695508[2] = 0;
   out_5971980461163695508[3] = 0;
   out_5971980461163695508[4] = 0;
   out_5971980461163695508[5] = 0;
   out_5971980461163695508[6] = 0;
   out_5971980461163695508[7] = 0;
   out_5971980461163695508[8] = 0;
   out_5971980461163695508[9] = 0;
   out_5971980461163695508[10] = 1;
   out_5971980461163695508[11] = 0;
   out_5971980461163695508[12] = 0;
   out_5971980461163695508[13] = 0;
   out_5971980461163695508[14] = 0;
   out_5971980461163695508[15] = 0;
   out_5971980461163695508[16] = 0;
   out_5971980461163695508[17] = 0;
   out_5971980461163695508[18] = 0;
   out_5971980461163695508[19] = 0;
   out_5971980461163695508[20] = 1;
   out_5971980461163695508[21] = 0;
   out_5971980461163695508[22] = 0;
   out_5971980461163695508[23] = 0;
   out_5971980461163695508[24] = 0;
   out_5971980461163695508[25] = 0;
   out_5971980461163695508[26] = 0;
   out_5971980461163695508[27] = 0;
   out_5971980461163695508[28] = 0;
   out_5971980461163695508[29] = 0;
   out_5971980461163695508[30] = 1;
   out_5971980461163695508[31] = 0;
   out_5971980461163695508[32] = 0;
   out_5971980461163695508[33] = 0;
   out_5971980461163695508[34] = 0;
   out_5971980461163695508[35] = 0;
   out_5971980461163695508[36] = 0;
   out_5971980461163695508[37] = 0;
   out_5971980461163695508[38] = 0;
   out_5971980461163695508[39] = 0;
   out_5971980461163695508[40] = 1;
   out_5971980461163695508[41] = 0;
   out_5971980461163695508[42] = 0;
   out_5971980461163695508[43] = 0;
   out_5971980461163695508[44] = 0;
   out_5971980461163695508[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_5971980461163695508[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_5971980461163695508[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_5971980461163695508[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_5971980461163695508[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_5971980461163695508[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_5971980461163695508[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_5971980461163695508[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_5971980461163695508[53] = -9.8000000000000007*dt;
   out_5971980461163695508[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_5971980461163695508[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_5971980461163695508[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_5971980461163695508[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_5971980461163695508[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_5971980461163695508[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_5971980461163695508[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_5971980461163695508[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_5971980461163695508[62] = 0;
   out_5971980461163695508[63] = 0;
   out_5971980461163695508[64] = 0;
   out_5971980461163695508[65] = 0;
   out_5971980461163695508[66] = 0;
   out_5971980461163695508[67] = 0;
   out_5971980461163695508[68] = 0;
   out_5971980461163695508[69] = 0;
   out_5971980461163695508[70] = 1;
   out_5971980461163695508[71] = 0;
   out_5971980461163695508[72] = 0;
   out_5971980461163695508[73] = 0;
   out_5971980461163695508[74] = 0;
   out_5971980461163695508[75] = 0;
   out_5971980461163695508[76] = 0;
   out_5971980461163695508[77] = 0;
   out_5971980461163695508[78] = 0;
   out_5971980461163695508[79] = 0;
   out_5971980461163695508[80] = 1;
}
void h_25(double *state, double *unused, double *out_2642320330981449862) {
   out_2642320330981449862[0] = state[6];
}
void H_25(double *state, double *unused, double *out_4231893028250857083) {
   out_4231893028250857083[0] = 0;
   out_4231893028250857083[1] = 0;
   out_4231893028250857083[2] = 0;
   out_4231893028250857083[3] = 0;
   out_4231893028250857083[4] = 0;
   out_4231893028250857083[5] = 0;
   out_4231893028250857083[6] = 1;
   out_4231893028250857083[7] = 0;
   out_4231893028250857083[8] = 0;
}
void h_24(double *state, double *unused, double *out_1213238302912253576) {
   out_1213238302912253576[0] = state[4];
   out_1213238302912253576[1] = state[5];
}
void H_24(double *state, double *unused, double *out_5919709464119961274) {
   out_5919709464119961274[0] = 0;
   out_5919709464119961274[1] = 0;
   out_5919709464119961274[2] = 0;
   out_5919709464119961274[3] = 0;
   out_5919709464119961274[4] = 1;
   out_5919709464119961274[5] = 0;
   out_5919709464119961274[6] = 0;
   out_5919709464119961274[7] = 0;
   out_5919709464119961274[8] = 0;
   out_5919709464119961274[9] = 0;
   out_5919709464119961274[10] = 0;
   out_5919709464119961274[11] = 0;
   out_5919709464119961274[12] = 0;
   out_5919709464119961274[13] = 0;
   out_5919709464119961274[14] = 1;
   out_5919709464119961274[15] = 0;
   out_5919709464119961274[16] = 0;
   out_5919709464119961274[17] = 0;
}
void h_30(double *state, double *unused, double *out_7923151091974052569) {
   out_7923151091974052569[0] = state[4];
}
void H_30(double *state, double *unused, double *out_6750225986758105710) {
   out_6750225986758105710[0] = 0;
   out_6750225986758105710[1] = 0;
   out_6750225986758105710[2] = 0;
   out_6750225986758105710[3] = 0;
   out_6750225986758105710[4] = 1;
   out_6750225986758105710[5] = 0;
   out_6750225986758105710[6] = 0;
   out_6750225986758105710[7] = 0;
   out_6750225986758105710[8] = 0;
}
void h_26(double *state, double *unused, double *out_5521919714074653402) {
   out_5521919714074653402[0] = state[7];
}
void H_26(double *state, double *unused, double *out_490389709376800859) {
   out_490389709376800859[0] = 0;
   out_490389709376800859[1] = 0;
   out_490389709376800859[2] = 0;
   out_490389709376800859[3] = 0;
   out_490389709376800859[4] = 0;
   out_490389709376800859[5] = 0;
   out_490389709376800859[6] = 0;
   out_490389709376800859[7] = 1;
   out_490389709376800859[8] = 0;
}
void h_27(double *state, double *unused, double *out_3245636215657927379) {
   out_3245636215657927379[0] = state[3];
}
void H_27(double *state, double *unused, double *out_8973820057942048927) {
   out_8973820057942048927[0] = 0;
   out_8973820057942048927[1] = 0;
   out_8973820057942048927[2] = 0;
   out_8973820057942048927[3] = 1;
   out_8973820057942048927[4] = 0;
   out_8973820057942048927[5] = 0;
   out_8973820057942048927[6] = 0;
   out_8973820057942048927[7] = 0;
   out_8973820057942048927[8] = 0;
}
void h_29(double *state, double *unused, double *out_6883085743911949729) {
   out_6883085743911949729[0] = state[1];
}
void H_29(double *state, double *unused, double *out_7260457331072497894) {
   out_7260457331072497894[0] = 0;
   out_7260457331072497894[1] = 1;
   out_7260457331072497894[2] = 0;
   out_7260457331072497894[3] = 0;
   out_7260457331072497894[4] = 0;
   out_7260457331072497894[5] = 0;
   out_7260457331072497894[6] = 0;
   out_7260457331072497894[7] = 0;
   out_7260457331072497894[8] = 0;
}
void h_28(double *state, double *unused, double *out_2302126362756264944) {
   out_2302126362756264944[0] = state[0];
}
void H_28(double *state, double *unused, double *out_2178058314002967320) {
   out_2178058314002967320[0] = 1;
   out_2178058314002967320[1] = 0;
   out_2178058314002967320[2] = 0;
   out_2178058314002967320[3] = 0;
   out_2178058314002967320[4] = 0;
   out_2178058314002967320[5] = 0;
   out_2178058314002967320[6] = 0;
   out_2178058314002967320[7] = 0;
   out_2178058314002967320[8] = 0;
}
void h_31(double *state, double *unused, double *out_305405659374035099) {
   out_305405659374035099[0] = state[8];
}
void H_31(double *state, double *unused, double *out_135818392856550617) {
   out_135818392856550617[0] = 0;
   out_135818392856550617[1] = 0;
   out_135818392856550617[2] = 0;
   out_135818392856550617[3] = 0;
   out_135818392856550617[4] = 0;
   out_135818392856550617[5] = 0;
   out_135818392856550617[6] = 0;
   out_135818392856550617[7] = 0;
   out_135818392856550617[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_6616974218141628763) {
  err_fun(nom_x, delta_x, out_6616974218141628763);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_603616978303022192) {
  inv_err_fun(nom_x, true_x, out_603616978303022192);
}
void car_H_mod_fun(double *state, double *out_5084198424536638935) {
  H_mod_fun(state, out_5084198424536638935);
}
void car_f_fun(double *state, double dt, double *out_2958089901796743382) {
  f_fun(state,  dt, out_2958089901796743382);
}
void car_F_fun(double *state, double dt, double *out_5971980461163695508) {
  F_fun(state,  dt, out_5971980461163695508);
}
void car_h_25(double *state, double *unused, double *out_2642320330981449862) {
  h_25(state, unused, out_2642320330981449862);
}
void car_H_25(double *state, double *unused, double *out_4231893028250857083) {
  H_25(state, unused, out_4231893028250857083);
}
void car_h_24(double *state, double *unused, double *out_1213238302912253576) {
  h_24(state, unused, out_1213238302912253576);
}
void car_H_24(double *state, double *unused, double *out_5919709464119961274) {
  H_24(state, unused, out_5919709464119961274);
}
void car_h_30(double *state, double *unused, double *out_7923151091974052569) {
  h_30(state, unused, out_7923151091974052569);
}
void car_H_30(double *state, double *unused, double *out_6750225986758105710) {
  H_30(state, unused, out_6750225986758105710);
}
void car_h_26(double *state, double *unused, double *out_5521919714074653402) {
  h_26(state, unused, out_5521919714074653402);
}
void car_H_26(double *state, double *unused, double *out_490389709376800859) {
  H_26(state, unused, out_490389709376800859);
}
void car_h_27(double *state, double *unused, double *out_3245636215657927379) {
  h_27(state, unused, out_3245636215657927379);
}
void car_H_27(double *state, double *unused, double *out_8973820057942048927) {
  H_27(state, unused, out_8973820057942048927);
}
void car_h_29(double *state, double *unused, double *out_6883085743911949729) {
  h_29(state, unused, out_6883085743911949729);
}
void car_H_29(double *state, double *unused, double *out_7260457331072497894) {
  H_29(state, unused, out_7260457331072497894);
}
void car_h_28(double *state, double *unused, double *out_2302126362756264944) {
  h_28(state, unused, out_2302126362756264944);
}
void car_H_28(double *state, double *unused, double *out_2178058314002967320) {
  H_28(state, unused, out_2178058314002967320);
}
void car_h_31(double *state, double *unused, double *out_305405659374035099) {
  h_31(state, unused, out_305405659374035099);
}
void car_H_31(double *state, double *unused, double *out_135818392856550617) {
  H_31(state, unused, out_135818392856550617);
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
