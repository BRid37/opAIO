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
void err_fun(double *nom_x, double *delta_x, double *out_6739729583278533622) {
   out_6739729583278533622[0] = delta_x[0] + nom_x[0];
   out_6739729583278533622[1] = delta_x[1] + nom_x[1];
   out_6739729583278533622[2] = delta_x[2] + nom_x[2];
   out_6739729583278533622[3] = delta_x[3] + nom_x[3];
   out_6739729583278533622[4] = delta_x[4] + nom_x[4];
   out_6739729583278533622[5] = delta_x[5] + nom_x[5];
   out_6739729583278533622[6] = delta_x[6] + nom_x[6];
   out_6739729583278533622[7] = delta_x[7] + nom_x[7];
   out_6739729583278533622[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_4580221091051696781) {
   out_4580221091051696781[0] = -nom_x[0] + true_x[0];
   out_4580221091051696781[1] = -nom_x[1] + true_x[1];
   out_4580221091051696781[2] = -nom_x[2] + true_x[2];
   out_4580221091051696781[3] = -nom_x[3] + true_x[3];
   out_4580221091051696781[4] = -nom_x[4] + true_x[4];
   out_4580221091051696781[5] = -nom_x[5] + true_x[5];
   out_4580221091051696781[6] = -nom_x[6] + true_x[6];
   out_4580221091051696781[7] = -nom_x[7] + true_x[7];
   out_4580221091051696781[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_9179971792990499705) {
   out_9179971792990499705[0] = 1.0;
   out_9179971792990499705[1] = 0.0;
   out_9179971792990499705[2] = 0.0;
   out_9179971792990499705[3] = 0.0;
   out_9179971792990499705[4] = 0.0;
   out_9179971792990499705[5] = 0.0;
   out_9179971792990499705[6] = 0.0;
   out_9179971792990499705[7] = 0.0;
   out_9179971792990499705[8] = 0.0;
   out_9179971792990499705[9] = 0.0;
   out_9179971792990499705[10] = 1.0;
   out_9179971792990499705[11] = 0.0;
   out_9179971792990499705[12] = 0.0;
   out_9179971792990499705[13] = 0.0;
   out_9179971792990499705[14] = 0.0;
   out_9179971792990499705[15] = 0.0;
   out_9179971792990499705[16] = 0.0;
   out_9179971792990499705[17] = 0.0;
   out_9179971792990499705[18] = 0.0;
   out_9179971792990499705[19] = 0.0;
   out_9179971792990499705[20] = 1.0;
   out_9179971792990499705[21] = 0.0;
   out_9179971792990499705[22] = 0.0;
   out_9179971792990499705[23] = 0.0;
   out_9179971792990499705[24] = 0.0;
   out_9179971792990499705[25] = 0.0;
   out_9179971792990499705[26] = 0.0;
   out_9179971792990499705[27] = 0.0;
   out_9179971792990499705[28] = 0.0;
   out_9179971792990499705[29] = 0.0;
   out_9179971792990499705[30] = 1.0;
   out_9179971792990499705[31] = 0.0;
   out_9179971792990499705[32] = 0.0;
   out_9179971792990499705[33] = 0.0;
   out_9179971792990499705[34] = 0.0;
   out_9179971792990499705[35] = 0.0;
   out_9179971792990499705[36] = 0.0;
   out_9179971792990499705[37] = 0.0;
   out_9179971792990499705[38] = 0.0;
   out_9179971792990499705[39] = 0.0;
   out_9179971792990499705[40] = 1.0;
   out_9179971792990499705[41] = 0.0;
   out_9179971792990499705[42] = 0.0;
   out_9179971792990499705[43] = 0.0;
   out_9179971792990499705[44] = 0.0;
   out_9179971792990499705[45] = 0.0;
   out_9179971792990499705[46] = 0.0;
   out_9179971792990499705[47] = 0.0;
   out_9179971792990499705[48] = 0.0;
   out_9179971792990499705[49] = 0.0;
   out_9179971792990499705[50] = 1.0;
   out_9179971792990499705[51] = 0.0;
   out_9179971792990499705[52] = 0.0;
   out_9179971792990499705[53] = 0.0;
   out_9179971792990499705[54] = 0.0;
   out_9179971792990499705[55] = 0.0;
   out_9179971792990499705[56] = 0.0;
   out_9179971792990499705[57] = 0.0;
   out_9179971792990499705[58] = 0.0;
   out_9179971792990499705[59] = 0.0;
   out_9179971792990499705[60] = 1.0;
   out_9179971792990499705[61] = 0.0;
   out_9179971792990499705[62] = 0.0;
   out_9179971792990499705[63] = 0.0;
   out_9179971792990499705[64] = 0.0;
   out_9179971792990499705[65] = 0.0;
   out_9179971792990499705[66] = 0.0;
   out_9179971792990499705[67] = 0.0;
   out_9179971792990499705[68] = 0.0;
   out_9179971792990499705[69] = 0.0;
   out_9179971792990499705[70] = 1.0;
   out_9179971792990499705[71] = 0.0;
   out_9179971792990499705[72] = 0.0;
   out_9179971792990499705[73] = 0.0;
   out_9179971792990499705[74] = 0.0;
   out_9179971792990499705[75] = 0.0;
   out_9179971792990499705[76] = 0.0;
   out_9179971792990499705[77] = 0.0;
   out_9179971792990499705[78] = 0.0;
   out_9179971792990499705[79] = 0.0;
   out_9179971792990499705[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_6748960235092935949) {
   out_6748960235092935949[0] = state[0];
   out_6748960235092935949[1] = state[1];
   out_6748960235092935949[2] = state[2];
   out_6748960235092935949[3] = state[3];
   out_6748960235092935949[4] = state[4];
   out_6748960235092935949[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_6748960235092935949[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_6748960235092935949[7] = state[7];
   out_6748960235092935949[8] = state[8];
}
void F_fun(double *state, double dt, double *out_2096886756008492430) {
   out_2096886756008492430[0] = 1;
   out_2096886756008492430[1] = 0;
   out_2096886756008492430[2] = 0;
   out_2096886756008492430[3] = 0;
   out_2096886756008492430[4] = 0;
   out_2096886756008492430[5] = 0;
   out_2096886756008492430[6] = 0;
   out_2096886756008492430[7] = 0;
   out_2096886756008492430[8] = 0;
   out_2096886756008492430[9] = 0;
   out_2096886756008492430[10] = 1;
   out_2096886756008492430[11] = 0;
   out_2096886756008492430[12] = 0;
   out_2096886756008492430[13] = 0;
   out_2096886756008492430[14] = 0;
   out_2096886756008492430[15] = 0;
   out_2096886756008492430[16] = 0;
   out_2096886756008492430[17] = 0;
   out_2096886756008492430[18] = 0;
   out_2096886756008492430[19] = 0;
   out_2096886756008492430[20] = 1;
   out_2096886756008492430[21] = 0;
   out_2096886756008492430[22] = 0;
   out_2096886756008492430[23] = 0;
   out_2096886756008492430[24] = 0;
   out_2096886756008492430[25] = 0;
   out_2096886756008492430[26] = 0;
   out_2096886756008492430[27] = 0;
   out_2096886756008492430[28] = 0;
   out_2096886756008492430[29] = 0;
   out_2096886756008492430[30] = 1;
   out_2096886756008492430[31] = 0;
   out_2096886756008492430[32] = 0;
   out_2096886756008492430[33] = 0;
   out_2096886756008492430[34] = 0;
   out_2096886756008492430[35] = 0;
   out_2096886756008492430[36] = 0;
   out_2096886756008492430[37] = 0;
   out_2096886756008492430[38] = 0;
   out_2096886756008492430[39] = 0;
   out_2096886756008492430[40] = 1;
   out_2096886756008492430[41] = 0;
   out_2096886756008492430[42] = 0;
   out_2096886756008492430[43] = 0;
   out_2096886756008492430[44] = 0;
   out_2096886756008492430[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_2096886756008492430[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_2096886756008492430[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_2096886756008492430[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_2096886756008492430[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_2096886756008492430[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_2096886756008492430[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_2096886756008492430[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_2096886756008492430[53] = -9.8000000000000007*dt;
   out_2096886756008492430[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_2096886756008492430[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_2096886756008492430[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2096886756008492430[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2096886756008492430[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_2096886756008492430[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_2096886756008492430[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_2096886756008492430[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2096886756008492430[62] = 0;
   out_2096886756008492430[63] = 0;
   out_2096886756008492430[64] = 0;
   out_2096886756008492430[65] = 0;
   out_2096886756008492430[66] = 0;
   out_2096886756008492430[67] = 0;
   out_2096886756008492430[68] = 0;
   out_2096886756008492430[69] = 0;
   out_2096886756008492430[70] = 1;
   out_2096886756008492430[71] = 0;
   out_2096886756008492430[72] = 0;
   out_2096886756008492430[73] = 0;
   out_2096886756008492430[74] = 0;
   out_2096886756008492430[75] = 0;
   out_2096886756008492430[76] = 0;
   out_2096886756008492430[77] = 0;
   out_2096886756008492430[78] = 0;
   out_2096886756008492430[79] = 0;
   out_2096886756008492430[80] = 1;
}
void h_25(double *state, double *unused, double *out_553976550253322035) {
   out_553976550253322035[0] = state[6];
}
void H_25(double *state, double *unused, double *out_7111446507229786949) {
   out_7111446507229786949[0] = 0;
   out_7111446507229786949[1] = 0;
   out_7111446507229786949[2] = 0;
   out_7111446507229786949[3] = 0;
   out_7111446507229786949[4] = 0;
   out_7111446507229786949[5] = 0;
   out_7111446507229786949[6] = 1;
   out_7111446507229786949[7] = 0;
   out_7111446507229786949[8] = 0;
}
void h_24(double *state, double *unused, double *out_1175334170647651268) {
   out_1175334170647651268[0] = state[4];
   out_1175334170647651268[1] = state[5];
}
void H_24(double *state, double *unused, double *out_910413827378625523) {
   out_910413827378625523[0] = 0;
   out_910413827378625523[1] = 0;
   out_910413827378625523[2] = 0;
   out_910413827378625523[3] = 0;
   out_910413827378625523[4] = 1;
   out_910413827378625523[5] = 0;
   out_910413827378625523[6] = 0;
   out_910413827378625523[7] = 0;
   out_910413827378625523[8] = 0;
   out_910413827378625523[9] = 0;
   out_910413827378625523[10] = 0;
   out_910413827378625523[11] = 0;
   out_910413827378625523[12] = 0;
   out_910413827378625523[13] = 0;
   out_910413827378625523[14] = 1;
   out_910413827378625523[15] = 0;
   out_910413827378625523[16] = 0;
   out_910413827378625523[17] = 0;
}
void h_30(double *state, double *unused, double *out_3501702540608806996) {
   out_3501702540608806996[0] = state[4];
}
void H_30(double *state, double *unused, double *out_6982107560086546879) {
   out_6982107560086546879[0] = 0;
   out_6982107560086546879[1] = 0;
   out_6982107560086546879[2] = 0;
   out_6982107560086546879[3] = 0;
   out_6982107560086546879[4] = 1;
   out_6982107560086546879[5] = 0;
   out_6982107560086546879[6] = 0;
   out_6982107560086546879[7] = 0;
   out_6982107560086546879[8] = 0;
}
void h_26(double *state, double *unused, double *out_7228212129951677070) {
   out_7228212129951677070[0] = state[7];
}
void H_26(double *state, double *unused, double *out_3369943188355730725) {
   out_3369943188355730725[0] = 0;
   out_3369943188355730725[1] = 0;
   out_3369943188355730725[2] = 0;
   out_3369943188355730725[3] = 0;
   out_3369943188355730725[4] = 0;
   out_3369943188355730725[5] = 0;
   out_3369943188355730725[6] = 0;
   out_3369943188355730725[7] = 1;
   out_3369943188355730725[8] = 0;
}
void h_27(double *state, double *unused, double *out_2050428770555375616) {
   out_2050428770555375616[0] = state[3];
}
void H_27(double *state, double *unused, double *out_4807344248286121968) {
   out_4807344248286121968[0] = 0;
   out_4807344248286121968[1] = 0;
   out_4807344248286121968[2] = 0;
   out_4807344248286121968[3] = 1;
   out_4807344248286121968[4] = 0;
   out_4807344248286121968[5] = 0;
   out_4807344248286121968[6] = 0;
   out_4807344248286121968[7] = 0;
   out_4807344248286121968[8] = 0;
}
void h_29(double *state, double *unused, double *out_4105018425285284513) {
   out_4105018425285284513[0] = state[1];
}
void H_29(double *state, double *unused, double *out_3093981521416570935) {
   out_3093981521416570935[0] = 0;
   out_3093981521416570935[1] = 1;
   out_3093981521416570935[2] = 0;
   out_3093981521416570935[3] = 0;
   out_3093981521416570935[4] = 0;
   out_3093981521416570935[5] = 0;
   out_3093981521416570935[6] = 0;
   out_3093981521416570935[7] = 0;
   out_3093981521416570935[8] = 0;
}
void h_28(double *state, double *unused, double *out_7414346131147335235) {
   out_7414346131147335235[0] = state[0];
}
void H_28(double *state, double *unused, double *out_5057611792981897186) {
   out_5057611792981897186[0] = 1;
   out_5057611792981897186[1] = 0;
   out_5057611792981897186[2] = 0;
   out_5057611792981897186[3] = 0;
   out_5057611792981897186[4] = 0;
   out_5057611792981897186[5] = 0;
   out_5057611792981897186[6] = 0;
   out_5057611792981897186[7] = 0;
   out_5057611792981897186[8] = 0;
}
void h_31(double *state, double *unused, double *out_7327296100500727150) {
   out_7327296100500727150[0] = state[8];
}
void H_31(double *state, double *unused, double *out_7142092469106747377) {
   out_7142092469106747377[0] = 0;
   out_7142092469106747377[1] = 0;
   out_7142092469106747377[2] = 0;
   out_7142092469106747377[3] = 0;
   out_7142092469106747377[4] = 0;
   out_7142092469106747377[5] = 0;
   out_7142092469106747377[6] = 0;
   out_7142092469106747377[7] = 0;
   out_7142092469106747377[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_6739729583278533622) {
  err_fun(nom_x, delta_x, out_6739729583278533622);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_4580221091051696781) {
  inv_err_fun(nom_x, true_x, out_4580221091051696781);
}
void car_H_mod_fun(double *state, double *out_9179971792990499705) {
  H_mod_fun(state, out_9179971792990499705);
}
void car_f_fun(double *state, double dt, double *out_6748960235092935949) {
  f_fun(state,  dt, out_6748960235092935949);
}
void car_F_fun(double *state, double dt, double *out_2096886756008492430) {
  F_fun(state,  dt, out_2096886756008492430);
}
void car_h_25(double *state, double *unused, double *out_553976550253322035) {
  h_25(state, unused, out_553976550253322035);
}
void car_H_25(double *state, double *unused, double *out_7111446507229786949) {
  H_25(state, unused, out_7111446507229786949);
}
void car_h_24(double *state, double *unused, double *out_1175334170647651268) {
  h_24(state, unused, out_1175334170647651268);
}
void car_H_24(double *state, double *unused, double *out_910413827378625523) {
  H_24(state, unused, out_910413827378625523);
}
void car_h_30(double *state, double *unused, double *out_3501702540608806996) {
  h_30(state, unused, out_3501702540608806996);
}
void car_H_30(double *state, double *unused, double *out_6982107560086546879) {
  H_30(state, unused, out_6982107560086546879);
}
void car_h_26(double *state, double *unused, double *out_7228212129951677070) {
  h_26(state, unused, out_7228212129951677070);
}
void car_H_26(double *state, double *unused, double *out_3369943188355730725) {
  H_26(state, unused, out_3369943188355730725);
}
void car_h_27(double *state, double *unused, double *out_2050428770555375616) {
  h_27(state, unused, out_2050428770555375616);
}
void car_H_27(double *state, double *unused, double *out_4807344248286121968) {
  H_27(state, unused, out_4807344248286121968);
}
void car_h_29(double *state, double *unused, double *out_4105018425285284513) {
  h_29(state, unused, out_4105018425285284513);
}
void car_H_29(double *state, double *unused, double *out_3093981521416570935) {
  H_29(state, unused, out_3093981521416570935);
}
void car_h_28(double *state, double *unused, double *out_7414346131147335235) {
  h_28(state, unused, out_7414346131147335235);
}
void car_H_28(double *state, double *unused, double *out_5057611792981897186) {
  H_28(state, unused, out_5057611792981897186);
}
void car_h_31(double *state, double *unused, double *out_7327296100500727150) {
  h_31(state, unused, out_7327296100500727150);
}
void car_H_31(double *state, double *unused, double *out_7142092469106747377) {
  H_31(state, unused, out_7142092469106747377);
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
