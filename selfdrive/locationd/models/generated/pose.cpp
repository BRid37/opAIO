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
void err_fun(double *nom_x, double *delta_x, double *out_4442264216625752623) {
   out_4442264216625752623[0] = delta_x[0] + nom_x[0];
   out_4442264216625752623[1] = delta_x[1] + nom_x[1];
   out_4442264216625752623[2] = delta_x[2] + nom_x[2];
   out_4442264216625752623[3] = delta_x[3] + nom_x[3];
   out_4442264216625752623[4] = delta_x[4] + nom_x[4];
   out_4442264216625752623[5] = delta_x[5] + nom_x[5];
   out_4442264216625752623[6] = delta_x[6] + nom_x[6];
   out_4442264216625752623[7] = delta_x[7] + nom_x[7];
   out_4442264216625752623[8] = delta_x[8] + nom_x[8];
   out_4442264216625752623[9] = delta_x[9] + nom_x[9];
   out_4442264216625752623[10] = delta_x[10] + nom_x[10];
   out_4442264216625752623[11] = delta_x[11] + nom_x[11];
   out_4442264216625752623[12] = delta_x[12] + nom_x[12];
   out_4442264216625752623[13] = delta_x[13] + nom_x[13];
   out_4442264216625752623[14] = delta_x[14] + nom_x[14];
   out_4442264216625752623[15] = delta_x[15] + nom_x[15];
   out_4442264216625752623[16] = delta_x[16] + nom_x[16];
   out_4442264216625752623[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_8068876060036098661) {
   out_8068876060036098661[0] = -nom_x[0] + true_x[0];
   out_8068876060036098661[1] = -nom_x[1] + true_x[1];
   out_8068876060036098661[2] = -nom_x[2] + true_x[2];
   out_8068876060036098661[3] = -nom_x[3] + true_x[3];
   out_8068876060036098661[4] = -nom_x[4] + true_x[4];
   out_8068876060036098661[5] = -nom_x[5] + true_x[5];
   out_8068876060036098661[6] = -nom_x[6] + true_x[6];
   out_8068876060036098661[7] = -nom_x[7] + true_x[7];
   out_8068876060036098661[8] = -nom_x[8] + true_x[8];
   out_8068876060036098661[9] = -nom_x[9] + true_x[9];
   out_8068876060036098661[10] = -nom_x[10] + true_x[10];
   out_8068876060036098661[11] = -nom_x[11] + true_x[11];
   out_8068876060036098661[12] = -nom_x[12] + true_x[12];
   out_8068876060036098661[13] = -nom_x[13] + true_x[13];
   out_8068876060036098661[14] = -nom_x[14] + true_x[14];
   out_8068876060036098661[15] = -nom_x[15] + true_x[15];
   out_8068876060036098661[16] = -nom_x[16] + true_x[16];
   out_8068876060036098661[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_3914528363574678845) {
   out_3914528363574678845[0] = 1.0;
   out_3914528363574678845[1] = 0.0;
   out_3914528363574678845[2] = 0.0;
   out_3914528363574678845[3] = 0.0;
   out_3914528363574678845[4] = 0.0;
   out_3914528363574678845[5] = 0.0;
   out_3914528363574678845[6] = 0.0;
   out_3914528363574678845[7] = 0.0;
   out_3914528363574678845[8] = 0.0;
   out_3914528363574678845[9] = 0.0;
   out_3914528363574678845[10] = 0.0;
   out_3914528363574678845[11] = 0.0;
   out_3914528363574678845[12] = 0.0;
   out_3914528363574678845[13] = 0.0;
   out_3914528363574678845[14] = 0.0;
   out_3914528363574678845[15] = 0.0;
   out_3914528363574678845[16] = 0.0;
   out_3914528363574678845[17] = 0.0;
   out_3914528363574678845[18] = 0.0;
   out_3914528363574678845[19] = 1.0;
   out_3914528363574678845[20] = 0.0;
   out_3914528363574678845[21] = 0.0;
   out_3914528363574678845[22] = 0.0;
   out_3914528363574678845[23] = 0.0;
   out_3914528363574678845[24] = 0.0;
   out_3914528363574678845[25] = 0.0;
   out_3914528363574678845[26] = 0.0;
   out_3914528363574678845[27] = 0.0;
   out_3914528363574678845[28] = 0.0;
   out_3914528363574678845[29] = 0.0;
   out_3914528363574678845[30] = 0.0;
   out_3914528363574678845[31] = 0.0;
   out_3914528363574678845[32] = 0.0;
   out_3914528363574678845[33] = 0.0;
   out_3914528363574678845[34] = 0.0;
   out_3914528363574678845[35] = 0.0;
   out_3914528363574678845[36] = 0.0;
   out_3914528363574678845[37] = 0.0;
   out_3914528363574678845[38] = 1.0;
   out_3914528363574678845[39] = 0.0;
   out_3914528363574678845[40] = 0.0;
   out_3914528363574678845[41] = 0.0;
   out_3914528363574678845[42] = 0.0;
   out_3914528363574678845[43] = 0.0;
   out_3914528363574678845[44] = 0.0;
   out_3914528363574678845[45] = 0.0;
   out_3914528363574678845[46] = 0.0;
   out_3914528363574678845[47] = 0.0;
   out_3914528363574678845[48] = 0.0;
   out_3914528363574678845[49] = 0.0;
   out_3914528363574678845[50] = 0.0;
   out_3914528363574678845[51] = 0.0;
   out_3914528363574678845[52] = 0.0;
   out_3914528363574678845[53] = 0.0;
   out_3914528363574678845[54] = 0.0;
   out_3914528363574678845[55] = 0.0;
   out_3914528363574678845[56] = 0.0;
   out_3914528363574678845[57] = 1.0;
   out_3914528363574678845[58] = 0.0;
   out_3914528363574678845[59] = 0.0;
   out_3914528363574678845[60] = 0.0;
   out_3914528363574678845[61] = 0.0;
   out_3914528363574678845[62] = 0.0;
   out_3914528363574678845[63] = 0.0;
   out_3914528363574678845[64] = 0.0;
   out_3914528363574678845[65] = 0.0;
   out_3914528363574678845[66] = 0.0;
   out_3914528363574678845[67] = 0.0;
   out_3914528363574678845[68] = 0.0;
   out_3914528363574678845[69] = 0.0;
   out_3914528363574678845[70] = 0.0;
   out_3914528363574678845[71] = 0.0;
   out_3914528363574678845[72] = 0.0;
   out_3914528363574678845[73] = 0.0;
   out_3914528363574678845[74] = 0.0;
   out_3914528363574678845[75] = 0.0;
   out_3914528363574678845[76] = 1.0;
   out_3914528363574678845[77] = 0.0;
   out_3914528363574678845[78] = 0.0;
   out_3914528363574678845[79] = 0.0;
   out_3914528363574678845[80] = 0.0;
   out_3914528363574678845[81] = 0.0;
   out_3914528363574678845[82] = 0.0;
   out_3914528363574678845[83] = 0.0;
   out_3914528363574678845[84] = 0.0;
   out_3914528363574678845[85] = 0.0;
   out_3914528363574678845[86] = 0.0;
   out_3914528363574678845[87] = 0.0;
   out_3914528363574678845[88] = 0.0;
   out_3914528363574678845[89] = 0.0;
   out_3914528363574678845[90] = 0.0;
   out_3914528363574678845[91] = 0.0;
   out_3914528363574678845[92] = 0.0;
   out_3914528363574678845[93] = 0.0;
   out_3914528363574678845[94] = 0.0;
   out_3914528363574678845[95] = 1.0;
   out_3914528363574678845[96] = 0.0;
   out_3914528363574678845[97] = 0.0;
   out_3914528363574678845[98] = 0.0;
   out_3914528363574678845[99] = 0.0;
   out_3914528363574678845[100] = 0.0;
   out_3914528363574678845[101] = 0.0;
   out_3914528363574678845[102] = 0.0;
   out_3914528363574678845[103] = 0.0;
   out_3914528363574678845[104] = 0.0;
   out_3914528363574678845[105] = 0.0;
   out_3914528363574678845[106] = 0.0;
   out_3914528363574678845[107] = 0.0;
   out_3914528363574678845[108] = 0.0;
   out_3914528363574678845[109] = 0.0;
   out_3914528363574678845[110] = 0.0;
   out_3914528363574678845[111] = 0.0;
   out_3914528363574678845[112] = 0.0;
   out_3914528363574678845[113] = 0.0;
   out_3914528363574678845[114] = 1.0;
   out_3914528363574678845[115] = 0.0;
   out_3914528363574678845[116] = 0.0;
   out_3914528363574678845[117] = 0.0;
   out_3914528363574678845[118] = 0.0;
   out_3914528363574678845[119] = 0.0;
   out_3914528363574678845[120] = 0.0;
   out_3914528363574678845[121] = 0.0;
   out_3914528363574678845[122] = 0.0;
   out_3914528363574678845[123] = 0.0;
   out_3914528363574678845[124] = 0.0;
   out_3914528363574678845[125] = 0.0;
   out_3914528363574678845[126] = 0.0;
   out_3914528363574678845[127] = 0.0;
   out_3914528363574678845[128] = 0.0;
   out_3914528363574678845[129] = 0.0;
   out_3914528363574678845[130] = 0.0;
   out_3914528363574678845[131] = 0.0;
   out_3914528363574678845[132] = 0.0;
   out_3914528363574678845[133] = 1.0;
   out_3914528363574678845[134] = 0.0;
   out_3914528363574678845[135] = 0.0;
   out_3914528363574678845[136] = 0.0;
   out_3914528363574678845[137] = 0.0;
   out_3914528363574678845[138] = 0.0;
   out_3914528363574678845[139] = 0.0;
   out_3914528363574678845[140] = 0.0;
   out_3914528363574678845[141] = 0.0;
   out_3914528363574678845[142] = 0.0;
   out_3914528363574678845[143] = 0.0;
   out_3914528363574678845[144] = 0.0;
   out_3914528363574678845[145] = 0.0;
   out_3914528363574678845[146] = 0.0;
   out_3914528363574678845[147] = 0.0;
   out_3914528363574678845[148] = 0.0;
   out_3914528363574678845[149] = 0.0;
   out_3914528363574678845[150] = 0.0;
   out_3914528363574678845[151] = 0.0;
   out_3914528363574678845[152] = 1.0;
   out_3914528363574678845[153] = 0.0;
   out_3914528363574678845[154] = 0.0;
   out_3914528363574678845[155] = 0.0;
   out_3914528363574678845[156] = 0.0;
   out_3914528363574678845[157] = 0.0;
   out_3914528363574678845[158] = 0.0;
   out_3914528363574678845[159] = 0.0;
   out_3914528363574678845[160] = 0.0;
   out_3914528363574678845[161] = 0.0;
   out_3914528363574678845[162] = 0.0;
   out_3914528363574678845[163] = 0.0;
   out_3914528363574678845[164] = 0.0;
   out_3914528363574678845[165] = 0.0;
   out_3914528363574678845[166] = 0.0;
   out_3914528363574678845[167] = 0.0;
   out_3914528363574678845[168] = 0.0;
   out_3914528363574678845[169] = 0.0;
   out_3914528363574678845[170] = 0.0;
   out_3914528363574678845[171] = 1.0;
   out_3914528363574678845[172] = 0.0;
   out_3914528363574678845[173] = 0.0;
   out_3914528363574678845[174] = 0.0;
   out_3914528363574678845[175] = 0.0;
   out_3914528363574678845[176] = 0.0;
   out_3914528363574678845[177] = 0.0;
   out_3914528363574678845[178] = 0.0;
   out_3914528363574678845[179] = 0.0;
   out_3914528363574678845[180] = 0.0;
   out_3914528363574678845[181] = 0.0;
   out_3914528363574678845[182] = 0.0;
   out_3914528363574678845[183] = 0.0;
   out_3914528363574678845[184] = 0.0;
   out_3914528363574678845[185] = 0.0;
   out_3914528363574678845[186] = 0.0;
   out_3914528363574678845[187] = 0.0;
   out_3914528363574678845[188] = 0.0;
   out_3914528363574678845[189] = 0.0;
   out_3914528363574678845[190] = 1.0;
   out_3914528363574678845[191] = 0.0;
   out_3914528363574678845[192] = 0.0;
   out_3914528363574678845[193] = 0.0;
   out_3914528363574678845[194] = 0.0;
   out_3914528363574678845[195] = 0.0;
   out_3914528363574678845[196] = 0.0;
   out_3914528363574678845[197] = 0.0;
   out_3914528363574678845[198] = 0.0;
   out_3914528363574678845[199] = 0.0;
   out_3914528363574678845[200] = 0.0;
   out_3914528363574678845[201] = 0.0;
   out_3914528363574678845[202] = 0.0;
   out_3914528363574678845[203] = 0.0;
   out_3914528363574678845[204] = 0.0;
   out_3914528363574678845[205] = 0.0;
   out_3914528363574678845[206] = 0.0;
   out_3914528363574678845[207] = 0.0;
   out_3914528363574678845[208] = 0.0;
   out_3914528363574678845[209] = 1.0;
   out_3914528363574678845[210] = 0.0;
   out_3914528363574678845[211] = 0.0;
   out_3914528363574678845[212] = 0.0;
   out_3914528363574678845[213] = 0.0;
   out_3914528363574678845[214] = 0.0;
   out_3914528363574678845[215] = 0.0;
   out_3914528363574678845[216] = 0.0;
   out_3914528363574678845[217] = 0.0;
   out_3914528363574678845[218] = 0.0;
   out_3914528363574678845[219] = 0.0;
   out_3914528363574678845[220] = 0.0;
   out_3914528363574678845[221] = 0.0;
   out_3914528363574678845[222] = 0.0;
   out_3914528363574678845[223] = 0.0;
   out_3914528363574678845[224] = 0.0;
   out_3914528363574678845[225] = 0.0;
   out_3914528363574678845[226] = 0.0;
   out_3914528363574678845[227] = 0.0;
   out_3914528363574678845[228] = 1.0;
   out_3914528363574678845[229] = 0.0;
   out_3914528363574678845[230] = 0.0;
   out_3914528363574678845[231] = 0.0;
   out_3914528363574678845[232] = 0.0;
   out_3914528363574678845[233] = 0.0;
   out_3914528363574678845[234] = 0.0;
   out_3914528363574678845[235] = 0.0;
   out_3914528363574678845[236] = 0.0;
   out_3914528363574678845[237] = 0.0;
   out_3914528363574678845[238] = 0.0;
   out_3914528363574678845[239] = 0.0;
   out_3914528363574678845[240] = 0.0;
   out_3914528363574678845[241] = 0.0;
   out_3914528363574678845[242] = 0.0;
   out_3914528363574678845[243] = 0.0;
   out_3914528363574678845[244] = 0.0;
   out_3914528363574678845[245] = 0.0;
   out_3914528363574678845[246] = 0.0;
   out_3914528363574678845[247] = 1.0;
   out_3914528363574678845[248] = 0.0;
   out_3914528363574678845[249] = 0.0;
   out_3914528363574678845[250] = 0.0;
   out_3914528363574678845[251] = 0.0;
   out_3914528363574678845[252] = 0.0;
   out_3914528363574678845[253] = 0.0;
   out_3914528363574678845[254] = 0.0;
   out_3914528363574678845[255] = 0.0;
   out_3914528363574678845[256] = 0.0;
   out_3914528363574678845[257] = 0.0;
   out_3914528363574678845[258] = 0.0;
   out_3914528363574678845[259] = 0.0;
   out_3914528363574678845[260] = 0.0;
   out_3914528363574678845[261] = 0.0;
   out_3914528363574678845[262] = 0.0;
   out_3914528363574678845[263] = 0.0;
   out_3914528363574678845[264] = 0.0;
   out_3914528363574678845[265] = 0.0;
   out_3914528363574678845[266] = 1.0;
   out_3914528363574678845[267] = 0.0;
   out_3914528363574678845[268] = 0.0;
   out_3914528363574678845[269] = 0.0;
   out_3914528363574678845[270] = 0.0;
   out_3914528363574678845[271] = 0.0;
   out_3914528363574678845[272] = 0.0;
   out_3914528363574678845[273] = 0.0;
   out_3914528363574678845[274] = 0.0;
   out_3914528363574678845[275] = 0.0;
   out_3914528363574678845[276] = 0.0;
   out_3914528363574678845[277] = 0.0;
   out_3914528363574678845[278] = 0.0;
   out_3914528363574678845[279] = 0.0;
   out_3914528363574678845[280] = 0.0;
   out_3914528363574678845[281] = 0.0;
   out_3914528363574678845[282] = 0.0;
   out_3914528363574678845[283] = 0.0;
   out_3914528363574678845[284] = 0.0;
   out_3914528363574678845[285] = 1.0;
   out_3914528363574678845[286] = 0.0;
   out_3914528363574678845[287] = 0.0;
   out_3914528363574678845[288] = 0.0;
   out_3914528363574678845[289] = 0.0;
   out_3914528363574678845[290] = 0.0;
   out_3914528363574678845[291] = 0.0;
   out_3914528363574678845[292] = 0.0;
   out_3914528363574678845[293] = 0.0;
   out_3914528363574678845[294] = 0.0;
   out_3914528363574678845[295] = 0.0;
   out_3914528363574678845[296] = 0.0;
   out_3914528363574678845[297] = 0.0;
   out_3914528363574678845[298] = 0.0;
   out_3914528363574678845[299] = 0.0;
   out_3914528363574678845[300] = 0.0;
   out_3914528363574678845[301] = 0.0;
   out_3914528363574678845[302] = 0.0;
   out_3914528363574678845[303] = 0.0;
   out_3914528363574678845[304] = 1.0;
   out_3914528363574678845[305] = 0.0;
   out_3914528363574678845[306] = 0.0;
   out_3914528363574678845[307] = 0.0;
   out_3914528363574678845[308] = 0.0;
   out_3914528363574678845[309] = 0.0;
   out_3914528363574678845[310] = 0.0;
   out_3914528363574678845[311] = 0.0;
   out_3914528363574678845[312] = 0.0;
   out_3914528363574678845[313] = 0.0;
   out_3914528363574678845[314] = 0.0;
   out_3914528363574678845[315] = 0.0;
   out_3914528363574678845[316] = 0.0;
   out_3914528363574678845[317] = 0.0;
   out_3914528363574678845[318] = 0.0;
   out_3914528363574678845[319] = 0.0;
   out_3914528363574678845[320] = 0.0;
   out_3914528363574678845[321] = 0.0;
   out_3914528363574678845[322] = 0.0;
   out_3914528363574678845[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_5861088598759542506) {
   out_5861088598759542506[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_5861088598759542506[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_5861088598759542506[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_5861088598759542506[3] = dt*state[12] + state[3];
   out_5861088598759542506[4] = dt*state[13] + state[4];
   out_5861088598759542506[5] = dt*state[14] + state[5];
   out_5861088598759542506[6] = state[6];
   out_5861088598759542506[7] = state[7];
   out_5861088598759542506[8] = state[8];
   out_5861088598759542506[9] = state[9];
   out_5861088598759542506[10] = state[10];
   out_5861088598759542506[11] = state[11];
   out_5861088598759542506[12] = state[12];
   out_5861088598759542506[13] = state[13];
   out_5861088598759542506[14] = state[14];
   out_5861088598759542506[15] = state[15];
   out_5861088598759542506[16] = state[16];
   out_5861088598759542506[17] = state[17];
}
void F_fun(double *state, double dt, double *out_6415614808115414031) {
   out_6415614808115414031[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6415614808115414031[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6415614808115414031[2] = 0;
   out_6415614808115414031[3] = 0;
   out_6415614808115414031[4] = 0;
   out_6415614808115414031[5] = 0;
   out_6415614808115414031[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6415614808115414031[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6415614808115414031[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6415614808115414031[9] = 0;
   out_6415614808115414031[10] = 0;
   out_6415614808115414031[11] = 0;
   out_6415614808115414031[12] = 0;
   out_6415614808115414031[13] = 0;
   out_6415614808115414031[14] = 0;
   out_6415614808115414031[15] = 0;
   out_6415614808115414031[16] = 0;
   out_6415614808115414031[17] = 0;
   out_6415614808115414031[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6415614808115414031[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6415614808115414031[20] = 0;
   out_6415614808115414031[21] = 0;
   out_6415614808115414031[22] = 0;
   out_6415614808115414031[23] = 0;
   out_6415614808115414031[24] = 0;
   out_6415614808115414031[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6415614808115414031[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6415614808115414031[27] = 0;
   out_6415614808115414031[28] = 0;
   out_6415614808115414031[29] = 0;
   out_6415614808115414031[30] = 0;
   out_6415614808115414031[31] = 0;
   out_6415614808115414031[32] = 0;
   out_6415614808115414031[33] = 0;
   out_6415614808115414031[34] = 0;
   out_6415614808115414031[35] = 0;
   out_6415614808115414031[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6415614808115414031[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6415614808115414031[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6415614808115414031[39] = 0;
   out_6415614808115414031[40] = 0;
   out_6415614808115414031[41] = 0;
   out_6415614808115414031[42] = 0;
   out_6415614808115414031[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6415614808115414031[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6415614808115414031[45] = 0;
   out_6415614808115414031[46] = 0;
   out_6415614808115414031[47] = 0;
   out_6415614808115414031[48] = 0;
   out_6415614808115414031[49] = 0;
   out_6415614808115414031[50] = 0;
   out_6415614808115414031[51] = 0;
   out_6415614808115414031[52] = 0;
   out_6415614808115414031[53] = 0;
   out_6415614808115414031[54] = 0;
   out_6415614808115414031[55] = 0;
   out_6415614808115414031[56] = 0;
   out_6415614808115414031[57] = 1;
   out_6415614808115414031[58] = 0;
   out_6415614808115414031[59] = 0;
   out_6415614808115414031[60] = 0;
   out_6415614808115414031[61] = 0;
   out_6415614808115414031[62] = 0;
   out_6415614808115414031[63] = 0;
   out_6415614808115414031[64] = 0;
   out_6415614808115414031[65] = 0;
   out_6415614808115414031[66] = dt;
   out_6415614808115414031[67] = 0;
   out_6415614808115414031[68] = 0;
   out_6415614808115414031[69] = 0;
   out_6415614808115414031[70] = 0;
   out_6415614808115414031[71] = 0;
   out_6415614808115414031[72] = 0;
   out_6415614808115414031[73] = 0;
   out_6415614808115414031[74] = 0;
   out_6415614808115414031[75] = 0;
   out_6415614808115414031[76] = 1;
   out_6415614808115414031[77] = 0;
   out_6415614808115414031[78] = 0;
   out_6415614808115414031[79] = 0;
   out_6415614808115414031[80] = 0;
   out_6415614808115414031[81] = 0;
   out_6415614808115414031[82] = 0;
   out_6415614808115414031[83] = 0;
   out_6415614808115414031[84] = 0;
   out_6415614808115414031[85] = dt;
   out_6415614808115414031[86] = 0;
   out_6415614808115414031[87] = 0;
   out_6415614808115414031[88] = 0;
   out_6415614808115414031[89] = 0;
   out_6415614808115414031[90] = 0;
   out_6415614808115414031[91] = 0;
   out_6415614808115414031[92] = 0;
   out_6415614808115414031[93] = 0;
   out_6415614808115414031[94] = 0;
   out_6415614808115414031[95] = 1;
   out_6415614808115414031[96] = 0;
   out_6415614808115414031[97] = 0;
   out_6415614808115414031[98] = 0;
   out_6415614808115414031[99] = 0;
   out_6415614808115414031[100] = 0;
   out_6415614808115414031[101] = 0;
   out_6415614808115414031[102] = 0;
   out_6415614808115414031[103] = 0;
   out_6415614808115414031[104] = dt;
   out_6415614808115414031[105] = 0;
   out_6415614808115414031[106] = 0;
   out_6415614808115414031[107] = 0;
   out_6415614808115414031[108] = 0;
   out_6415614808115414031[109] = 0;
   out_6415614808115414031[110] = 0;
   out_6415614808115414031[111] = 0;
   out_6415614808115414031[112] = 0;
   out_6415614808115414031[113] = 0;
   out_6415614808115414031[114] = 1;
   out_6415614808115414031[115] = 0;
   out_6415614808115414031[116] = 0;
   out_6415614808115414031[117] = 0;
   out_6415614808115414031[118] = 0;
   out_6415614808115414031[119] = 0;
   out_6415614808115414031[120] = 0;
   out_6415614808115414031[121] = 0;
   out_6415614808115414031[122] = 0;
   out_6415614808115414031[123] = 0;
   out_6415614808115414031[124] = 0;
   out_6415614808115414031[125] = 0;
   out_6415614808115414031[126] = 0;
   out_6415614808115414031[127] = 0;
   out_6415614808115414031[128] = 0;
   out_6415614808115414031[129] = 0;
   out_6415614808115414031[130] = 0;
   out_6415614808115414031[131] = 0;
   out_6415614808115414031[132] = 0;
   out_6415614808115414031[133] = 1;
   out_6415614808115414031[134] = 0;
   out_6415614808115414031[135] = 0;
   out_6415614808115414031[136] = 0;
   out_6415614808115414031[137] = 0;
   out_6415614808115414031[138] = 0;
   out_6415614808115414031[139] = 0;
   out_6415614808115414031[140] = 0;
   out_6415614808115414031[141] = 0;
   out_6415614808115414031[142] = 0;
   out_6415614808115414031[143] = 0;
   out_6415614808115414031[144] = 0;
   out_6415614808115414031[145] = 0;
   out_6415614808115414031[146] = 0;
   out_6415614808115414031[147] = 0;
   out_6415614808115414031[148] = 0;
   out_6415614808115414031[149] = 0;
   out_6415614808115414031[150] = 0;
   out_6415614808115414031[151] = 0;
   out_6415614808115414031[152] = 1;
   out_6415614808115414031[153] = 0;
   out_6415614808115414031[154] = 0;
   out_6415614808115414031[155] = 0;
   out_6415614808115414031[156] = 0;
   out_6415614808115414031[157] = 0;
   out_6415614808115414031[158] = 0;
   out_6415614808115414031[159] = 0;
   out_6415614808115414031[160] = 0;
   out_6415614808115414031[161] = 0;
   out_6415614808115414031[162] = 0;
   out_6415614808115414031[163] = 0;
   out_6415614808115414031[164] = 0;
   out_6415614808115414031[165] = 0;
   out_6415614808115414031[166] = 0;
   out_6415614808115414031[167] = 0;
   out_6415614808115414031[168] = 0;
   out_6415614808115414031[169] = 0;
   out_6415614808115414031[170] = 0;
   out_6415614808115414031[171] = 1;
   out_6415614808115414031[172] = 0;
   out_6415614808115414031[173] = 0;
   out_6415614808115414031[174] = 0;
   out_6415614808115414031[175] = 0;
   out_6415614808115414031[176] = 0;
   out_6415614808115414031[177] = 0;
   out_6415614808115414031[178] = 0;
   out_6415614808115414031[179] = 0;
   out_6415614808115414031[180] = 0;
   out_6415614808115414031[181] = 0;
   out_6415614808115414031[182] = 0;
   out_6415614808115414031[183] = 0;
   out_6415614808115414031[184] = 0;
   out_6415614808115414031[185] = 0;
   out_6415614808115414031[186] = 0;
   out_6415614808115414031[187] = 0;
   out_6415614808115414031[188] = 0;
   out_6415614808115414031[189] = 0;
   out_6415614808115414031[190] = 1;
   out_6415614808115414031[191] = 0;
   out_6415614808115414031[192] = 0;
   out_6415614808115414031[193] = 0;
   out_6415614808115414031[194] = 0;
   out_6415614808115414031[195] = 0;
   out_6415614808115414031[196] = 0;
   out_6415614808115414031[197] = 0;
   out_6415614808115414031[198] = 0;
   out_6415614808115414031[199] = 0;
   out_6415614808115414031[200] = 0;
   out_6415614808115414031[201] = 0;
   out_6415614808115414031[202] = 0;
   out_6415614808115414031[203] = 0;
   out_6415614808115414031[204] = 0;
   out_6415614808115414031[205] = 0;
   out_6415614808115414031[206] = 0;
   out_6415614808115414031[207] = 0;
   out_6415614808115414031[208] = 0;
   out_6415614808115414031[209] = 1;
   out_6415614808115414031[210] = 0;
   out_6415614808115414031[211] = 0;
   out_6415614808115414031[212] = 0;
   out_6415614808115414031[213] = 0;
   out_6415614808115414031[214] = 0;
   out_6415614808115414031[215] = 0;
   out_6415614808115414031[216] = 0;
   out_6415614808115414031[217] = 0;
   out_6415614808115414031[218] = 0;
   out_6415614808115414031[219] = 0;
   out_6415614808115414031[220] = 0;
   out_6415614808115414031[221] = 0;
   out_6415614808115414031[222] = 0;
   out_6415614808115414031[223] = 0;
   out_6415614808115414031[224] = 0;
   out_6415614808115414031[225] = 0;
   out_6415614808115414031[226] = 0;
   out_6415614808115414031[227] = 0;
   out_6415614808115414031[228] = 1;
   out_6415614808115414031[229] = 0;
   out_6415614808115414031[230] = 0;
   out_6415614808115414031[231] = 0;
   out_6415614808115414031[232] = 0;
   out_6415614808115414031[233] = 0;
   out_6415614808115414031[234] = 0;
   out_6415614808115414031[235] = 0;
   out_6415614808115414031[236] = 0;
   out_6415614808115414031[237] = 0;
   out_6415614808115414031[238] = 0;
   out_6415614808115414031[239] = 0;
   out_6415614808115414031[240] = 0;
   out_6415614808115414031[241] = 0;
   out_6415614808115414031[242] = 0;
   out_6415614808115414031[243] = 0;
   out_6415614808115414031[244] = 0;
   out_6415614808115414031[245] = 0;
   out_6415614808115414031[246] = 0;
   out_6415614808115414031[247] = 1;
   out_6415614808115414031[248] = 0;
   out_6415614808115414031[249] = 0;
   out_6415614808115414031[250] = 0;
   out_6415614808115414031[251] = 0;
   out_6415614808115414031[252] = 0;
   out_6415614808115414031[253] = 0;
   out_6415614808115414031[254] = 0;
   out_6415614808115414031[255] = 0;
   out_6415614808115414031[256] = 0;
   out_6415614808115414031[257] = 0;
   out_6415614808115414031[258] = 0;
   out_6415614808115414031[259] = 0;
   out_6415614808115414031[260] = 0;
   out_6415614808115414031[261] = 0;
   out_6415614808115414031[262] = 0;
   out_6415614808115414031[263] = 0;
   out_6415614808115414031[264] = 0;
   out_6415614808115414031[265] = 0;
   out_6415614808115414031[266] = 1;
   out_6415614808115414031[267] = 0;
   out_6415614808115414031[268] = 0;
   out_6415614808115414031[269] = 0;
   out_6415614808115414031[270] = 0;
   out_6415614808115414031[271] = 0;
   out_6415614808115414031[272] = 0;
   out_6415614808115414031[273] = 0;
   out_6415614808115414031[274] = 0;
   out_6415614808115414031[275] = 0;
   out_6415614808115414031[276] = 0;
   out_6415614808115414031[277] = 0;
   out_6415614808115414031[278] = 0;
   out_6415614808115414031[279] = 0;
   out_6415614808115414031[280] = 0;
   out_6415614808115414031[281] = 0;
   out_6415614808115414031[282] = 0;
   out_6415614808115414031[283] = 0;
   out_6415614808115414031[284] = 0;
   out_6415614808115414031[285] = 1;
   out_6415614808115414031[286] = 0;
   out_6415614808115414031[287] = 0;
   out_6415614808115414031[288] = 0;
   out_6415614808115414031[289] = 0;
   out_6415614808115414031[290] = 0;
   out_6415614808115414031[291] = 0;
   out_6415614808115414031[292] = 0;
   out_6415614808115414031[293] = 0;
   out_6415614808115414031[294] = 0;
   out_6415614808115414031[295] = 0;
   out_6415614808115414031[296] = 0;
   out_6415614808115414031[297] = 0;
   out_6415614808115414031[298] = 0;
   out_6415614808115414031[299] = 0;
   out_6415614808115414031[300] = 0;
   out_6415614808115414031[301] = 0;
   out_6415614808115414031[302] = 0;
   out_6415614808115414031[303] = 0;
   out_6415614808115414031[304] = 1;
   out_6415614808115414031[305] = 0;
   out_6415614808115414031[306] = 0;
   out_6415614808115414031[307] = 0;
   out_6415614808115414031[308] = 0;
   out_6415614808115414031[309] = 0;
   out_6415614808115414031[310] = 0;
   out_6415614808115414031[311] = 0;
   out_6415614808115414031[312] = 0;
   out_6415614808115414031[313] = 0;
   out_6415614808115414031[314] = 0;
   out_6415614808115414031[315] = 0;
   out_6415614808115414031[316] = 0;
   out_6415614808115414031[317] = 0;
   out_6415614808115414031[318] = 0;
   out_6415614808115414031[319] = 0;
   out_6415614808115414031[320] = 0;
   out_6415614808115414031[321] = 0;
   out_6415614808115414031[322] = 0;
   out_6415614808115414031[323] = 1;
}
void h_4(double *state, double *unused, double *out_1046875653712579764) {
   out_1046875653712579764[0] = state[6] + state[9];
   out_1046875653712579764[1] = state[7] + state[10];
   out_1046875653712579764[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_7188750442365628098) {
   out_7188750442365628098[0] = 0;
   out_7188750442365628098[1] = 0;
   out_7188750442365628098[2] = 0;
   out_7188750442365628098[3] = 0;
   out_7188750442365628098[4] = 0;
   out_7188750442365628098[5] = 0;
   out_7188750442365628098[6] = 1;
   out_7188750442365628098[7] = 0;
   out_7188750442365628098[8] = 0;
   out_7188750442365628098[9] = 1;
   out_7188750442365628098[10] = 0;
   out_7188750442365628098[11] = 0;
   out_7188750442365628098[12] = 0;
   out_7188750442365628098[13] = 0;
   out_7188750442365628098[14] = 0;
   out_7188750442365628098[15] = 0;
   out_7188750442365628098[16] = 0;
   out_7188750442365628098[17] = 0;
   out_7188750442365628098[18] = 0;
   out_7188750442365628098[19] = 0;
   out_7188750442365628098[20] = 0;
   out_7188750442365628098[21] = 0;
   out_7188750442365628098[22] = 0;
   out_7188750442365628098[23] = 0;
   out_7188750442365628098[24] = 0;
   out_7188750442365628098[25] = 1;
   out_7188750442365628098[26] = 0;
   out_7188750442365628098[27] = 0;
   out_7188750442365628098[28] = 1;
   out_7188750442365628098[29] = 0;
   out_7188750442365628098[30] = 0;
   out_7188750442365628098[31] = 0;
   out_7188750442365628098[32] = 0;
   out_7188750442365628098[33] = 0;
   out_7188750442365628098[34] = 0;
   out_7188750442365628098[35] = 0;
   out_7188750442365628098[36] = 0;
   out_7188750442365628098[37] = 0;
   out_7188750442365628098[38] = 0;
   out_7188750442365628098[39] = 0;
   out_7188750442365628098[40] = 0;
   out_7188750442365628098[41] = 0;
   out_7188750442365628098[42] = 0;
   out_7188750442365628098[43] = 0;
   out_7188750442365628098[44] = 1;
   out_7188750442365628098[45] = 0;
   out_7188750442365628098[46] = 0;
   out_7188750442365628098[47] = 1;
   out_7188750442365628098[48] = 0;
   out_7188750442365628098[49] = 0;
   out_7188750442365628098[50] = 0;
   out_7188750442365628098[51] = 0;
   out_7188750442365628098[52] = 0;
   out_7188750442365628098[53] = 0;
}
void h_10(double *state, double *unused, double *out_6939817699329021946) {
   out_6939817699329021946[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_6939817699329021946[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_6939817699329021946[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_8722847441151408688) {
   out_8722847441151408688[0] = 0;
   out_8722847441151408688[1] = 9.8100000000000005*cos(state[1]);
   out_8722847441151408688[2] = 0;
   out_8722847441151408688[3] = 0;
   out_8722847441151408688[4] = -state[8];
   out_8722847441151408688[5] = state[7];
   out_8722847441151408688[6] = 0;
   out_8722847441151408688[7] = state[5];
   out_8722847441151408688[8] = -state[4];
   out_8722847441151408688[9] = 0;
   out_8722847441151408688[10] = 0;
   out_8722847441151408688[11] = 0;
   out_8722847441151408688[12] = 1;
   out_8722847441151408688[13] = 0;
   out_8722847441151408688[14] = 0;
   out_8722847441151408688[15] = 1;
   out_8722847441151408688[16] = 0;
   out_8722847441151408688[17] = 0;
   out_8722847441151408688[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_8722847441151408688[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_8722847441151408688[20] = 0;
   out_8722847441151408688[21] = state[8];
   out_8722847441151408688[22] = 0;
   out_8722847441151408688[23] = -state[6];
   out_8722847441151408688[24] = -state[5];
   out_8722847441151408688[25] = 0;
   out_8722847441151408688[26] = state[3];
   out_8722847441151408688[27] = 0;
   out_8722847441151408688[28] = 0;
   out_8722847441151408688[29] = 0;
   out_8722847441151408688[30] = 0;
   out_8722847441151408688[31] = 1;
   out_8722847441151408688[32] = 0;
   out_8722847441151408688[33] = 0;
   out_8722847441151408688[34] = 1;
   out_8722847441151408688[35] = 0;
   out_8722847441151408688[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_8722847441151408688[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_8722847441151408688[38] = 0;
   out_8722847441151408688[39] = -state[7];
   out_8722847441151408688[40] = state[6];
   out_8722847441151408688[41] = 0;
   out_8722847441151408688[42] = state[4];
   out_8722847441151408688[43] = -state[3];
   out_8722847441151408688[44] = 0;
   out_8722847441151408688[45] = 0;
   out_8722847441151408688[46] = 0;
   out_8722847441151408688[47] = 0;
   out_8722847441151408688[48] = 0;
   out_8722847441151408688[49] = 0;
   out_8722847441151408688[50] = 1;
   out_8722847441151408688[51] = 0;
   out_8722847441151408688[52] = 0;
   out_8722847441151408688[53] = 1;
}
void h_13(double *state, double *unused, double *out_6853026663320228979) {
   out_6853026663320228979[0] = state[3];
   out_6853026663320228979[1] = state[4];
   out_6853026663320228979[2] = state[5];
}
void H_13(double *state, double *unused, double *out_3976476617033295297) {
   out_3976476617033295297[0] = 0;
   out_3976476617033295297[1] = 0;
   out_3976476617033295297[2] = 0;
   out_3976476617033295297[3] = 1;
   out_3976476617033295297[4] = 0;
   out_3976476617033295297[5] = 0;
   out_3976476617033295297[6] = 0;
   out_3976476617033295297[7] = 0;
   out_3976476617033295297[8] = 0;
   out_3976476617033295297[9] = 0;
   out_3976476617033295297[10] = 0;
   out_3976476617033295297[11] = 0;
   out_3976476617033295297[12] = 0;
   out_3976476617033295297[13] = 0;
   out_3976476617033295297[14] = 0;
   out_3976476617033295297[15] = 0;
   out_3976476617033295297[16] = 0;
   out_3976476617033295297[17] = 0;
   out_3976476617033295297[18] = 0;
   out_3976476617033295297[19] = 0;
   out_3976476617033295297[20] = 0;
   out_3976476617033295297[21] = 0;
   out_3976476617033295297[22] = 1;
   out_3976476617033295297[23] = 0;
   out_3976476617033295297[24] = 0;
   out_3976476617033295297[25] = 0;
   out_3976476617033295297[26] = 0;
   out_3976476617033295297[27] = 0;
   out_3976476617033295297[28] = 0;
   out_3976476617033295297[29] = 0;
   out_3976476617033295297[30] = 0;
   out_3976476617033295297[31] = 0;
   out_3976476617033295297[32] = 0;
   out_3976476617033295297[33] = 0;
   out_3976476617033295297[34] = 0;
   out_3976476617033295297[35] = 0;
   out_3976476617033295297[36] = 0;
   out_3976476617033295297[37] = 0;
   out_3976476617033295297[38] = 0;
   out_3976476617033295297[39] = 0;
   out_3976476617033295297[40] = 0;
   out_3976476617033295297[41] = 1;
   out_3976476617033295297[42] = 0;
   out_3976476617033295297[43] = 0;
   out_3976476617033295297[44] = 0;
   out_3976476617033295297[45] = 0;
   out_3976476617033295297[46] = 0;
   out_3976476617033295297[47] = 0;
   out_3976476617033295297[48] = 0;
   out_3976476617033295297[49] = 0;
   out_3976476617033295297[50] = 0;
   out_3976476617033295297[51] = 0;
   out_3976476617033295297[52] = 0;
   out_3976476617033295297[53] = 0;
}
void h_14(double *state, double *unused, double *out_1334170023894757499) {
   out_1334170023894757499[0] = state[6];
   out_1334170023894757499[1] = state[7];
   out_1334170023894757499[2] = state[8];
}
void H_14(double *state, double *unused, double *out_3225509586026143569) {
   out_3225509586026143569[0] = 0;
   out_3225509586026143569[1] = 0;
   out_3225509586026143569[2] = 0;
   out_3225509586026143569[3] = 0;
   out_3225509586026143569[4] = 0;
   out_3225509586026143569[5] = 0;
   out_3225509586026143569[6] = 1;
   out_3225509586026143569[7] = 0;
   out_3225509586026143569[8] = 0;
   out_3225509586026143569[9] = 0;
   out_3225509586026143569[10] = 0;
   out_3225509586026143569[11] = 0;
   out_3225509586026143569[12] = 0;
   out_3225509586026143569[13] = 0;
   out_3225509586026143569[14] = 0;
   out_3225509586026143569[15] = 0;
   out_3225509586026143569[16] = 0;
   out_3225509586026143569[17] = 0;
   out_3225509586026143569[18] = 0;
   out_3225509586026143569[19] = 0;
   out_3225509586026143569[20] = 0;
   out_3225509586026143569[21] = 0;
   out_3225509586026143569[22] = 0;
   out_3225509586026143569[23] = 0;
   out_3225509586026143569[24] = 0;
   out_3225509586026143569[25] = 1;
   out_3225509586026143569[26] = 0;
   out_3225509586026143569[27] = 0;
   out_3225509586026143569[28] = 0;
   out_3225509586026143569[29] = 0;
   out_3225509586026143569[30] = 0;
   out_3225509586026143569[31] = 0;
   out_3225509586026143569[32] = 0;
   out_3225509586026143569[33] = 0;
   out_3225509586026143569[34] = 0;
   out_3225509586026143569[35] = 0;
   out_3225509586026143569[36] = 0;
   out_3225509586026143569[37] = 0;
   out_3225509586026143569[38] = 0;
   out_3225509586026143569[39] = 0;
   out_3225509586026143569[40] = 0;
   out_3225509586026143569[41] = 0;
   out_3225509586026143569[42] = 0;
   out_3225509586026143569[43] = 0;
   out_3225509586026143569[44] = 1;
   out_3225509586026143569[45] = 0;
   out_3225509586026143569[46] = 0;
   out_3225509586026143569[47] = 0;
   out_3225509586026143569[48] = 0;
   out_3225509586026143569[49] = 0;
   out_3225509586026143569[50] = 0;
   out_3225509586026143569[51] = 0;
   out_3225509586026143569[52] = 0;
   out_3225509586026143569[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_4442264216625752623) {
  err_fun(nom_x, delta_x, out_4442264216625752623);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_8068876060036098661) {
  inv_err_fun(nom_x, true_x, out_8068876060036098661);
}
void pose_H_mod_fun(double *state, double *out_3914528363574678845) {
  H_mod_fun(state, out_3914528363574678845);
}
void pose_f_fun(double *state, double dt, double *out_5861088598759542506) {
  f_fun(state,  dt, out_5861088598759542506);
}
void pose_F_fun(double *state, double dt, double *out_6415614808115414031) {
  F_fun(state,  dt, out_6415614808115414031);
}
void pose_h_4(double *state, double *unused, double *out_1046875653712579764) {
  h_4(state, unused, out_1046875653712579764);
}
void pose_H_4(double *state, double *unused, double *out_7188750442365628098) {
  H_4(state, unused, out_7188750442365628098);
}
void pose_h_10(double *state, double *unused, double *out_6939817699329021946) {
  h_10(state, unused, out_6939817699329021946);
}
void pose_H_10(double *state, double *unused, double *out_8722847441151408688) {
  H_10(state, unused, out_8722847441151408688);
}
void pose_h_13(double *state, double *unused, double *out_6853026663320228979) {
  h_13(state, unused, out_6853026663320228979);
}
void pose_H_13(double *state, double *unused, double *out_3976476617033295297) {
  H_13(state, unused, out_3976476617033295297);
}
void pose_h_14(double *state, double *unused, double *out_1334170023894757499) {
  h_14(state, unused, out_1334170023894757499);
}
void pose_H_14(double *state, double *unused, double *out_3225509586026143569) {
  H_14(state, unused, out_3225509586026143569);
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
