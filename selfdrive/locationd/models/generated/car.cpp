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
void err_fun(double *nom_x, double *delta_x, double *out_7892580644768456538) {
   out_7892580644768456538[0] = delta_x[0] + nom_x[0];
   out_7892580644768456538[1] = delta_x[1] + nom_x[1];
   out_7892580644768456538[2] = delta_x[2] + nom_x[2];
   out_7892580644768456538[3] = delta_x[3] + nom_x[3];
   out_7892580644768456538[4] = delta_x[4] + nom_x[4];
   out_7892580644768456538[5] = delta_x[5] + nom_x[5];
   out_7892580644768456538[6] = delta_x[6] + nom_x[6];
   out_7892580644768456538[7] = delta_x[7] + nom_x[7];
   out_7892580644768456538[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_5204839923779822433) {
   out_5204839923779822433[0] = -nom_x[0] + true_x[0];
   out_5204839923779822433[1] = -nom_x[1] + true_x[1];
   out_5204839923779822433[2] = -nom_x[2] + true_x[2];
   out_5204839923779822433[3] = -nom_x[3] + true_x[3];
   out_5204839923779822433[4] = -nom_x[4] + true_x[4];
   out_5204839923779822433[5] = -nom_x[5] + true_x[5];
   out_5204839923779822433[6] = -nom_x[6] + true_x[6];
   out_5204839923779822433[7] = -nom_x[7] + true_x[7];
   out_5204839923779822433[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_8344684464375028132) {
   out_8344684464375028132[0] = 1.0;
   out_8344684464375028132[1] = 0.0;
   out_8344684464375028132[2] = 0.0;
   out_8344684464375028132[3] = 0.0;
   out_8344684464375028132[4] = 0.0;
   out_8344684464375028132[5] = 0.0;
   out_8344684464375028132[6] = 0.0;
   out_8344684464375028132[7] = 0.0;
   out_8344684464375028132[8] = 0.0;
   out_8344684464375028132[9] = 0.0;
   out_8344684464375028132[10] = 1.0;
   out_8344684464375028132[11] = 0.0;
   out_8344684464375028132[12] = 0.0;
   out_8344684464375028132[13] = 0.0;
   out_8344684464375028132[14] = 0.0;
   out_8344684464375028132[15] = 0.0;
   out_8344684464375028132[16] = 0.0;
   out_8344684464375028132[17] = 0.0;
   out_8344684464375028132[18] = 0.0;
   out_8344684464375028132[19] = 0.0;
   out_8344684464375028132[20] = 1.0;
   out_8344684464375028132[21] = 0.0;
   out_8344684464375028132[22] = 0.0;
   out_8344684464375028132[23] = 0.0;
   out_8344684464375028132[24] = 0.0;
   out_8344684464375028132[25] = 0.0;
   out_8344684464375028132[26] = 0.0;
   out_8344684464375028132[27] = 0.0;
   out_8344684464375028132[28] = 0.0;
   out_8344684464375028132[29] = 0.0;
   out_8344684464375028132[30] = 1.0;
   out_8344684464375028132[31] = 0.0;
   out_8344684464375028132[32] = 0.0;
   out_8344684464375028132[33] = 0.0;
   out_8344684464375028132[34] = 0.0;
   out_8344684464375028132[35] = 0.0;
   out_8344684464375028132[36] = 0.0;
   out_8344684464375028132[37] = 0.0;
   out_8344684464375028132[38] = 0.0;
   out_8344684464375028132[39] = 0.0;
   out_8344684464375028132[40] = 1.0;
   out_8344684464375028132[41] = 0.0;
   out_8344684464375028132[42] = 0.0;
   out_8344684464375028132[43] = 0.0;
   out_8344684464375028132[44] = 0.0;
   out_8344684464375028132[45] = 0.0;
   out_8344684464375028132[46] = 0.0;
   out_8344684464375028132[47] = 0.0;
   out_8344684464375028132[48] = 0.0;
   out_8344684464375028132[49] = 0.0;
   out_8344684464375028132[50] = 1.0;
   out_8344684464375028132[51] = 0.0;
   out_8344684464375028132[52] = 0.0;
   out_8344684464375028132[53] = 0.0;
   out_8344684464375028132[54] = 0.0;
   out_8344684464375028132[55] = 0.0;
   out_8344684464375028132[56] = 0.0;
   out_8344684464375028132[57] = 0.0;
   out_8344684464375028132[58] = 0.0;
   out_8344684464375028132[59] = 0.0;
   out_8344684464375028132[60] = 1.0;
   out_8344684464375028132[61] = 0.0;
   out_8344684464375028132[62] = 0.0;
   out_8344684464375028132[63] = 0.0;
   out_8344684464375028132[64] = 0.0;
   out_8344684464375028132[65] = 0.0;
   out_8344684464375028132[66] = 0.0;
   out_8344684464375028132[67] = 0.0;
   out_8344684464375028132[68] = 0.0;
   out_8344684464375028132[69] = 0.0;
   out_8344684464375028132[70] = 1.0;
   out_8344684464375028132[71] = 0.0;
   out_8344684464375028132[72] = 0.0;
   out_8344684464375028132[73] = 0.0;
   out_8344684464375028132[74] = 0.0;
   out_8344684464375028132[75] = 0.0;
   out_8344684464375028132[76] = 0.0;
   out_8344684464375028132[77] = 0.0;
   out_8344684464375028132[78] = 0.0;
   out_8344684464375028132[79] = 0.0;
   out_8344684464375028132[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_2949132285120758150) {
   out_2949132285120758150[0] = state[0];
   out_2949132285120758150[1] = state[1];
   out_2949132285120758150[2] = state[2];
   out_2949132285120758150[3] = state[3];
   out_2949132285120758150[4] = state[4];
   out_2949132285120758150[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_2949132285120758150[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_2949132285120758150[7] = state[7];
   out_2949132285120758150[8] = state[8];
}
void F_fun(double *state, double dt, double *out_3845759010015306785) {
   out_3845759010015306785[0] = 1;
   out_3845759010015306785[1] = 0;
   out_3845759010015306785[2] = 0;
   out_3845759010015306785[3] = 0;
   out_3845759010015306785[4] = 0;
   out_3845759010015306785[5] = 0;
   out_3845759010015306785[6] = 0;
   out_3845759010015306785[7] = 0;
   out_3845759010015306785[8] = 0;
   out_3845759010015306785[9] = 0;
   out_3845759010015306785[10] = 1;
   out_3845759010015306785[11] = 0;
   out_3845759010015306785[12] = 0;
   out_3845759010015306785[13] = 0;
   out_3845759010015306785[14] = 0;
   out_3845759010015306785[15] = 0;
   out_3845759010015306785[16] = 0;
   out_3845759010015306785[17] = 0;
   out_3845759010015306785[18] = 0;
   out_3845759010015306785[19] = 0;
   out_3845759010015306785[20] = 1;
   out_3845759010015306785[21] = 0;
   out_3845759010015306785[22] = 0;
   out_3845759010015306785[23] = 0;
   out_3845759010015306785[24] = 0;
   out_3845759010015306785[25] = 0;
   out_3845759010015306785[26] = 0;
   out_3845759010015306785[27] = 0;
   out_3845759010015306785[28] = 0;
   out_3845759010015306785[29] = 0;
   out_3845759010015306785[30] = 1;
   out_3845759010015306785[31] = 0;
   out_3845759010015306785[32] = 0;
   out_3845759010015306785[33] = 0;
   out_3845759010015306785[34] = 0;
   out_3845759010015306785[35] = 0;
   out_3845759010015306785[36] = 0;
   out_3845759010015306785[37] = 0;
   out_3845759010015306785[38] = 0;
   out_3845759010015306785[39] = 0;
   out_3845759010015306785[40] = 1;
   out_3845759010015306785[41] = 0;
   out_3845759010015306785[42] = 0;
   out_3845759010015306785[43] = 0;
   out_3845759010015306785[44] = 0;
   out_3845759010015306785[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_3845759010015306785[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_3845759010015306785[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_3845759010015306785[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_3845759010015306785[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_3845759010015306785[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_3845759010015306785[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_3845759010015306785[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_3845759010015306785[53] = -9.8100000000000005*dt;
   out_3845759010015306785[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_3845759010015306785[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_3845759010015306785[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3845759010015306785[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3845759010015306785[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_3845759010015306785[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_3845759010015306785[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_3845759010015306785[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3845759010015306785[62] = 0;
   out_3845759010015306785[63] = 0;
   out_3845759010015306785[64] = 0;
   out_3845759010015306785[65] = 0;
   out_3845759010015306785[66] = 0;
   out_3845759010015306785[67] = 0;
   out_3845759010015306785[68] = 0;
   out_3845759010015306785[69] = 0;
   out_3845759010015306785[70] = 1;
   out_3845759010015306785[71] = 0;
   out_3845759010015306785[72] = 0;
   out_3845759010015306785[73] = 0;
   out_3845759010015306785[74] = 0;
   out_3845759010015306785[75] = 0;
   out_3845759010015306785[76] = 0;
   out_3845759010015306785[77] = 0;
   out_3845759010015306785[78] = 0;
   out_3845759010015306785[79] = 0;
   out_3845759010015306785[80] = 1;
}
void h_25(double *state, double *unused, double *out_5895820651173676631) {
   out_5895820651173676631[0] = state[6];
}
void H_25(double *state, double *unused, double *out_3605036649444493533) {
   out_3605036649444493533[0] = 0;
   out_3605036649444493533[1] = 0;
   out_3605036649444493533[2] = 0;
   out_3605036649444493533[3] = 0;
   out_3605036649444493533[4] = 0;
   out_3605036649444493533[5] = 0;
   out_3605036649444493533[6] = 1;
   out_3605036649444493533[7] = 0;
   out_3605036649444493533[8] = 0;
}
void h_24(double *state, double *unused, double *out_482928573552333087) {
   out_482928573552333087[0] = state[4];
   out_482928573552333087[1] = state[5];
}
void H_24(double *state, double *unused, double *out_3134579167401154809) {
   out_3134579167401154809[0] = 0;
   out_3134579167401154809[1] = 0;
   out_3134579167401154809[2] = 0;
   out_3134579167401154809[3] = 0;
   out_3134579167401154809[4] = 1;
   out_3134579167401154809[5] = 0;
   out_3134579167401154809[6] = 0;
   out_3134579167401154809[7] = 0;
   out_3134579167401154809[8] = 0;
   out_3134579167401154809[9] = 0;
   out_3134579167401154809[10] = 0;
   out_3134579167401154809[11] = 0;
   out_3134579167401154809[12] = 0;
   out_3134579167401154809[13] = 0;
   out_3134579167401154809[14] = 1;
   out_3134579167401154809[15] = 0;
   out_3134579167401154809[16] = 0;
   out_3134579167401154809[17] = 0;
}
void h_30(double *state, double *unused, double *out_2258371122919654281) {
   out_2258371122919654281[0] = state[4];
}
void H_30(double *state, double *unused, double *out_3475697702301253463) {
   out_3475697702301253463[0] = 0;
   out_3475697702301253463[1] = 0;
   out_3475697702301253463[2] = 0;
   out_3475697702301253463[3] = 0;
   out_3475697702301253463[4] = 1;
   out_3475697702301253463[5] = 0;
   out_3475697702301253463[6] = 0;
   out_3475697702301253463[7] = 0;
   out_3475697702301253463[8] = 0;
}
void h_26(double *state, double *unused, double *out_6723598049087186484) {
   out_6723598049087186484[0] = state[7];
}
void H_26(double *state, double *unused, double *out_136466669429562691) {
   out_136466669429562691[0] = 0;
   out_136466669429562691[1] = 0;
   out_136466669429562691[2] = 0;
   out_136466669429562691[3] = 0;
   out_136466669429562691[4] = 0;
   out_136466669429562691[5] = 0;
   out_136466669429562691[6] = 0;
   out_136466669429562691[7] = 1;
   out_136466669429562691[8] = 0;
}
void h_27(double *state, double *unused, double *out_8500225971982374282) {
   out_8500225971982374282[0] = state[3];
}
void H_27(double *state, double *unused, double *out_1300934390500828552) {
   out_1300934390500828552[0] = 0;
   out_1300934390500828552[1] = 0;
   out_1300934390500828552[2] = 0;
   out_1300934390500828552[3] = 1;
   out_1300934390500828552[4] = 0;
   out_1300934390500828552[5] = 0;
   out_1300934390500828552[6] = 0;
   out_1300934390500828552[7] = 0;
   out_1300934390500828552[8] = 0;
}
void h_29(double *state, double *unused, double *out_2743302144741191364) {
   out_2743302144741191364[0] = state[1];
}
void H_29(double *state, double *unused, double *out_412428336368722481) {
   out_412428336368722481[0] = 0;
   out_412428336368722481[1] = 1;
   out_412428336368722481[2] = 0;
   out_412428336368722481[3] = 0;
   out_412428336368722481[4] = 0;
   out_412428336368722481[5] = 0;
   out_412428336368722481[6] = 0;
   out_412428336368722481[7] = 0;
   out_412428336368722481[8] = 0;
}
void h_28(double *state, double *unused, double *out_2511374667298476521) {
   out_2511374667298476521[0] = state[0];
}
void H_28(double *state, double *unused, double *out_5494827353438253055) {
   out_5494827353438253055[0] = 1;
   out_5494827353438253055[1] = 0;
   out_5494827353438253055[2] = 0;
   out_5494827353438253055[3] = 0;
   out_5494827353438253055[4] = 0;
   out_5494827353438253055[5] = 0;
   out_5494827353438253055[6] = 0;
   out_5494827353438253055[7] = 0;
   out_5494827353438253055[8] = 0;
}
void h_31(double *state, double *unused, double *out_4669650771781825800) {
   out_4669650771781825800[0] = state[8];
}
void H_31(double *state, double *unused, double *out_3635682611321453961) {
   out_3635682611321453961[0] = 0;
   out_3635682611321453961[1] = 0;
   out_3635682611321453961[2] = 0;
   out_3635682611321453961[3] = 0;
   out_3635682611321453961[4] = 0;
   out_3635682611321453961[5] = 0;
   out_3635682611321453961[6] = 0;
   out_3635682611321453961[7] = 0;
   out_3635682611321453961[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_7892580644768456538) {
  err_fun(nom_x, delta_x, out_7892580644768456538);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_5204839923779822433) {
  inv_err_fun(nom_x, true_x, out_5204839923779822433);
}
void car_H_mod_fun(double *state, double *out_8344684464375028132) {
  H_mod_fun(state, out_8344684464375028132);
}
void car_f_fun(double *state, double dt, double *out_2949132285120758150) {
  f_fun(state,  dt, out_2949132285120758150);
}
void car_F_fun(double *state, double dt, double *out_3845759010015306785) {
  F_fun(state,  dt, out_3845759010015306785);
}
void car_h_25(double *state, double *unused, double *out_5895820651173676631) {
  h_25(state, unused, out_5895820651173676631);
}
void car_H_25(double *state, double *unused, double *out_3605036649444493533) {
  H_25(state, unused, out_3605036649444493533);
}
void car_h_24(double *state, double *unused, double *out_482928573552333087) {
  h_24(state, unused, out_482928573552333087);
}
void car_H_24(double *state, double *unused, double *out_3134579167401154809) {
  H_24(state, unused, out_3134579167401154809);
}
void car_h_30(double *state, double *unused, double *out_2258371122919654281) {
  h_30(state, unused, out_2258371122919654281);
}
void car_H_30(double *state, double *unused, double *out_3475697702301253463) {
  H_30(state, unused, out_3475697702301253463);
}
void car_h_26(double *state, double *unused, double *out_6723598049087186484) {
  h_26(state, unused, out_6723598049087186484);
}
void car_H_26(double *state, double *unused, double *out_136466669429562691) {
  H_26(state, unused, out_136466669429562691);
}
void car_h_27(double *state, double *unused, double *out_8500225971982374282) {
  h_27(state, unused, out_8500225971982374282);
}
void car_H_27(double *state, double *unused, double *out_1300934390500828552) {
  H_27(state, unused, out_1300934390500828552);
}
void car_h_29(double *state, double *unused, double *out_2743302144741191364) {
  h_29(state, unused, out_2743302144741191364);
}
void car_H_29(double *state, double *unused, double *out_412428336368722481) {
  H_29(state, unused, out_412428336368722481);
}
void car_h_28(double *state, double *unused, double *out_2511374667298476521) {
  h_28(state, unused, out_2511374667298476521);
}
void car_H_28(double *state, double *unused, double *out_5494827353438253055) {
  H_28(state, unused, out_5494827353438253055);
}
void car_h_31(double *state, double *unused, double *out_4669650771781825800) {
  h_31(state, unused, out_4669650771781825800);
}
void car_H_31(double *state, double *unused, double *out_3635682611321453961) {
  H_31(state, unused, out_3635682611321453961);
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
