#include "pose.h"

namespace {
#define DIM 18
#define EDIM 18
#define MEDIM 18
typedef void (*Hfun)(double *, double *, double *);
const static double MAHA_THRESH_4 = 7.814727903251177;
const static double MAHA_THRESH_10 = 7.814727903251177;
const static double MAHA_THRESH_13 = 7.814727903251177;
const static double MAHA_THRESH_14 = 7.814727903251177;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_2671738792046849383) {
   out_2671738792046849383[0] = delta_x[0] + nom_x[0];
   out_2671738792046849383[1] = delta_x[1] + nom_x[1];
   out_2671738792046849383[2] = delta_x[2] + nom_x[2];
   out_2671738792046849383[3] = delta_x[3] + nom_x[3];
   out_2671738792046849383[4] = delta_x[4] + nom_x[4];
   out_2671738792046849383[5] = delta_x[5] + nom_x[5];
   out_2671738792046849383[6] = delta_x[6] + nom_x[6];
   out_2671738792046849383[7] = delta_x[7] + nom_x[7];
   out_2671738792046849383[8] = delta_x[8] + nom_x[8];
   out_2671738792046849383[9] = delta_x[9] + nom_x[9];
   out_2671738792046849383[10] = delta_x[10] + nom_x[10];
   out_2671738792046849383[11] = delta_x[11] + nom_x[11];
   out_2671738792046849383[12] = delta_x[12] + nom_x[12];
   out_2671738792046849383[13] = delta_x[13] + nom_x[13];
   out_2671738792046849383[14] = delta_x[14] + nom_x[14];
   out_2671738792046849383[15] = delta_x[15] + nom_x[15];
   out_2671738792046849383[16] = delta_x[16] + nom_x[16];
   out_2671738792046849383[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_424188773766453759) {
   out_424188773766453759[0] = -nom_x[0] + true_x[0];
   out_424188773766453759[1] = -nom_x[1] + true_x[1];
   out_424188773766453759[2] = -nom_x[2] + true_x[2];
   out_424188773766453759[3] = -nom_x[3] + true_x[3];
   out_424188773766453759[4] = -nom_x[4] + true_x[4];
   out_424188773766453759[5] = -nom_x[5] + true_x[5];
   out_424188773766453759[6] = -nom_x[6] + true_x[6];
   out_424188773766453759[7] = -nom_x[7] + true_x[7];
   out_424188773766453759[8] = -nom_x[8] + true_x[8];
   out_424188773766453759[9] = -nom_x[9] + true_x[9];
   out_424188773766453759[10] = -nom_x[10] + true_x[10];
   out_424188773766453759[11] = -nom_x[11] + true_x[11];
   out_424188773766453759[12] = -nom_x[12] + true_x[12];
   out_424188773766453759[13] = -nom_x[13] + true_x[13];
   out_424188773766453759[14] = -nom_x[14] + true_x[14];
   out_424188773766453759[15] = -nom_x[15] + true_x[15];
   out_424188773766453759[16] = -nom_x[16] + true_x[16];
   out_424188773766453759[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_7263482371397085867) {
   out_7263482371397085867[0] = 1.0;
   out_7263482371397085867[1] = 0.0;
   out_7263482371397085867[2] = 0.0;
   out_7263482371397085867[3] = 0.0;
   out_7263482371397085867[4] = 0.0;
   out_7263482371397085867[5] = 0.0;
   out_7263482371397085867[6] = 0.0;
   out_7263482371397085867[7] = 0.0;
   out_7263482371397085867[8] = 0.0;
   out_7263482371397085867[9] = 0.0;
   out_7263482371397085867[10] = 0.0;
   out_7263482371397085867[11] = 0.0;
   out_7263482371397085867[12] = 0.0;
   out_7263482371397085867[13] = 0.0;
   out_7263482371397085867[14] = 0.0;
   out_7263482371397085867[15] = 0.0;
   out_7263482371397085867[16] = 0.0;
   out_7263482371397085867[17] = 0.0;
   out_7263482371397085867[18] = 0.0;
   out_7263482371397085867[19] = 1.0;
   out_7263482371397085867[20] = 0.0;
   out_7263482371397085867[21] = 0.0;
   out_7263482371397085867[22] = 0.0;
   out_7263482371397085867[23] = 0.0;
   out_7263482371397085867[24] = 0.0;
   out_7263482371397085867[25] = 0.0;
   out_7263482371397085867[26] = 0.0;
   out_7263482371397085867[27] = 0.0;
   out_7263482371397085867[28] = 0.0;
   out_7263482371397085867[29] = 0.0;
   out_7263482371397085867[30] = 0.0;
   out_7263482371397085867[31] = 0.0;
   out_7263482371397085867[32] = 0.0;
   out_7263482371397085867[33] = 0.0;
   out_7263482371397085867[34] = 0.0;
   out_7263482371397085867[35] = 0.0;
   out_7263482371397085867[36] = 0.0;
   out_7263482371397085867[37] = 0.0;
   out_7263482371397085867[38] = 1.0;
   out_7263482371397085867[39] = 0.0;
   out_7263482371397085867[40] = 0.0;
   out_7263482371397085867[41] = 0.0;
   out_7263482371397085867[42] = 0.0;
   out_7263482371397085867[43] = 0.0;
   out_7263482371397085867[44] = 0.0;
   out_7263482371397085867[45] = 0.0;
   out_7263482371397085867[46] = 0.0;
   out_7263482371397085867[47] = 0.0;
   out_7263482371397085867[48] = 0.0;
   out_7263482371397085867[49] = 0.0;
   out_7263482371397085867[50] = 0.0;
   out_7263482371397085867[51] = 0.0;
   out_7263482371397085867[52] = 0.0;
   out_7263482371397085867[53] = 0.0;
   out_7263482371397085867[54] = 0.0;
   out_7263482371397085867[55] = 0.0;
   out_7263482371397085867[56] = 0.0;
   out_7263482371397085867[57] = 1.0;
   out_7263482371397085867[58] = 0.0;
   out_7263482371397085867[59] = 0.0;
   out_7263482371397085867[60] = 0.0;
   out_7263482371397085867[61] = 0.0;
   out_7263482371397085867[62] = 0.0;
   out_7263482371397085867[63] = 0.0;
   out_7263482371397085867[64] = 0.0;
   out_7263482371397085867[65] = 0.0;
   out_7263482371397085867[66] = 0.0;
   out_7263482371397085867[67] = 0.0;
   out_7263482371397085867[68] = 0.0;
   out_7263482371397085867[69] = 0.0;
   out_7263482371397085867[70] = 0.0;
   out_7263482371397085867[71] = 0.0;
   out_7263482371397085867[72] = 0.0;
   out_7263482371397085867[73] = 0.0;
   out_7263482371397085867[74] = 0.0;
   out_7263482371397085867[75] = 0.0;
   out_7263482371397085867[76] = 1.0;
   out_7263482371397085867[77] = 0.0;
   out_7263482371397085867[78] = 0.0;
   out_7263482371397085867[79] = 0.0;
   out_7263482371397085867[80] = 0.0;
   out_7263482371397085867[81] = 0.0;
   out_7263482371397085867[82] = 0.0;
   out_7263482371397085867[83] = 0.0;
   out_7263482371397085867[84] = 0.0;
   out_7263482371397085867[85] = 0.0;
   out_7263482371397085867[86] = 0.0;
   out_7263482371397085867[87] = 0.0;
   out_7263482371397085867[88] = 0.0;
   out_7263482371397085867[89] = 0.0;
   out_7263482371397085867[90] = 0.0;
   out_7263482371397085867[91] = 0.0;
   out_7263482371397085867[92] = 0.0;
   out_7263482371397085867[93] = 0.0;
   out_7263482371397085867[94] = 0.0;
   out_7263482371397085867[95] = 1.0;
   out_7263482371397085867[96] = 0.0;
   out_7263482371397085867[97] = 0.0;
   out_7263482371397085867[98] = 0.0;
   out_7263482371397085867[99] = 0.0;
   out_7263482371397085867[100] = 0.0;
   out_7263482371397085867[101] = 0.0;
   out_7263482371397085867[102] = 0.0;
   out_7263482371397085867[103] = 0.0;
   out_7263482371397085867[104] = 0.0;
   out_7263482371397085867[105] = 0.0;
   out_7263482371397085867[106] = 0.0;
   out_7263482371397085867[107] = 0.0;
   out_7263482371397085867[108] = 0.0;
   out_7263482371397085867[109] = 0.0;
   out_7263482371397085867[110] = 0.0;
   out_7263482371397085867[111] = 0.0;
   out_7263482371397085867[112] = 0.0;
   out_7263482371397085867[113] = 0.0;
   out_7263482371397085867[114] = 1.0;
   out_7263482371397085867[115] = 0.0;
   out_7263482371397085867[116] = 0.0;
   out_7263482371397085867[117] = 0.0;
   out_7263482371397085867[118] = 0.0;
   out_7263482371397085867[119] = 0.0;
   out_7263482371397085867[120] = 0.0;
   out_7263482371397085867[121] = 0.0;
   out_7263482371397085867[122] = 0.0;
   out_7263482371397085867[123] = 0.0;
   out_7263482371397085867[124] = 0.0;
   out_7263482371397085867[125] = 0.0;
   out_7263482371397085867[126] = 0.0;
   out_7263482371397085867[127] = 0.0;
   out_7263482371397085867[128] = 0.0;
   out_7263482371397085867[129] = 0.0;
   out_7263482371397085867[130] = 0.0;
   out_7263482371397085867[131] = 0.0;
   out_7263482371397085867[132] = 0.0;
   out_7263482371397085867[133] = 1.0;
   out_7263482371397085867[134] = 0.0;
   out_7263482371397085867[135] = 0.0;
   out_7263482371397085867[136] = 0.0;
   out_7263482371397085867[137] = 0.0;
   out_7263482371397085867[138] = 0.0;
   out_7263482371397085867[139] = 0.0;
   out_7263482371397085867[140] = 0.0;
   out_7263482371397085867[141] = 0.0;
   out_7263482371397085867[142] = 0.0;
   out_7263482371397085867[143] = 0.0;
   out_7263482371397085867[144] = 0.0;
   out_7263482371397085867[145] = 0.0;
   out_7263482371397085867[146] = 0.0;
   out_7263482371397085867[147] = 0.0;
   out_7263482371397085867[148] = 0.0;
   out_7263482371397085867[149] = 0.0;
   out_7263482371397085867[150] = 0.0;
   out_7263482371397085867[151] = 0.0;
   out_7263482371397085867[152] = 1.0;
   out_7263482371397085867[153] = 0.0;
   out_7263482371397085867[154] = 0.0;
   out_7263482371397085867[155] = 0.0;
   out_7263482371397085867[156] = 0.0;
   out_7263482371397085867[157] = 0.0;
   out_7263482371397085867[158] = 0.0;
   out_7263482371397085867[159] = 0.0;
   out_7263482371397085867[160] = 0.0;
   out_7263482371397085867[161] = 0.0;
   out_7263482371397085867[162] = 0.0;
   out_7263482371397085867[163] = 0.0;
   out_7263482371397085867[164] = 0.0;
   out_7263482371397085867[165] = 0.0;
   out_7263482371397085867[166] = 0.0;
   out_7263482371397085867[167] = 0.0;
   out_7263482371397085867[168] = 0.0;
   out_7263482371397085867[169] = 0.0;
   out_7263482371397085867[170] = 0.0;
   out_7263482371397085867[171] = 1.0;
   out_7263482371397085867[172] = 0.0;
   out_7263482371397085867[173] = 0.0;
   out_7263482371397085867[174] = 0.0;
   out_7263482371397085867[175] = 0.0;
   out_7263482371397085867[176] = 0.0;
   out_7263482371397085867[177] = 0.0;
   out_7263482371397085867[178] = 0.0;
   out_7263482371397085867[179] = 0.0;
   out_7263482371397085867[180] = 0.0;
   out_7263482371397085867[181] = 0.0;
   out_7263482371397085867[182] = 0.0;
   out_7263482371397085867[183] = 0.0;
   out_7263482371397085867[184] = 0.0;
   out_7263482371397085867[185] = 0.0;
   out_7263482371397085867[186] = 0.0;
   out_7263482371397085867[187] = 0.0;
   out_7263482371397085867[188] = 0.0;
   out_7263482371397085867[189] = 0.0;
   out_7263482371397085867[190] = 1.0;
   out_7263482371397085867[191] = 0.0;
   out_7263482371397085867[192] = 0.0;
   out_7263482371397085867[193] = 0.0;
   out_7263482371397085867[194] = 0.0;
   out_7263482371397085867[195] = 0.0;
   out_7263482371397085867[196] = 0.0;
   out_7263482371397085867[197] = 0.0;
   out_7263482371397085867[198] = 0.0;
   out_7263482371397085867[199] = 0.0;
   out_7263482371397085867[200] = 0.0;
   out_7263482371397085867[201] = 0.0;
   out_7263482371397085867[202] = 0.0;
   out_7263482371397085867[203] = 0.0;
   out_7263482371397085867[204] = 0.0;
   out_7263482371397085867[205] = 0.0;
   out_7263482371397085867[206] = 0.0;
   out_7263482371397085867[207] = 0.0;
   out_7263482371397085867[208] = 0.0;
   out_7263482371397085867[209] = 1.0;
   out_7263482371397085867[210] = 0.0;
   out_7263482371397085867[211] = 0.0;
   out_7263482371397085867[212] = 0.0;
   out_7263482371397085867[213] = 0.0;
   out_7263482371397085867[214] = 0.0;
   out_7263482371397085867[215] = 0.0;
   out_7263482371397085867[216] = 0.0;
   out_7263482371397085867[217] = 0.0;
   out_7263482371397085867[218] = 0.0;
   out_7263482371397085867[219] = 0.0;
   out_7263482371397085867[220] = 0.0;
   out_7263482371397085867[221] = 0.0;
   out_7263482371397085867[222] = 0.0;
   out_7263482371397085867[223] = 0.0;
   out_7263482371397085867[224] = 0.0;
   out_7263482371397085867[225] = 0.0;
   out_7263482371397085867[226] = 0.0;
   out_7263482371397085867[227] = 0.0;
   out_7263482371397085867[228] = 1.0;
   out_7263482371397085867[229] = 0.0;
   out_7263482371397085867[230] = 0.0;
   out_7263482371397085867[231] = 0.0;
   out_7263482371397085867[232] = 0.0;
   out_7263482371397085867[233] = 0.0;
   out_7263482371397085867[234] = 0.0;
   out_7263482371397085867[235] = 0.0;
   out_7263482371397085867[236] = 0.0;
   out_7263482371397085867[237] = 0.0;
   out_7263482371397085867[238] = 0.0;
   out_7263482371397085867[239] = 0.0;
   out_7263482371397085867[240] = 0.0;
   out_7263482371397085867[241] = 0.0;
   out_7263482371397085867[242] = 0.0;
   out_7263482371397085867[243] = 0.0;
   out_7263482371397085867[244] = 0.0;
   out_7263482371397085867[245] = 0.0;
   out_7263482371397085867[246] = 0.0;
   out_7263482371397085867[247] = 1.0;
   out_7263482371397085867[248] = 0.0;
   out_7263482371397085867[249] = 0.0;
   out_7263482371397085867[250] = 0.0;
   out_7263482371397085867[251] = 0.0;
   out_7263482371397085867[252] = 0.0;
   out_7263482371397085867[253] = 0.0;
   out_7263482371397085867[254] = 0.0;
   out_7263482371397085867[255] = 0.0;
   out_7263482371397085867[256] = 0.0;
   out_7263482371397085867[257] = 0.0;
   out_7263482371397085867[258] = 0.0;
   out_7263482371397085867[259] = 0.0;
   out_7263482371397085867[260] = 0.0;
   out_7263482371397085867[261] = 0.0;
   out_7263482371397085867[262] = 0.0;
   out_7263482371397085867[263] = 0.0;
   out_7263482371397085867[264] = 0.0;
   out_7263482371397085867[265] = 0.0;
   out_7263482371397085867[266] = 1.0;
   out_7263482371397085867[267] = 0.0;
   out_7263482371397085867[268] = 0.0;
   out_7263482371397085867[269] = 0.0;
   out_7263482371397085867[270] = 0.0;
   out_7263482371397085867[271] = 0.0;
   out_7263482371397085867[272] = 0.0;
   out_7263482371397085867[273] = 0.0;
   out_7263482371397085867[274] = 0.0;
   out_7263482371397085867[275] = 0.0;
   out_7263482371397085867[276] = 0.0;
   out_7263482371397085867[277] = 0.0;
   out_7263482371397085867[278] = 0.0;
   out_7263482371397085867[279] = 0.0;
   out_7263482371397085867[280] = 0.0;
   out_7263482371397085867[281] = 0.0;
   out_7263482371397085867[282] = 0.0;
   out_7263482371397085867[283] = 0.0;
   out_7263482371397085867[284] = 0.0;
   out_7263482371397085867[285] = 1.0;
   out_7263482371397085867[286] = 0.0;
   out_7263482371397085867[287] = 0.0;
   out_7263482371397085867[288] = 0.0;
   out_7263482371397085867[289] = 0.0;
   out_7263482371397085867[290] = 0.0;
   out_7263482371397085867[291] = 0.0;
   out_7263482371397085867[292] = 0.0;
   out_7263482371397085867[293] = 0.0;
   out_7263482371397085867[294] = 0.0;
   out_7263482371397085867[295] = 0.0;
   out_7263482371397085867[296] = 0.0;
   out_7263482371397085867[297] = 0.0;
   out_7263482371397085867[298] = 0.0;
   out_7263482371397085867[299] = 0.0;
   out_7263482371397085867[300] = 0.0;
   out_7263482371397085867[301] = 0.0;
   out_7263482371397085867[302] = 0.0;
   out_7263482371397085867[303] = 0.0;
   out_7263482371397085867[304] = 1.0;
   out_7263482371397085867[305] = 0.0;
   out_7263482371397085867[306] = 0.0;
   out_7263482371397085867[307] = 0.0;
   out_7263482371397085867[308] = 0.0;
   out_7263482371397085867[309] = 0.0;
   out_7263482371397085867[310] = 0.0;
   out_7263482371397085867[311] = 0.0;
   out_7263482371397085867[312] = 0.0;
   out_7263482371397085867[313] = 0.0;
   out_7263482371397085867[314] = 0.0;
   out_7263482371397085867[315] = 0.0;
   out_7263482371397085867[316] = 0.0;
   out_7263482371397085867[317] = 0.0;
   out_7263482371397085867[318] = 0.0;
   out_7263482371397085867[319] = 0.0;
   out_7263482371397085867[320] = 0.0;
   out_7263482371397085867[321] = 0.0;
   out_7263482371397085867[322] = 0.0;
   out_7263482371397085867[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_5712205142337176613) {
   out_5712205142337176613[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_5712205142337176613[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_5712205142337176613[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_5712205142337176613[3] = dt*state[12] + state[3];
   out_5712205142337176613[4] = dt*state[13] + state[4];
   out_5712205142337176613[5] = dt*state[14] + state[5];
   out_5712205142337176613[6] = state[6];
   out_5712205142337176613[7] = state[7];
   out_5712205142337176613[8] = state[8];
   out_5712205142337176613[9] = state[9];
   out_5712205142337176613[10] = state[10];
   out_5712205142337176613[11] = state[11];
   out_5712205142337176613[12] = state[12];
   out_5712205142337176613[13] = state[13];
   out_5712205142337176613[14] = state[14];
   out_5712205142337176613[15] = state[15];
   out_5712205142337176613[16] = state[16];
   out_5712205142337176613[17] = state[17];
}
void F_fun(double *state, double dt, double *out_3453992788886440929) {
   out_3453992788886440929[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3453992788886440929[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3453992788886440929[2] = 0;
   out_3453992788886440929[3] = 0;
   out_3453992788886440929[4] = 0;
   out_3453992788886440929[5] = 0;
   out_3453992788886440929[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3453992788886440929[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3453992788886440929[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3453992788886440929[9] = 0;
   out_3453992788886440929[10] = 0;
   out_3453992788886440929[11] = 0;
   out_3453992788886440929[12] = 0;
   out_3453992788886440929[13] = 0;
   out_3453992788886440929[14] = 0;
   out_3453992788886440929[15] = 0;
   out_3453992788886440929[16] = 0;
   out_3453992788886440929[17] = 0;
   out_3453992788886440929[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3453992788886440929[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3453992788886440929[20] = 0;
   out_3453992788886440929[21] = 0;
   out_3453992788886440929[22] = 0;
   out_3453992788886440929[23] = 0;
   out_3453992788886440929[24] = 0;
   out_3453992788886440929[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3453992788886440929[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3453992788886440929[27] = 0;
   out_3453992788886440929[28] = 0;
   out_3453992788886440929[29] = 0;
   out_3453992788886440929[30] = 0;
   out_3453992788886440929[31] = 0;
   out_3453992788886440929[32] = 0;
   out_3453992788886440929[33] = 0;
   out_3453992788886440929[34] = 0;
   out_3453992788886440929[35] = 0;
   out_3453992788886440929[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3453992788886440929[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3453992788886440929[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3453992788886440929[39] = 0;
   out_3453992788886440929[40] = 0;
   out_3453992788886440929[41] = 0;
   out_3453992788886440929[42] = 0;
   out_3453992788886440929[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3453992788886440929[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3453992788886440929[45] = 0;
   out_3453992788886440929[46] = 0;
   out_3453992788886440929[47] = 0;
   out_3453992788886440929[48] = 0;
   out_3453992788886440929[49] = 0;
   out_3453992788886440929[50] = 0;
   out_3453992788886440929[51] = 0;
   out_3453992788886440929[52] = 0;
   out_3453992788886440929[53] = 0;
   out_3453992788886440929[54] = 0;
   out_3453992788886440929[55] = 0;
   out_3453992788886440929[56] = 0;
   out_3453992788886440929[57] = 1;
   out_3453992788886440929[58] = 0;
   out_3453992788886440929[59] = 0;
   out_3453992788886440929[60] = 0;
   out_3453992788886440929[61] = 0;
   out_3453992788886440929[62] = 0;
   out_3453992788886440929[63] = 0;
   out_3453992788886440929[64] = 0;
   out_3453992788886440929[65] = 0;
   out_3453992788886440929[66] = dt;
   out_3453992788886440929[67] = 0;
   out_3453992788886440929[68] = 0;
   out_3453992788886440929[69] = 0;
   out_3453992788886440929[70] = 0;
   out_3453992788886440929[71] = 0;
   out_3453992788886440929[72] = 0;
   out_3453992788886440929[73] = 0;
   out_3453992788886440929[74] = 0;
   out_3453992788886440929[75] = 0;
   out_3453992788886440929[76] = 1;
   out_3453992788886440929[77] = 0;
   out_3453992788886440929[78] = 0;
   out_3453992788886440929[79] = 0;
   out_3453992788886440929[80] = 0;
   out_3453992788886440929[81] = 0;
   out_3453992788886440929[82] = 0;
   out_3453992788886440929[83] = 0;
   out_3453992788886440929[84] = 0;
   out_3453992788886440929[85] = dt;
   out_3453992788886440929[86] = 0;
   out_3453992788886440929[87] = 0;
   out_3453992788886440929[88] = 0;
   out_3453992788886440929[89] = 0;
   out_3453992788886440929[90] = 0;
   out_3453992788886440929[91] = 0;
   out_3453992788886440929[92] = 0;
   out_3453992788886440929[93] = 0;
   out_3453992788886440929[94] = 0;
   out_3453992788886440929[95] = 1;
   out_3453992788886440929[96] = 0;
   out_3453992788886440929[97] = 0;
   out_3453992788886440929[98] = 0;
   out_3453992788886440929[99] = 0;
   out_3453992788886440929[100] = 0;
   out_3453992788886440929[101] = 0;
   out_3453992788886440929[102] = 0;
   out_3453992788886440929[103] = 0;
   out_3453992788886440929[104] = dt;
   out_3453992788886440929[105] = 0;
   out_3453992788886440929[106] = 0;
   out_3453992788886440929[107] = 0;
   out_3453992788886440929[108] = 0;
   out_3453992788886440929[109] = 0;
   out_3453992788886440929[110] = 0;
   out_3453992788886440929[111] = 0;
   out_3453992788886440929[112] = 0;
   out_3453992788886440929[113] = 0;
   out_3453992788886440929[114] = 1;
   out_3453992788886440929[115] = 0;
   out_3453992788886440929[116] = 0;
   out_3453992788886440929[117] = 0;
   out_3453992788886440929[118] = 0;
   out_3453992788886440929[119] = 0;
   out_3453992788886440929[120] = 0;
   out_3453992788886440929[121] = 0;
   out_3453992788886440929[122] = 0;
   out_3453992788886440929[123] = 0;
   out_3453992788886440929[124] = 0;
   out_3453992788886440929[125] = 0;
   out_3453992788886440929[126] = 0;
   out_3453992788886440929[127] = 0;
   out_3453992788886440929[128] = 0;
   out_3453992788886440929[129] = 0;
   out_3453992788886440929[130] = 0;
   out_3453992788886440929[131] = 0;
   out_3453992788886440929[132] = 0;
   out_3453992788886440929[133] = 1;
   out_3453992788886440929[134] = 0;
   out_3453992788886440929[135] = 0;
   out_3453992788886440929[136] = 0;
   out_3453992788886440929[137] = 0;
   out_3453992788886440929[138] = 0;
   out_3453992788886440929[139] = 0;
   out_3453992788886440929[140] = 0;
   out_3453992788886440929[141] = 0;
   out_3453992788886440929[142] = 0;
   out_3453992788886440929[143] = 0;
   out_3453992788886440929[144] = 0;
   out_3453992788886440929[145] = 0;
   out_3453992788886440929[146] = 0;
   out_3453992788886440929[147] = 0;
   out_3453992788886440929[148] = 0;
   out_3453992788886440929[149] = 0;
   out_3453992788886440929[150] = 0;
   out_3453992788886440929[151] = 0;
   out_3453992788886440929[152] = 1;
   out_3453992788886440929[153] = 0;
   out_3453992788886440929[154] = 0;
   out_3453992788886440929[155] = 0;
   out_3453992788886440929[156] = 0;
   out_3453992788886440929[157] = 0;
   out_3453992788886440929[158] = 0;
   out_3453992788886440929[159] = 0;
   out_3453992788886440929[160] = 0;
   out_3453992788886440929[161] = 0;
   out_3453992788886440929[162] = 0;
   out_3453992788886440929[163] = 0;
   out_3453992788886440929[164] = 0;
   out_3453992788886440929[165] = 0;
   out_3453992788886440929[166] = 0;
   out_3453992788886440929[167] = 0;
   out_3453992788886440929[168] = 0;
   out_3453992788886440929[169] = 0;
   out_3453992788886440929[170] = 0;
   out_3453992788886440929[171] = 1;
   out_3453992788886440929[172] = 0;
   out_3453992788886440929[173] = 0;
   out_3453992788886440929[174] = 0;
   out_3453992788886440929[175] = 0;
   out_3453992788886440929[176] = 0;
   out_3453992788886440929[177] = 0;
   out_3453992788886440929[178] = 0;
   out_3453992788886440929[179] = 0;
   out_3453992788886440929[180] = 0;
   out_3453992788886440929[181] = 0;
   out_3453992788886440929[182] = 0;
   out_3453992788886440929[183] = 0;
   out_3453992788886440929[184] = 0;
   out_3453992788886440929[185] = 0;
   out_3453992788886440929[186] = 0;
   out_3453992788886440929[187] = 0;
   out_3453992788886440929[188] = 0;
   out_3453992788886440929[189] = 0;
   out_3453992788886440929[190] = 1;
   out_3453992788886440929[191] = 0;
   out_3453992788886440929[192] = 0;
   out_3453992788886440929[193] = 0;
   out_3453992788886440929[194] = 0;
   out_3453992788886440929[195] = 0;
   out_3453992788886440929[196] = 0;
   out_3453992788886440929[197] = 0;
   out_3453992788886440929[198] = 0;
   out_3453992788886440929[199] = 0;
   out_3453992788886440929[200] = 0;
   out_3453992788886440929[201] = 0;
   out_3453992788886440929[202] = 0;
   out_3453992788886440929[203] = 0;
   out_3453992788886440929[204] = 0;
   out_3453992788886440929[205] = 0;
   out_3453992788886440929[206] = 0;
   out_3453992788886440929[207] = 0;
   out_3453992788886440929[208] = 0;
   out_3453992788886440929[209] = 1;
   out_3453992788886440929[210] = 0;
   out_3453992788886440929[211] = 0;
   out_3453992788886440929[212] = 0;
   out_3453992788886440929[213] = 0;
   out_3453992788886440929[214] = 0;
   out_3453992788886440929[215] = 0;
   out_3453992788886440929[216] = 0;
   out_3453992788886440929[217] = 0;
   out_3453992788886440929[218] = 0;
   out_3453992788886440929[219] = 0;
   out_3453992788886440929[220] = 0;
   out_3453992788886440929[221] = 0;
   out_3453992788886440929[222] = 0;
   out_3453992788886440929[223] = 0;
   out_3453992788886440929[224] = 0;
   out_3453992788886440929[225] = 0;
   out_3453992788886440929[226] = 0;
   out_3453992788886440929[227] = 0;
   out_3453992788886440929[228] = 1;
   out_3453992788886440929[229] = 0;
   out_3453992788886440929[230] = 0;
   out_3453992788886440929[231] = 0;
   out_3453992788886440929[232] = 0;
   out_3453992788886440929[233] = 0;
   out_3453992788886440929[234] = 0;
   out_3453992788886440929[235] = 0;
   out_3453992788886440929[236] = 0;
   out_3453992788886440929[237] = 0;
   out_3453992788886440929[238] = 0;
   out_3453992788886440929[239] = 0;
   out_3453992788886440929[240] = 0;
   out_3453992788886440929[241] = 0;
   out_3453992788886440929[242] = 0;
   out_3453992788886440929[243] = 0;
   out_3453992788886440929[244] = 0;
   out_3453992788886440929[245] = 0;
   out_3453992788886440929[246] = 0;
   out_3453992788886440929[247] = 1;
   out_3453992788886440929[248] = 0;
   out_3453992788886440929[249] = 0;
   out_3453992788886440929[250] = 0;
   out_3453992788886440929[251] = 0;
   out_3453992788886440929[252] = 0;
   out_3453992788886440929[253] = 0;
   out_3453992788886440929[254] = 0;
   out_3453992788886440929[255] = 0;
   out_3453992788886440929[256] = 0;
   out_3453992788886440929[257] = 0;
   out_3453992788886440929[258] = 0;
   out_3453992788886440929[259] = 0;
   out_3453992788886440929[260] = 0;
   out_3453992788886440929[261] = 0;
   out_3453992788886440929[262] = 0;
   out_3453992788886440929[263] = 0;
   out_3453992788886440929[264] = 0;
   out_3453992788886440929[265] = 0;
   out_3453992788886440929[266] = 1;
   out_3453992788886440929[267] = 0;
   out_3453992788886440929[268] = 0;
   out_3453992788886440929[269] = 0;
   out_3453992788886440929[270] = 0;
   out_3453992788886440929[271] = 0;
   out_3453992788886440929[272] = 0;
   out_3453992788886440929[273] = 0;
   out_3453992788886440929[274] = 0;
   out_3453992788886440929[275] = 0;
   out_3453992788886440929[276] = 0;
   out_3453992788886440929[277] = 0;
   out_3453992788886440929[278] = 0;
   out_3453992788886440929[279] = 0;
   out_3453992788886440929[280] = 0;
   out_3453992788886440929[281] = 0;
   out_3453992788886440929[282] = 0;
   out_3453992788886440929[283] = 0;
   out_3453992788886440929[284] = 0;
   out_3453992788886440929[285] = 1;
   out_3453992788886440929[286] = 0;
   out_3453992788886440929[287] = 0;
   out_3453992788886440929[288] = 0;
   out_3453992788886440929[289] = 0;
   out_3453992788886440929[290] = 0;
   out_3453992788886440929[291] = 0;
   out_3453992788886440929[292] = 0;
   out_3453992788886440929[293] = 0;
   out_3453992788886440929[294] = 0;
   out_3453992788886440929[295] = 0;
   out_3453992788886440929[296] = 0;
   out_3453992788886440929[297] = 0;
   out_3453992788886440929[298] = 0;
   out_3453992788886440929[299] = 0;
   out_3453992788886440929[300] = 0;
   out_3453992788886440929[301] = 0;
   out_3453992788886440929[302] = 0;
   out_3453992788886440929[303] = 0;
   out_3453992788886440929[304] = 1;
   out_3453992788886440929[305] = 0;
   out_3453992788886440929[306] = 0;
   out_3453992788886440929[307] = 0;
   out_3453992788886440929[308] = 0;
   out_3453992788886440929[309] = 0;
   out_3453992788886440929[310] = 0;
   out_3453992788886440929[311] = 0;
   out_3453992788886440929[312] = 0;
   out_3453992788886440929[313] = 0;
   out_3453992788886440929[314] = 0;
   out_3453992788886440929[315] = 0;
   out_3453992788886440929[316] = 0;
   out_3453992788886440929[317] = 0;
   out_3453992788886440929[318] = 0;
   out_3453992788886440929[319] = 0;
   out_3453992788886440929[320] = 0;
   out_3453992788886440929[321] = 0;
   out_3453992788886440929[322] = 0;
   out_3453992788886440929[323] = 1;
}
void h_4(double *state, double *unused, double *out_2219177127358835334) {
   out_2219177127358835334[0] = state[6] + state[9];
   out_2219177127358835334[1] = state[7] + state[10];
   out_2219177127358835334[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_3491675161553178295) {
   out_3491675161553178295[0] = 0;
   out_3491675161553178295[1] = 0;
   out_3491675161553178295[2] = 0;
   out_3491675161553178295[3] = 0;
   out_3491675161553178295[4] = 0;
   out_3491675161553178295[5] = 0;
   out_3491675161553178295[6] = 1;
   out_3491675161553178295[7] = 0;
   out_3491675161553178295[8] = 0;
   out_3491675161553178295[9] = 1;
   out_3491675161553178295[10] = 0;
   out_3491675161553178295[11] = 0;
   out_3491675161553178295[12] = 0;
   out_3491675161553178295[13] = 0;
   out_3491675161553178295[14] = 0;
   out_3491675161553178295[15] = 0;
   out_3491675161553178295[16] = 0;
   out_3491675161553178295[17] = 0;
   out_3491675161553178295[18] = 0;
   out_3491675161553178295[19] = 0;
   out_3491675161553178295[20] = 0;
   out_3491675161553178295[21] = 0;
   out_3491675161553178295[22] = 0;
   out_3491675161553178295[23] = 0;
   out_3491675161553178295[24] = 0;
   out_3491675161553178295[25] = 1;
   out_3491675161553178295[26] = 0;
   out_3491675161553178295[27] = 0;
   out_3491675161553178295[28] = 1;
   out_3491675161553178295[29] = 0;
   out_3491675161553178295[30] = 0;
   out_3491675161553178295[31] = 0;
   out_3491675161553178295[32] = 0;
   out_3491675161553178295[33] = 0;
   out_3491675161553178295[34] = 0;
   out_3491675161553178295[35] = 0;
   out_3491675161553178295[36] = 0;
   out_3491675161553178295[37] = 0;
   out_3491675161553178295[38] = 0;
   out_3491675161553178295[39] = 0;
   out_3491675161553178295[40] = 0;
   out_3491675161553178295[41] = 0;
   out_3491675161553178295[42] = 0;
   out_3491675161553178295[43] = 0;
   out_3491675161553178295[44] = 1;
   out_3491675161553178295[45] = 0;
   out_3491675161553178295[46] = 0;
   out_3491675161553178295[47] = 1;
   out_3491675161553178295[48] = 0;
   out_3491675161553178295[49] = 0;
   out_3491675161553178295[50] = 0;
   out_3491675161553178295[51] = 0;
   out_3491675161553178295[52] = 0;
   out_3491675161553178295[53] = 0;
}
void h_10(double *state, double *unused, double *out_587419100042313946) {
   out_587419100042313946[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_587419100042313946[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_587419100042313946[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_7812932492250781234) {
   out_7812932492250781234[0] = 0;
   out_7812932492250781234[1] = 9.8100000000000005*cos(state[1]);
   out_7812932492250781234[2] = 0;
   out_7812932492250781234[3] = 0;
   out_7812932492250781234[4] = -state[8];
   out_7812932492250781234[5] = state[7];
   out_7812932492250781234[6] = 0;
   out_7812932492250781234[7] = state[5];
   out_7812932492250781234[8] = -state[4];
   out_7812932492250781234[9] = 0;
   out_7812932492250781234[10] = 0;
   out_7812932492250781234[11] = 0;
   out_7812932492250781234[12] = 1;
   out_7812932492250781234[13] = 0;
   out_7812932492250781234[14] = 0;
   out_7812932492250781234[15] = 1;
   out_7812932492250781234[16] = 0;
   out_7812932492250781234[17] = 0;
   out_7812932492250781234[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_7812932492250781234[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_7812932492250781234[20] = 0;
   out_7812932492250781234[21] = state[8];
   out_7812932492250781234[22] = 0;
   out_7812932492250781234[23] = -state[6];
   out_7812932492250781234[24] = -state[5];
   out_7812932492250781234[25] = 0;
   out_7812932492250781234[26] = state[3];
   out_7812932492250781234[27] = 0;
   out_7812932492250781234[28] = 0;
   out_7812932492250781234[29] = 0;
   out_7812932492250781234[30] = 0;
   out_7812932492250781234[31] = 1;
   out_7812932492250781234[32] = 0;
   out_7812932492250781234[33] = 0;
   out_7812932492250781234[34] = 1;
   out_7812932492250781234[35] = 0;
   out_7812932492250781234[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_7812932492250781234[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_7812932492250781234[38] = 0;
   out_7812932492250781234[39] = -state[7];
   out_7812932492250781234[40] = state[6];
   out_7812932492250781234[41] = 0;
   out_7812932492250781234[42] = state[4];
   out_7812932492250781234[43] = -state[3];
   out_7812932492250781234[44] = 0;
   out_7812932492250781234[45] = 0;
   out_7812932492250781234[46] = 0;
   out_7812932492250781234[47] = 0;
   out_7812932492250781234[48] = 0;
   out_7812932492250781234[49] = 0;
   out_7812932492250781234[50] = 1;
   out_7812932492250781234[51] = 0;
   out_7812932492250781234[52] = 0;
   out_7812932492250781234[53] = 1;
}
void h_13(double *state, double *unused, double *out_7036493165250912321) {
   out_7036493165250912321[0] = state[3];
   out_7036493165250912321[1] = state[4];
   out_7036493165250912321[2] = state[5];
}
void H_13(double *state, double *unused, double *out_4118956046763522634) {
   out_4118956046763522634[0] = 0;
   out_4118956046763522634[1] = 0;
   out_4118956046763522634[2] = 0;
   out_4118956046763522634[3] = 1;
   out_4118956046763522634[4] = 0;
   out_4118956046763522634[5] = 0;
   out_4118956046763522634[6] = 0;
   out_4118956046763522634[7] = 0;
   out_4118956046763522634[8] = 0;
   out_4118956046763522634[9] = 0;
   out_4118956046763522634[10] = 0;
   out_4118956046763522634[11] = 0;
   out_4118956046763522634[12] = 0;
   out_4118956046763522634[13] = 0;
   out_4118956046763522634[14] = 0;
   out_4118956046763522634[15] = 0;
   out_4118956046763522634[16] = 0;
   out_4118956046763522634[17] = 0;
   out_4118956046763522634[18] = 0;
   out_4118956046763522634[19] = 0;
   out_4118956046763522634[20] = 0;
   out_4118956046763522634[21] = 0;
   out_4118956046763522634[22] = 1;
   out_4118956046763522634[23] = 0;
   out_4118956046763522634[24] = 0;
   out_4118956046763522634[25] = 0;
   out_4118956046763522634[26] = 0;
   out_4118956046763522634[27] = 0;
   out_4118956046763522634[28] = 0;
   out_4118956046763522634[29] = 0;
   out_4118956046763522634[30] = 0;
   out_4118956046763522634[31] = 0;
   out_4118956046763522634[32] = 0;
   out_4118956046763522634[33] = 0;
   out_4118956046763522634[34] = 0;
   out_4118956046763522634[35] = 0;
   out_4118956046763522634[36] = 0;
   out_4118956046763522634[37] = 0;
   out_4118956046763522634[38] = 0;
   out_4118956046763522634[39] = 0;
   out_4118956046763522634[40] = 0;
   out_4118956046763522634[41] = 1;
   out_4118956046763522634[42] = 0;
   out_4118956046763522634[43] = 0;
   out_4118956046763522634[44] = 0;
   out_4118956046763522634[45] = 0;
   out_4118956046763522634[46] = 0;
   out_4118956046763522634[47] = 0;
   out_4118956046763522634[48] = 0;
   out_4118956046763522634[49] = 0;
   out_4118956046763522634[50] = 0;
   out_4118956046763522634[51] = 0;
   out_4118956046763522634[52] = 0;
   out_4118956046763522634[53] = 0;
}
void h_14(double *state, double *unused, double *out_5223014531241664562) {
   out_5223014531241664562[0] = state[6];
   out_5223014531241664562[1] = state[7];
   out_5223014531241664562[2] = state[8];
}
void H_14(double *state, double *unused, double *out_6574463593848550591) {
   out_6574463593848550591[0] = 0;
   out_6574463593848550591[1] = 0;
   out_6574463593848550591[2] = 0;
   out_6574463593848550591[3] = 0;
   out_6574463593848550591[4] = 0;
   out_6574463593848550591[5] = 0;
   out_6574463593848550591[6] = 1;
   out_6574463593848550591[7] = 0;
   out_6574463593848550591[8] = 0;
   out_6574463593848550591[9] = 0;
   out_6574463593848550591[10] = 0;
   out_6574463593848550591[11] = 0;
   out_6574463593848550591[12] = 0;
   out_6574463593848550591[13] = 0;
   out_6574463593848550591[14] = 0;
   out_6574463593848550591[15] = 0;
   out_6574463593848550591[16] = 0;
   out_6574463593848550591[17] = 0;
   out_6574463593848550591[18] = 0;
   out_6574463593848550591[19] = 0;
   out_6574463593848550591[20] = 0;
   out_6574463593848550591[21] = 0;
   out_6574463593848550591[22] = 0;
   out_6574463593848550591[23] = 0;
   out_6574463593848550591[24] = 0;
   out_6574463593848550591[25] = 1;
   out_6574463593848550591[26] = 0;
   out_6574463593848550591[27] = 0;
   out_6574463593848550591[28] = 0;
   out_6574463593848550591[29] = 0;
   out_6574463593848550591[30] = 0;
   out_6574463593848550591[31] = 0;
   out_6574463593848550591[32] = 0;
   out_6574463593848550591[33] = 0;
   out_6574463593848550591[34] = 0;
   out_6574463593848550591[35] = 0;
   out_6574463593848550591[36] = 0;
   out_6574463593848550591[37] = 0;
   out_6574463593848550591[38] = 0;
   out_6574463593848550591[39] = 0;
   out_6574463593848550591[40] = 0;
   out_6574463593848550591[41] = 0;
   out_6574463593848550591[42] = 0;
   out_6574463593848550591[43] = 0;
   out_6574463593848550591[44] = 1;
   out_6574463593848550591[45] = 0;
   out_6574463593848550591[46] = 0;
   out_6574463593848550591[47] = 0;
   out_6574463593848550591[48] = 0;
   out_6574463593848550591[49] = 0;
   out_6574463593848550591[50] = 0;
   out_6574463593848550591[51] = 0;
   out_6574463593848550591[52] = 0;
   out_6574463593848550591[53] = 0;
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

void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_4, H_4, NULL, in_z, in_R, in_ea, MAHA_THRESH_4);
}
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_10, H_10, NULL, in_z, in_R, in_ea, MAHA_THRESH_10);
}
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_13, H_13, NULL, in_z, in_R, in_ea, MAHA_THRESH_13);
}
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_14, H_14, NULL, in_z, in_R, in_ea, MAHA_THRESH_14);
}
void pose_err_fun(double *nom_x, double *delta_x, double *out_2671738792046849383) {
  err_fun(nom_x, delta_x, out_2671738792046849383);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_424188773766453759) {
  inv_err_fun(nom_x, true_x, out_424188773766453759);
}
void pose_H_mod_fun(double *state, double *out_7263482371397085867) {
  H_mod_fun(state, out_7263482371397085867);
}
void pose_f_fun(double *state, double dt, double *out_5712205142337176613) {
  f_fun(state,  dt, out_5712205142337176613);
}
void pose_F_fun(double *state, double dt, double *out_3453992788886440929) {
  F_fun(state,  dt, out_3453992788886440929);
}
void pose_h_4(double *state, double *unused, double *out_2219177127358835334) {
  h_4(state, unused, out_2219177127358835334);
}
void pose_H_4(double *state, double *unused, double *out_3491675161553178295) {
  H_4(state, unused, out_3491675161553178295);
}
void pose_h_10(double *state, double *unused, double *out_587419100042313946) {
  h_10(state, unused, out_587419100042313946);
}
void pose_H_10(double *state, double *unused, double *out_7812932492250781234) {
  H_10(state, unused, out_7812932492250781234);
}
void pose_h_13(double *state, double *unused, double *out_7036493165250912321) {
  h_13(state, unused, out_7036493165250912321);
}
void pose_H_13(double *state, double *unused, double *out_4118956046763522634) {
  H_13(state, unused, out_4118956046763522634);
}
void pose_h_14(double *state, double *unused, double *out_5223014531241664562) {
  h_14(state, unused, out_5223014531241664562);
}
void pose_H_14(double *state, double *unused, double *out_6574463593848550591) {
  H_14(state, unused, out_6574463593848550591);
}
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
}

const EKF pose = {
  .name = "pose",
  .kinds = { 4, 10, 13, 14 },
  .feature_kinds = {  },
  .f_fun = pose_f_fun,
  .F_fun = pose_F_fun,
  .err_fun = pose_err_fun,
  .inv_err_fun = pose_inv_err_fun,
  .H_mod_fun = pose_H_mod_fun,
  .predict = pose_predict,
  .hs = {
    { 4, pose_h_4 },
    { 10, pose_h_10 },
    { 13, pose_h_13 },
    { 14, pose_h_14 },
  },
  .Hs = {
    { 4, pose_H_4 },
    { 10, pose_H_10 },
    { 13, pose_H_13 },
    { 14, pose_H_14 },
  },
  .updates = {
    { 4, pose_update_4 },
    { 10, pose_update_10 },
    { 13, pose_update_13 },
    { 14, pose_update_14 },
  },
  .Hes = {
  },
  .sets = {
  },
  .extra_routines = {
  },
};

ekf_lib_init(pose)
