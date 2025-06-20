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
void err_fun(double *nom_x, double *delta_x, double *out_6231474097932119358) {
   out_6231474097932119358[0] = delta_x[0] + nom_x[0];
   out_6231474097932119358[1] = delta_x[1] + nom_x[1];
   out_6231474097932119358[2] = delta_x[2] + nom_x[2];
   out_6231474097932119358[3] = delta_x[3] + nom_x[3];
   out_6231474097932119358[4] = delta_x[4] + nom_x[4];
   out_6231474097932119358[5] = delta_x[5] + nom_x[5];
   out_6231474097932119358[6] = delta_x[6] + nom_x[6];
   out_6231474097932119358[7] = delta_x[7] + nom_x[7];
   out_6231474097932119358[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_8658353309641893703) {
   out_8658353309641893703[0] = -nom_x[0] + true_x[0];
   out_8658353309641893703[1] = -nom_x[1] + true_x[1];
   out_8658353309641893703[2] = -nom_x[2] + true_x[2];
   out_8658353309641893703[3] = -nom_x[3] + true_x[3];
   out_8658353309641893703[4] = -nom_x[4] + true_x[4];
   out_8658353309641893703[5] = -nom_x[5] + true_x[5];
   out_8658353309641893703[6] = -nom_x[6] + true_x[6];
   out_8658353309641893703[7] = -nom_x[7] + true_x[7];
   out_8658353309641893703[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_5523145543669707057) {
   out_5523145543669707057[0] = 1.0;
   out_5523145543669707057[1] = 0.0;
   out_5523145543669707057[2] = 0.0;
   out_5523145543669707057[3] = 0.0;
   out_5523145543669707057[4] = 0.0;
   out_5523145543669707057[5] = 0.0;
   out_5523145543669707057[6] = 0.0;
   out_5523145543669707057[7] = 0.0;
   out_5523145543669707057[8] = 0.0;
   out_5523145543669707057[9] = 0.0;
   out_5523145543669707057[10] = 1.0;
   out_5523145543669707057[11] = 0.0;
   out_5523145543669707057[12] = 0.0;
   out_5523145543669707057[13] = 0.0;
   out_5523145543669707057[14] = 0.0;
   out_5523145543669707057[15] = 0.0;
   out_5523145543669707057[16] = 0.0;
   out_5523145543669707057[17] = 0.0;
   out_5523145543669707057[18] = 0.0;
   out_5523145543669707057[19] = 0.0;
   out_5523145543669707057[20] = 1.0;
   out_5523145543669707057[21] = 0.0;
   out_5523145543669707057[22] = 0.0;
   out_5523145543669707057[23] = 0.0;
   out_5523145543669707057[24] = 0.0;
   out_5523145543669707057[25] = 0.0;
   out_5523145543669707057[26] = 0.0;
   out_5523145543669707057[27] = 0.0;
   out_5523145543669707057[28] = 0.0;
   out_5523145543669707057[29] = 0.0;
   out_5523145543669707057[30] = 1.0;
   out_5523145543669707057[31] = 0.0;
   out_5523145543669707057[32] = 0.0;
   out_5523145543669707057[33] = 0.0;
   out_5523145543669707057[34] = 0.0;
   out_5523145543669707057[35] = 0.0;
   out_5523145543669707057[36] = 0.0;
   out_5523145543669707057[37] = 0.0;
   out_5523145543669707057[38] = 0.0;
   out_5523145543669707057[39] = 0.0;
   out_5523145543669707057[40] = 1.0;
   out_5523145543669707057[41] = 0.0;
   out_5523145543669707057[42] = 0.0;
   out_5523145543669707057[43] = 0.0;
   out_5523145543669707057[44] = 0.0;
   out_5523145543669707057[45] = 0.0;
   out_5523145543669707057[46] = 0.0;
   out_5523145543669707057[47] = 0.0;
   out_5523145543669707057[48] = 0.0;
   out_5523145543669707057[49] = 0.0;
   out_5523145543669707057[50] = 1.0;
   out_5523145543669707057[51] = 0.0;
   out_5523145543669707057[52] = 0.0;
   out_5523145543669707057[53] = 0.0;
   out_5523145543669707057[54] = 0.0;
   out_5523145543669707057[55] = 0.0;
   out_5523145543669707057[56] = 0.0;
   out_5523145543669707057[57] = 0.0;
   out_5523145543669707057[58] = 0.0;
   out_5523145543669707057[59] = 0.0;
   out_5523145543669707057[60] = 1.0;
   out_5523145543669707057[61] = 0.0;
   out_5523145543669707057[62] = 0.0;
   out_5523145543669707057[63] = 0.0;
   out_5523145543669707057[64] = 0.0;
   out_5523145543669707057[65] = 0.0;
   out_5523145543669707057[66] = 0.0;
   out_5523145543669707057[67] = 0.0;
   out_5523145543669707057[68] = 0.0;
   out_5523145543669707057[69] = 0.0;
   out_5523145543669707057[70] = 1.0;
   out_5523145543669707057[71] = 0.0;
   out_5523145543669707057[72] = 0.0;
   out_5523145543669707057[73] = 0.0;
   out_5523145543669707057[74] = 0.0;
   out_5523145543669707057[75] = 0.0;
   out_5523145543669707057[76] = 0.0;
   out_5523145543669707057[77] = 0.0;
   out_5523145543669707057[78] = 0.0;
   out_5523145543669707057[79] = 0.0;
   out_5523145543669707057[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_6690793444903813550) {
   out_6690793444903813550[0] = state[0];
   out_6690793444903813550[1] = state[1];
   out_6690793444903813550[2] = state[2];
   out_6690793444903813550[3] = state[3];
   out_6690793444903813550[4] = state[4];
   out_6690793444903813550[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_6690793444903813550[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_6690793444903813550[7] = state[7];
   out_6690793444903813550[8] = state[8];
}
void F_fun(double *state, double dt, double *out_6579261019638953676) {
   out_6579261019638953676[0] = 1;
   out_6579261019638953676[1] = 0;
   out_6579261019638953676[2] = 0;
   out_6579261019638953676[3] = 0;
   out_6579261019638953676[4] = 0;
   out_6579261019638953676[5] = 0;
   out_6579261019638953676[6] = 0;
   out_6579261019638953676[7] = 0;
   out_6579261019638953676[8] = 0;
   out_6579261019638953676[9] = 0;
   out_6579261019638953676[10] = 1;
   out_6579261019638953676[11] = 0;
   out_6579261019638953676[12] = 0;
   out_6579261019638953676[13] = 0;
   out_6579261019638953676[14] = 0;
   out_6579261019638953676[15] = 0;
   out_6579261019638953676[16] = 0;
   out_6579261019638953676[17] = 0;
   out_6579261019638953676[18] = 0;
   out_6579261019638953676[19] = 0;
   out_6579261019638953676[20] = 1;
   out_6579261019638953676[21] = 0;
   out_6579261019638953676[22] = 0;
   out_6579261019638953676[23] = 0;
   out_6579261019638953676[24] = 0;
   out_6579261019638953676[25] = 0;
   out_6579261019638953676[26] = 0;
   out_6579261019638953676[27] = 0;
   out_6579261019638953676[28] = 0;
   out_6579261019638953676[29] = 0;
   out_6579261019638953676[30] = 1;
   out_6579261019638953676[31] = 0;
   out_6579261019638953676[32] = 0;
   out_6579261019638953676[33] = 0;
   out_6579261019638953676[34] = 0;
   out_6579261019638953676[35] = 0;
   out_6579261019638953676[36] = 0;
   out_6579261019638953676[37] = 0;
   out_6579261019638953676[38] = 0;
   out_6579261019638953676[39] = 0;
   out_6579261019638953676[40] = 1;
   out_6579261019638953676[41] = 0;
   out_6579261019638953676[42] = 0;
   out_6579261019638953676[43] = 0;
   out_6579261019638953676[44] = 0;
   out_6579261019638953676[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_6579261019638953676[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_6579261019638953676[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_6579261019638953676[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_6579261019638953676[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_6579261019638953676[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_6579261019638953676[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_6579261019638953676[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_6579261019638953676[53] = -9.8000000000000007*dt;
   out_6579261019638953676[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_6579261019638953676[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_6579261019638953676[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6579261019638953676[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6579261019638953676[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_6579261019638953676[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_6579261019638953676[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_6579261019638953676[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6579261019638953676[62] = 0;
   out_6579261019638953676[63] = 0;
   out_6579261019638953676[64] = 0;
   out_6579261019638953676[65] = 0;
   out_6579261019638953676[66] = 0;
   out_6579261019638953676[67] = 0;
   out_6579261019638953676[68] = 0;
   out_6579261019638953676[69] = 0;
   out_6579261019638953676[70] = 1;
   out_6579261019638953676[71] = 0;
   out_6579261019638953676[72] = 0;
   out_6579261019638953676[73] = 0;
   out_6579261019638953676[74] = 0;
   out_6579261019638953676[75] = 0;
   out_6579261019638953676[76] = 0;
   out_6579261019638953676[77] = 0;
   out_6579261019638953676[78] = 0;
   out_6579261019638953676[79] = 0;
   out_6579261019638953676[80] = 1;
}
void h_25(double *state, double *unused, double *out_7306685628894564884) {
   out_7306685628894564884[0] = state[6];
}
void H_25(double *state, double *unused, double *out_973877416220322894) {
   out_973877416220322894[0] = 0;
   out_973877416220322894[1] = 0;
   out_973877416220322894[2] = 0;
   out_973877416220322894[3] = 0;
   out_973877416220322894[4] = 0;
   out_973877416220322894[5] = 0;
   out_973877416220322894[6] = 1;
   out_973877416220322894[7] = 0;
   out_973877416220322894[8] = 0;
}
void h_24(double *state, double *unused, double *out_52094312227393299) {
   out_52094312227393299[0] = state[4];
   out_52094312227393299[1] = state[5];
}
void H_24(double *state, double *unused, double *out_7174910096071484320) {
   out_7174910096071484320[0] = 0;
   out_7174910096071484320[1] = 0;
   out_7174910096071484320[2] = 0;
   out_7174910096071484320[3] = 0;
   out_7174910096071484320[4] = 1;
   out_7174910096071484320[5] = 0;
   out_7174910096071484320[6] = 0;
   out_7174910096071484320[7] = 0;
   out_7174910096071484320[8] = 0;
   out_7174910096071484320[9] = 0;
   out_7174910096071484320[10] = 0;
   out_7174910096071484320[11] = 0;
   out_7174910096071484320[12] = 0;
   out_7174910096071484320[13] = 0;
   out_7174910096071484320[14] = 1;
   out_7174910096071484320[15] = 0;
   out_7174910096071484320[16] = 0;
   out_7174910096071484320[17] = 0;
}
void h_30(double *state, double *unused, double *out_7581879691179070773) {
   out_7581879691179070773[0] = state[4];
}
void H_30(double *state, double *unused, double *out_1103216363363562964) {
   out_1103216363363562964[0] = 0;
   out_1103216363363562964[1] = 0;
   out_1103216363363562964[2] = 0;
   out_1103216363363562964[3] = 0;
   out_1103216363363562964[4] = 1;
   out_1103216363363562964[5] = 0;
   out_1103216363363562964[6] = 0;
   out_1103216363363562964[7] = 0;
   out_1103216363363562964[8] = 0;
}
void h_26(double *state, double *unused, double *out_2580206423518225128) {
   out_2580206423518225128[0] = state[7];
}
void H_26(double *state, double *unused, double *out_4715380735094379118) {
   out_4715380735094379118[0] = 0;
   out_4715380735094379118[1] = 0;
   out_4715380735094379118[2] = 0;
   out_4715380735094379118[3] = 0;
   out_4715380735094379118[4] = 0;
   out_4715380735094379118[5] = 0;
   out_4715380735094379118[6] = 0;
   out_4715380735094379118[7] = 1;
   out_4715380735094379118[8] = 0;
}
void h_27(double *state, double *unused, double *out_6138385177154141087) {
   out_6138385177154141087[0] = state[3];
}
void H_27(double *state, double *unused, double *out_3277979675163987875) {
   out_3277979675163987875[0] = 0;
   out_3277979675163987875[1] = 0;
   out_3277979675163987875[2] = 0;
   out_3277979675163987875[3] = 1;
   out_3277979675163987875[4] = 0;
   out_3277979675163987875[5] = 0;
   out_3277979675163987875[6] = 0;
   out_3277979675163987875[7] = 0;
   out_3277979675163987875[8] = 0;
}
void h_29(double *state, double *unused, double *out_7589016569783024254) {
   out_7589016569783024254[0] = state[1];
}
void H_29(double *state, double *unused, double *out_4991342402033538908) {
   out_4991342402033538908[0] = 0;
   out_4991342402033538908[1] = 1;
   out_4991342402033538908[2] = 0;
   out_4991342402033538908[3] = 0;
   out_4991342402033538908[4] = 0;
   out_4991342402033538908[5] = 0;
   out_4991342402033538908[6] = 0;
   out_4991342402033538908[7] = 0;
   out_4991342402033538908[8] = 0;
}
void h_28(double *state, double *unused, double *out_35865741420946697) {
   out_35865741420946697[0] = state[0];
}
void H_28(double *state, double *unused, double *out_8373002654606482134) {
   out_8373002654606482134[0] = 1;
   out_8373002654606482134[1] = 0;
   out_8373002654606482134[2] = 0;
   out_8373002654606482134[3] = 0;
   out_8373002654606482134[4] = 0;
   out_8373002654606482134[5] = 0;
   out_8373002654606482134[6] = 0;
   out_8373002654606482134[7] = 0;
   out_8373002654606482134[8] = 0;
}
void h_31(double *state, double *unused, double *out_3669236100640542534) {
   out_3669236100640542534[0] = state[8];
}
void H_31(double *state, double *unused, double *out_943231454343362466) {
   out_943231454343362466[0] = 0;
   out_943231454343362466[1] = 0;
   out_943231454343362466[2] = 0;
   out_943231454343362466[3] = 0;
   out_943231454343362466[4] = 0;
   out_943231454343362466[5] = 0;
   out_943231454343362466[6] = 0;
   out_943231454343362466[7] = 0;
   out_943231454343362466[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_6231474097932119358) {
  err_fun(nom_x, delta_x, out_6231474097932119358);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8658353309641893703) {
  inv_err_fun(nom_x, true_x, out_8658353309641893703);
}
void car_H_mod_fun(double *state, double *out_5523145543669707057) {
  H_mod_fun(state, out_5523145543669707057);
}
void car_f_fun(double *state, double dt, double *out_6690793444903813550) {
  f_fun(state,  dt, out_6690793444903813550);
}
void car_F_fun(double *state, double dt, double *out_6579261019638953676) {
  F_fun(state,  dt, out_6579261019638953676);
}
void car_h_25(double *state, double *unused, double *out_7306685628894564884) {
  h_25(state, unused, out_7306685628894564884);
}
void car_H_25(double *state, double *unused, double *out_973877416220322894) {
  H_25(state, unused, out_973877416220322894);
}
void car_h_24(double *state, double *unused, double *out_52094312227393299) {
  h_24(state, unused, out_52094312227393299);
}
void car_H_24(double *state, double *unused, double *out_7174910096071484320) {
  H_24(state, unused, out_7174910096071484320);
}
void car_h_30(double *state, double *unused, double *out_7581879691179070773) {
  h_30(state, unused, out_7581879691179070773);
}
void car_H_30(double *state, double *unused, double *out_1103216363363562964) {
  H_30(state, unused, out_1103216363363562964);
}
void car_h_26(double *state, double *unused, double *out_2580206423518225128) {
  h_26(state, unused, out_2580206423518225128);
}
void car_H_26(double *state, double *unused, double *out_4715380735094379118) {
  H_26(state, unused, out_4715380735094379118);
}
void car_h_27(double *state, double *unused, double *out_6138385177154141087) {
  h_27(state, unused, out_6138385177154141087);
}
void car_H_27(double *state, double *unused, double *out_3277979675163987875) {
  H_27(state, unused, out_3277979675163987875);
}
void car_h_29(double *state, double *unused, double *out_7589016569783024254) {
  h_29(state, unused, out_7589016569783024254);
}
void car_H_29(double *state, double *unused, double *out_4991342402033538908) {
  H_29(state, unused, out_4991342402033538908);
}
void car_h_28(double *state, double *unused, double *out_35865741420946697) {
  h_28(state, unused, out_35865741420946697);
}
void car_H_28(double *state, double *unused, double *out_8373002654606482134) {
  H_28(state, unused, out_8373002654606482134);
}
void car_h_31(double *state, double *unused, double *out_3669236100640542534) {
  h_31(state, unused, out_3669236100640542534);
}
void car_H_31(double *state, double *unused, double *out_943231454343362466) {
  H_31(state, unused, out_943231454343362466);
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
