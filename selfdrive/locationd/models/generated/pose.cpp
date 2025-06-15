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
void err_fun(double *nom_x, double *delta_x, double *out_1454459679057110584) {
   out_1454459679057110584[0] = delta_x[0] + nom_x[0];
   out_1454459679057110584[1] = delta_x[1] + nom_x[1];
   out_1454459679057110584[2] = delta_x[2] + nom_x[2];
   out_1454459679057110584[3] = delta_x[3] + nom_x[3];
   out_1454459679057110584[4] = delta_x[4] + nom_x[4];
   out_1454459679057110584[5] = delta_x[5] + nom_x[5];
   out_1454459679057110584[6] = delta_x[6] + nom_x[6];
   out_1454459679057110584[7] = delta_x[7] + nom_x[7];
   out_1454459679057110584[8] = delta_x[8] + nom_x[8];
   out_1454459679057110584[9] = delta_x[9] + nom_x[9];
   out_1454459679057110584[10] = delta_x[10] + nom_x[10];
   out_1454459679057110584[11] = delta_x[11] + nom_x[11];
   out_1454459679057110584[12] = delta_x[12] + nom_x[12];
   out_1454459679057110584[13] = delta_x[13] + nom_x[13];
   out_1454459679057110584[14] = delta_x[14] + nom_x[14];
   out_1454459679057110584[15] = delta_x[15] + nom_x[15];
   out_1454459679057110584[16] = delta_x[16] + nom_x[16];
   out_1454459679057110584[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_8466886164721569510) {
   out_8466886164721569510[0] = -nom_x[0] + true_x[0];
   out_8466886164721569510[1] = -nom_x[1] + true_x[1];
   out_8466886164721569510[2] = -nom_x[2] + true_x[2];
   out_8466886164721569510[3] = -nom_x[3] + true_x[3];
   out_8466886164721569510[4] = -nom_x[4] + true_x[4];
   out_8466886164721569510[5] = -nom_x[5] + true_x[5];
   out_8466886164721569510[6] = -nom_x[6] + true_x[6];
   out_8466886164721569510[7] = -nom_x[7] + true_x[7];
   out_8466886164721569510[8] = -nom_x[8] + true_x[8];
   out_8466886164721569510[9] = -nom_x[9] + true_x[9];
   out_8466886164721569510[10] = -nom_x[10] + true_x[10];
   out_8466886164721569510[11] = -nom_x[11] + true_x[11];
   out_8466886164721569510[12] = -nom_x[12] + true_x[12];
   out_8466886164721569510[13] = -nom_x[13] + true_x[13];
   out_8466886164721569510[14] = -nom_x[14] + true_x[14];
   out_8466886164721569510[15] = -nom_x[15] + true_x[15];
   out_8466886164721569510[16] = -nom_x[16] + true_x[16];
   out_8466886164721569510[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_6891492054151298461) {
   out_6891492054151298461[0] = 1.0;
   out_6891492054151298461[1] = 0.0;
   out_6891492054151298461[2] = 0.0;
   out_6891492054151298461[3] = 0.0;
   out_6891492054151298461[4] = 0.0;
   out_6891492054151298461[5] = 0.0;
   out_6891492054151298461[6] = 0.0;
   out_6891492054151298461[7] = 0.0;
   out_6891492054151298461[8] = 0.0;
   out_6891492054151298461[9] = 0.0;
   out_6891492054151298461[10] = 0.0;
   out_6891492054151298461[11] = 0.0;
   out_6891492054151298461[12] = 0.0;
   out_6891492054151298461[13] = 0.0;
   out_6891492054151298461[14] = 0.0;
   out_6891492054151298461[15] = 0.0;
   out_6891492054151298461[16] = 0.0;
   out_6891492054151298461[17] = 0.0;
   out_6891492054151298461[18] = 0.0;
   out_6891492054151298461[19] = 1.0;
   out_6891492054151298461[20] = 0.0;
   out_6891492054151298461[21] = 0.0;
   out_6891492054151298461[22] = 0.0;
   out_6891492054151298461[23] = 0.0;
   out_6891492054151298461[24] = 0.0;
   out_6891492054151298461[25] = 0.0;
   out_6891492054151298461[26] = 0.0;
   out_6891492054151298461[27] = 0.0;
   out_6891492054151298461[28] = 0.0;
   out_6891492054151298461[29] = 0.0;
   out_6891492054151298461[30] = 0.0;
   out_6891492054151298461[31] = 0.0;
   out_6891492054151298461[32] = 0.0;
   out_6891492054151298461[33] = 0.0;
   out_6891492054151298461[34] = 0.0;
   out_6891492054151298461[35] = 0.0;
   out_6891492054151298461[36] = 0.0;
   out_6891492054151298461[37] = 0.0;
   out_6891492054151298461[38] = 1.0;
   out_6891492054151298461[39] = 0.0;
   out_6891492054151298461[40] = 0.0;
   out_6891492054151298461[41] = 0.0;
   out_6891492054151298461[42] = 0.0;
   out_6891492054151298461[43] = 0.0;
   out_6891492054151298461[44] = 0.0;
   out_6891492054151298461[45] = 0.0;
   out_6891492054151298461[46] = 0.0;
   out_6891492054151298461[47] = 0.0;
   out_6891492054151298461[48] = 0.0;
   out_6891492054151298461[49] = 0.0;
   out_6891492054151298461[50] = 0.0;
   out_6891492054151298461[51] = 0.0;
   out_6891492054151298461[52] = 0.0;
   out_6891492054151298461[53] = 0.0;
   out_6891492054151298461[54] = 0.0;
   out_6891492054151298461[55] = 0.0;
   out_6891492054151298461[56] = 0.0;
   out_6891492054151298461[57] = 1.0;
   out_6891492054151298461[58] = 0.0;
   out_6891492054151298461[59] = 0.0;
   out_6891492054151298461[60] = 0.0;
   out_6891492054151298461[61] = 0.0;
   out_6891492054151298461[62] = 0.0;
   out_6891492054151298461[63] = 0.0;
   out_6891492054151298461[64] = 0.0;
   out_6891492054151298461[65] = 0.0;
   out_6891492054151298461[66] = 0.0;
   out_6891492054151298461[67] = 0.0;
   out_6891492054151298461[68] = 0.0;
   out_6891492054151298461[69] = 0.0;
   out_6891492054151298461[70] = 0.0;
   out_6891492054151298461[71] = 0.0;
   out_6891492054151298461[72] = 0.0;
   out_6891492054151298461[73] = 0.0;
   out_6891492054151298461[74] = 0.0;
   out_6891492054151298461[75] = 0.0;
   out_6891492054151298461[76] = 1.0;
   out_6891492054151298461[77] = 0.0;
   out_6891492054151298461[78] = 0.0;
   out_6891492054151298461[79] = 0.0;
   out_6891492054151298461[80] = 0.0;
   out_6891492054151298461[81] = 0.0;
   out_6891492054151298461[82] = 0.0;
   out_6891492054151298461[83] = 0.0;
   out_6891492054151298461[84] = 0.0;
   out_6891492054151298461[85] = 0.0;
   out_6891492054151298461[86] = 0.0;
   out_6891492054151298461[87] = 0.0;
   out_6891492054151298461[88] = 0.0;
   out_6891492054151298461[89] = 0.0;
   out_6891492054151298461[90] = 0.0;
   out_6891492054151298461[91] = 0.0;
   out_6891492054151298461[92] = 0.0;
   out_6891492054151298461[93] = 0.0;
   out_6891492054151298461[94] = 0.0;
   out_6891492054151298461[95] = 1.0;
   out_6891492054151298461[96] = 0.0;
   out_6891492054151298461[97] = 0.0;
   out_6891492054151298461[98] = 0.0;
   out_6891492054151298461[99] = 0.0;
   out_6891492054151298461[100] = 0.0;
   out_6891492054151298461[101] = 0.0;
   out_6891492054151298461[102] = 0.0;
   out_6891492054151298461[103] = 0.0;
   out_6891492054151298461[104] = 0.0;
   out_6891492054151298461[105] = 0.0;
   out_6891492054151298461[106] = 0.0;
   out_6891492054151298461[107] = 0.0;
   out_6891492054151298461[108] = 0.0;
   out_6891492054151298461[109] = 0.0;
   out_6891492054151298461[110] = 0.0;
   out_6891492054151298461[111] = 0.0;
   out_6891492054151298461[112] = 0.0;
   out_6891492054151298461[113] = 0.0;
   out_6891492054151298461[114] = 1.0;
   out_6891492054151298461[115] = 0.0;
   out_6891492054151298461[116] = 0.0;
   out_6891492054151298461[117] = 0.0;
   out_6891492054151298461[118] = 0.0;
   out_6891492054151298461[119] = 0.0;
   out_6891492054151298461[120] = 0.0;
   out_6891492054151298461[121] = 0.0;
   out_6891492054151298461[122] = 0.0;
   out_6891492054151298461[123] = 0.0;
   out_6891492054151298461[124] = 0.0;
   out_6891492054151298461[125] = 0.0;
   out_6891492054151298461[126] = 0.0;
   out_6891492054151298461[127] = 0.0;
   out_6891492054151298461[128] = 0.0;
   out_6891492054151298461[129] = 0.0;
   out_6891492054151298461[130] = 0.0;
   out_6891492054151298461[131] = 0.0;
   out_6891492054151298461[132] = 0.0;
   out_6891492054151298461[133] = 1.0;
   out_6891492054151298461[134] = 0.0;
   out_6891492054151298461[135] = 0.0;
   out_6891492054151298461[136] = 0.0;
   out_6891492054151298461[137] = 0.0;
   out_6891492054151298461[138] = 0.0;
   out_6891492054151298461[139] = 0.0;
   out_6891492054151298461[140] = 0.0;
   out_6891492054151298461[141] = 0.0;
   out_6891492054151298461[142] = 0.0;
   out_6891492054151298461[143] = 0.0;
   out_6891492054151298461[144] = 0.0;
   out_6891492054151298461[145] = 0.0;
   out_6891492054151298461[146] = 0.0;
   out_6891492054151298461[147] = 0.0;
   out_6891492054151298461[148] = 0.0;
   out_6891492054151298461[149] = 0.0;
   out_6891492054151298461[150] = 0.0;
   out_6891492054151298461[151] = 0.0;
   out_6891492054151298461[152] = 1.0;
   out_6891492054151298461[153] = 0.0;
   out_6891492054151298461[154] = 0.0;
   out_6891492054151298461[155] = 0.0;
   out_6891492054151298461[156] = 0.0;
   out_6891492054151298461[157] = 0.0;
   out_6891492054151298461[158] = 0.0;
   out_6891492054151298461[159] = 0.0;
   out_6891492054151298461[160] = 0.0;
   out_6891492054151298461[161] = 0.0;
   out_6891492054151298461[162] = 0.0;
   out_6891492054151298461[163] = 0.0;
   out_6891492054151298461[164] = 0.0;
   out_6891492054151298461[165] = 0.0;
   out_6891492054151298461[166] = 0.0;
   out_6891492054151298461[167] = 0.0;
   out_6891492054151298461[168] = 0.0;
   out_6891492054151298461[169] = 0.0;
   out_6891492054151298461[170] = 0.0;
   out_6891492054151298461[171] = 1.0;
   out_6891492054151298461[172] = 0.0;
   out_6891492054151298461[173] = 0.0;
   out_6891492054151298461[174] = 0.0;
   out_6891492054151298461[175] = 0.0;
   out_6891492054151298461[176] = 0.0;
   out_6891492054151298461[177] = 0.0;
   out_6891492054151298461[178] = 0.0;
   out_6891492054151298461[179] = 0.0;
   out_6891492054151298461[180] = 0.0;
   out_6891492054151298461[181] = 0.0;
   out_6891492054151298461[182] = 0.0;
   out_6891492054151298461[183] = 0.0;
   out_6891492054151298461[184] = 0.0;
   out_6891492054151298461[185] = 0.0;
   out_6891492054151298461[186] = 0.0;
   out_6891492054151298461[187] = 0.0;
   out_6891492054151298461[188] = 0.0;
   out_6891492054151298461[189] = 0.0;
   out_6891492054151298461[190] = 1.0;
   out_6891492054151298461[191] = 0.0;
   out_6891492054151298461[192] = 0.0;
   out_6891492054151298461[193] = 0.0;
   out_6891492054151298461[194] = 0.0;
   out_6891492054151298461[195] = 0.0;
   out_6891492054151298461[196] = 0.0;
   out_6891492054151298461[197] = 0.0;
   out_6891492054151298461[198] = 0.0;
   out_6891492054151298461[199] = 0.0;
   out_6891492054151298461[200] = 0.0;
   out_6891492054151298461[201] = 0.0;
   out_6891492054151298461[202] = 0.0;
   out_6891492054151298461[203] = 0.0;
   out_6891492054151298461[204] = 0.0;
   out_6891492054151298461[205] = 0.0;
   out_6891492054151298461[206] = 0.0;
   out_6891492054151298461[207] = 0.0;
   out_6891492054151298461[208] = 0.0;
   out_6891492054151298461[209] = 1.0;
   out_6891492054151298461[210] = 0.0;
   out_6891492054151298461[211] = 0.0;
   out_6891492054151298461[212] = 0.0;
   out_6891492054151298461[213] = 0.0;
   out_6891492054151298461[214] = 0.0;
   out_6891492054151298461[215] = 0.0;
   out_6891492054151298461[216] = 0.0;
   out_6891492054151298461[217] = 0.0;
   out_6891492054151298461[218] = 0.0;
   out_6891492054151298461[219] = 0.0;
   out_6891492054151298461[220] = 0.0;
   out_6891492054151298461[221] = 0.0;
   out_6891492054151298461[222] = 0.0;
   out_6891492054151298461[223] = 0.0;
   out_6891492054151298461[224] = 0.0;
   out_6891492054151298461[225] = 0.0;
   out_6891492054151298461[226] = 0.0;
   out_6891492054151298461[227] = 0.0;
   out_6891492054151298461[228] = 1.0;
   out_6891492054151298461[229] = 0.0;
   out_6891492054151298461[230] = 0.0;
   out_6891492054151298461[231] = 0.0;
   out_6891492054151298461[232] = 0.0;
   out_6891492054151298461[233] = 0.0;
   out_6891492054151298461[234] = 0.0;
   out_6891492054151298461[235] = 0.0;
   out_6891492054151298461[236] = 0.0;
   out_6891492054151298461[237] = 0.0;
   out_6891492054151298461[238] = 0.0;
   out_6891492054151298461[239] = 0.0;
   out_6891492054151298461[240] = 0.0;
   out_6891492054151298461[241] = 0.0;
   out_6891492054151298461[242] = 0.0;
   out_6891492054151298461[243] = 0.0;
   out_6891492054151298461[244] = 0.0;
   out_6891492054151298461[245] = 0.0;
   out_6891492054151298461[246] = 0.0;
   out_6891492054151298461[247] = 1.0;
   out_6891492054151298461[248] = 0.0;
   out_6891492054151298461[249] = 0.0;
   out_6891492054151298461[250] = 0.0;
   out_6891492054151298461[251] = 0.0;
   out_6891492054151298461[252] = 0.0;
   out_6891492054151298461[253] = 0.0;
   out_6891492054151298461[254] = 0.0;
   out_6891492054151298461[255] = 0.0;
   out_6891492054151298461[256] = 0.0;
   out_6891492054151298461[257] = 0.0;
   out_6891492054151298461[258] = 0.0;
   out_6891492054151298461[259] = 0.0;
   out_6891492054151298461[260] = 0.0;
   out_6891492054151298461[261] = 0.0;
   out_6891492054151298461[262] = 0.0;
   out_6891492054151298461[263] = 0.0;
   out_6891492054151298461[264] = 0.0;
   out_6891492054151298461[265] = 0.0;
   out_6891492054151298461[266] = 1.0;
   out_6891492054151298461[267] = 0.0;
   out_6891492054151298461[268] = 0.0;
   out_6891492054151298461[269] = 0.0;
   out_6891492054151298461[270] = 0.0;
   out_6891492054151298461[271] = 0.0;
   out_6891492054151298461[272] = 0.0;
   out_6891492054151298461[273] = 0.0;
   out_6891492054151298461[274] = 0.0;
   out_6891492054151298461[275] = 0.0;
   out_6891492054151298461[276] = 0.0;
   out_6891492054151298461[277] = 0.0;
   out_6891492054151298461[278] = 0.0;
   out_6891492054151298461[279] = 0.0;
   out_6891492054151298461[280] = 0.0;
   out_6891492054151298461[281] = 0.0;
   out_6891492054151298461[282] = 0.0;
   out_6891492054151298461[283] = 0.0;
   out_6891492054151298461[284] = 0.0;
   out_6891492054151298461[285] = 1.0;
   out_6891492054151298461[286] = 0.0;
   out_6891492054151298461[287] = 0.0;
   out_6891492054151298461[288] = 0.0;
   out_6891492054151298461[289] = 0.0;
   out_6891492054151298461[290] = 0.0;
   out_6891492054151298461[291] = 0.0;
   out_6891492054151298461[292] = 0.0;
   out_6891492054151298461[293] = 0.0;
   out_6891492054151298461[294] = 0.0;
   out_6891492054151298461[295] = 0.0;
   out_6891492054151298461[296] = 0.0;
   out_6891492054151298461[297] = 0.0;
   out_6891492054151298461[298] = 0.0;
   out_6891492054151298461[299] = 0.0;
   out_6891492054151298461[300] = 0.0;
   out_6891492054151298461[301] = 0.0;
   out_6891492054151298461[302] = 0.0;
   out_6891492054151298461[303] = 0.0;
   out_6891492054151298461[304] = 1.0;
   out_6891492054151298461[305] = 0.0;
   out_6891492054151298461[306] = 0.0;
   out_6891492054151298461[307] = 0.0;
   out_6891492054151298461[308] = 0.0;
   out_6891492054151298461[309] = 0.0;
   out_6891492054151298461[310] = 0.0;
   out_6891492054151298461[311] = 0.0;
   out_6891492054151298461[312] = 0.0;
   out_6891492054151298461[313] = 0.0;
   out_6891492054151298461[314] = 0.0;
   out_6891492054151298461[315] = 0.0;
   out_6891492054151298461[316] = 0.0;
   out_6891492054151298461[317] = 0.0;
   out_6891492054151298461[318] = 0.0;
   out_6891492054151298461[319] = 0.0;
   out_6891492054151298461[320] = 0.0;
   out_6891492054151298461[321] = 0.0;
   out_6891492054151298461[322] = 0.0;
   out_6891492054151298461[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_6198631950895505143) {
   out_6198631950895505143[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_6198631950895505143[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_6198631950895505143[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_6198631950895505143[3] = dt*state[12] + state[3];
   out_6198631950895505143[4] = dt*state[13] + state[4];
   out_6198631950895505143[5] = dt*state[14] + state[5];
   out_6198631950895505143[6] = state[6];
   out_6198631950895505143[7] = state[7];
   out_6198631950895505143[8] = state[8];
   out_6198631950895505143[9] = state[9];
   out_6198631950895505143[10] = state[10];
   out_6198631950895505143[11] = state[11];
   out_6198631950895505143[12] = state[12];
   out_6198631950895505143[13] = state[13];
   out_6198631950895505143[14] = state[14];
   out_6198631950895505143[15] = state[15];
   out_6198631950895505143[16] = state[16];
   out_6198631950895505143[17] = state[17];
}
void F_fun(double *state, double dt, double *out_5188989910390169613) {
   out_5188989910390169613[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5188989910390169613[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5188989910390169613[2] = 0;
   out_5188989910390169613[3] = 0;
   out_5188989910390169613[4] = 0;
   out_5188989910390169613[5] = 0;
   out_5188989910390169613[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5188989910390169613[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5188989910390169613[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5188989910390169613[9] = 0;
   out_5188989910390169613[10] = 0;
   out_5188989910390169613[11] = 0;
   out_5188989910390169613[12] = 0;
   out_5188989910390169613[13] = 0;
   out_5188989910390169613[14] = 0;
   out_5188989910390169613[15] = 0;
   out_5188989910390169613[16] = 0;
   out_5188989910390169613[17] = 0;
   out_5188989910390169613[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5188989910390169613[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5188989910390169613[20] = 0;
   out_5188989910390169613[21] = 0;
   out_5188989910390169613[22] = 0;
   out_5188989910390169613[23] = 0;
   out_5188989910390169613[24] = 0;
   out_5188989910390169613[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5188989910390169613[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5188989910390169613[27] = 0;
   out_5188989910390169613[28] = 0;
   out_5188989910390169613[29] = 0;
   out_5188989910390169613[30] = 0;
   out_5188989910390169613[31] = 0;
   out_5188989910390169613[32] = 0;
   out_5188989910390169613[33] = 0;
   out_5188989910390169613[34] = 0;
   out_5188989910390169613[35] = 0;
   out_5188989910390169613[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5188989910390169613[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5188989910390169613[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5188989910390169613[39] = 0;
   out_5188989910390169613[40] = 0;
   out_5188989910390169613[41] = 0;
   out_5188989910390169613[42] = 0;
   out_5188989910390169613[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5188989910390169613[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5188989910390169613[45] = 0;
   out_5188989910390169613[46] = 0;
   out_5188989910390169613[47] = 0;
   out_5188989910390169613[48] = 0;
   out_5188989910390169613[49] = 0;
   out_5188989910390169613[50] = 0;
   out_5188989910390169613[51] = 0;
   out_5188989910390169613[52] = 0;
   out_5188989910390169613[53] = 0;
   out_5188989910390169613[54] = 0;
   out_5188989910390169613[55] = 0;
   out_5188989910390169613[56] = 0;
   out_5188989910390169613[57] = 1;
   out_5188989910390169613[58] = 0;
   out_5188989910390169613[59] = 0;
   out_5188989910390169613[60] = 0;
   out_5188989910390169613[61] = 0;
   out_5188989910390169613[62] = 0;
   out_5188989910390169613[63] = 0;
   out_5188989910390169613[64] = 0;
   out_5188989910390169613[65] = 0;
   out_5188989910390169613[66] = dt;
   out_5188989910390169613[67] = 0;
   out_5188989910390169613[68] = 0;
   out_5188989910390169613[69] = 0;
   out_5188989910390169613[70] = 0;
   out_5188989910390169613[71] = 0;
   out_5188989910390169613[72] = 0;
   out_5188989910390169613[73] = 0;
   out_5188989910390169613[74] = 0;
   out_5188989910390169613[75] = 0;
   out_5188989910390169613[76] = 1;
   out_5188989910390169613[77] = 0;
   out_5188989910390169613[78] = 0;
   out_5188989910390169613[79] = 0;
   out_5188989910390169613[80] = 0;
   out_5188989910390169613[81] = 0;
   out_5188989910390169613[82] = 0;
   out_5188989910390169613[83] = 0;
   out_5188989910390169613[84] = 0;
   out_5188989910390169613[85] = dt;
   out_5188989910390169613[86] = 0;
   out_5188989910390169613[87] = 0;
   out_5188989910390169613[88] = 0;
   out_5188989910390169613[89] = 0;
   out_5188989910390169613[90] = 0;
   out_5188989910390169613[91] = 0;
   out_5188989910390169613[92] = 0;
   out_5188989910390169613[93] = 0;
   out_5188989910390169613[94] = 0;
   out_5188989910390169613[95] = 1;
   out_5188989910390169613[96] = 0;
   out_5188989910390169613[97] = 0;
   out_5188989910390169613[98] = 0;
   out_5188989910390169613[99] = 0;
   out_5188989910390169613[100] = 0;
   out_5188989910390169613[101] = 0;
   out_5188989910390169613[102] = 0;
   out_5188989910390169613[103] = 0;
   out_5188989910390169613[104] = dt;
   out_5188989910390169613[105] = 0;
   out_5188989910390169613[106] = 0;
   out_5188989910390169613[107] = 0;
   out_5188989910390169613[108] = 0;
   out_5188989910390169613[109] = 0;
   out_5188989910390169613[110] = 0;
   out_5188989910390169613[111] = 0;
   out_5188989910390169613[112] = 0;
   out_5188989910390169613[113] = 0;
   out_5188989910390169613[114] = 1;
   out_5188989910390169613[115] = 0;
   out_5188989910390169613[116] = 0;
   out_5188989910390169613[117] = 0;
   out_5188989910390169613[118] = 0;
   out_5188989910390169613[119] = 0;
   out_5188989910390169613[120] = 0;
   out_5188989910390169613[121] = 0;
   out_5188989910390169613[122] = 0;
   out_5188989910390169613[123] = 0;
   out_5188989910390169613[124] = 0;
   out_5188989910390169613[125] = 0;
   out_5188989910390169613[126] = 0;
   out_5188989910390169613[127] = 0;
   out_5188989910390169613[128] = 0;
   out_5188989910390169613[129] = 0;
   out_5188989910390169613[130] = 0;
   out_5188989910390169613[131] = 0;
   out_5188989910390169613[132] = 0;
   out_5188989910390169613[133] = 1;
   out_5188989910390169613[134] = 0;
   out_5188989910390169613[135] = 0;
   out_5188989910390169613[136] = 0;
   out_5188989910390169613[137] = 0;
   out_5188989910390169613[138] = 0;
   out_5188989910390169613[139] = 0;
   out_5188989910390169613[140] = 0;
   out_5188989910390169613[141] = 0;
   out_5188989910390169613[142] = 0;
   out_5188989910390169613[143] = 0;
   out_5188989910390169613[144] = 0;
   out_5188989910390169613[145] = 0;
   out_5188989910390169613[146] = 0;
   out_5188989910390169613[147] = 0;
   out_5188989910390169613[148] = 0;
   out_5188989910390169613[149] = 0;
   out_5188989910390169613[150] = 0;
   out_5188989910390169613[151] = 0;
   out_5188989910390169613[152] = 1;
   out_5188989910390169613[153] = 0;
   out_5188989910390169613[154] = 0;
   out_5188989910390169613[155] = 0;
   out_5188989910390169613[156] = 0;
   out_5188989910390169613[157] = 0;
   out_5188989910390169613[158] = 0;
   out_5188989910390169613[159] = 0;
   out_5188989910390169613[160] = 0;
   out_5188989910390169613[161] = 0;
   out_5188989910390169613[162] = 0;
   out_5188989910390169613[163] = 0;
   out_5188989910390169613[164] = 0;
   out_5188989910390169613[165] = 0;
   out_5188989910390169613[166] = 0;
   out_5188989910390169613[167] = 0;
   out_5188989910390169613[168] = 0;
   out_5188989910390169613[169] = 0;
   out_5188989910390169613[170] = 0;
   out_5188989910390169613[171] = 1;
   out_5188989910390169613[172] = 0;
   out_5188989910390169613[173] = 0;
   out_5188989910390169613[174] = 0;
   out_5188989910390169613[175] = 0;
   out_5188989910390169613[176] = 0;
   out_5188989910390169613[177] = 0;
   out_5188989910390169613[178] = 0;
   out_5188989910390169613[179] = 0;
   out_5188989910390169613[180] = 0;
   out_5188989910390169613[181] = 0;
   out_5188989910390169613[182] = 0;
   out_5188989910390169613[183] = 0;
   out_5188989910390169613[184] = 0;
   out_5188989910390169613[185] = 0;
   out_5188989910390169613[186] = 0;
   out_5188989910390169613[187] = 0;
   out_5188989910390169613[188] = 0;
   out_5188989910390169613[189] = 0;
   out_5188989910390169613[190] = 1;
   out_5188989910390169613[191] = 0;
   out_5188989910390169613[192] = 0;
   out_5188989910390169613[193] = 0;
   out_5188989910390169613[194] = 0;
   out_5188989910390169613[195] = 0;
   out_5188989910390169613[196] = 0;
   out_5188989910390169613[197] = 0;
   out_5188989910390169613[198] = 0;
   out_5188989910390169613[199] = 0;
   out_5188989910390169613[200] = 0;
   out_5188989910390169613[201] = 0;
   out_5188989910390169613[202] = 0;
   out_5188989910390169613[203] = 0;
   out_5188989910390169613[204] = 0;
   out_5188989910390169613[205] = 0;
   out_5188989910390169613[206] = 0;
   out_5188989910390169613[207] = 0;
   out_5188989910390169613[208] = 0;
   out_5188989910390169613[209] = 1;
   out_5188989910390169613[210] = 0;
   out_5188989910390169613[211] = 0;
   out_5188989910390169613[212] = 0;
   out_5188989910390169613[213] = 0;
   out_5188989910390169613[214] = 0;
   out_5188989910390169613[215] = 0;
   out_5188989910390169613[216] = 0;
   out_5188989910390169613[217] = 0;
   out_5188989910390169613[218] = 0;
   out_5188989910390169613[219] = 0;
   out_5188989910390169613[220] = 0;
   out_5188989910390169613[221] = 0;
   out_5188989910390169613[222] = 0;
   out_5188989910390169613[223] = 0;
   out_5188989910390169613[224] = 0;
   out_5188989910390169613[225] = 0;
   out_5188989910390169613[226] = 0;
   out_5188989910390169613[227] = 0;
   out_5188989910390169613[228] = 1;
   out_5188989910390169613[229] = 0;
   out_5188989910390169613[230] = 0;
   out_5188989910390169613[231] = 0;
   out_5188989910390169613[232] = 0;
   out_5188989910390169613[233] = 0;
   out_5188989910390169613[234] = 0;
   out_5188989910390169613[235] = 0;
   out_5188989910390169613[236] = 0;
   out_5188989910390169613[237] = 0;
   out_5188989910390169613[238] = 0;
   out_5188989910390169613[239] = 0;
   out_5188989910390169613[240] = 0;
   out_5188989910390169613[241] = 0;
   out_5188989910390169613[242] = 0;
   out_5188989910390169613[243] = 0;
   out_5188989910390169613[244] = 0;
   out_5188989910390169613[245] = 0;
   out_5188989910390169613[246] = 0;
   out_5188989910390169613[247] = 1;
   out_5188989910390169613[248] = 0;
   out_5188989910390169613[249] = 0;
   out_5188989910390169613[250] = 0;
   out_5188989910390169613[251] = 0;
   out_5188989910390169613[252] = 0;
   out_5188989910390169613[253] = 0;
   out_5188989910390169613[254] = 0;
   out_5188989910390169613[255] = 0;
   out_5188989910390169613[256] = 0;
   out_5188989910390169613[257] = 0;
   out_5188989910390169613[258] = 0;
   out_5188989910390169613[259] = 0;
   out_5188989910390169613[260] = 0;
   out_5188989910390169613[261] = 0;
   out_5188989910390169613[262] = 0;
   out_5188989910390169613[263] = 0;
   out_5188989910390169613[264] = 0;
   out_5188989910390169613[265] = 0;
   out_5188989910390169613[266] = 1;
   out_5188989910390169613[267] = 0;
   out_5188989910390169613[268] = 0;
   out_5188989910390169613[269] = 0;
   out_5188989910390169613[270] = 0;
   out_5188989910390169613[271] = 0;
   out_5188989910390169613[272] = 0;
   out_5188989910390169613[273] = 0;
   out_5188989910390169613[274] = 0;
   out_5188989910390169613[275] = 0;
   out_5188989910390169613[276] = 0;
   out_5188989910390169613[277] = 0;
   out_5188989910390169613[278] = 0;
   out_5188989910390169613[279] = 0;
   out_5188989910390169613[280] = 0;
   out_5188989910390169613[281] = 0;
   out_5188989910390169613[282] = 0;
   out_5188989910390169613[283] = 0;
   out_5188989910390169613[284] = 0;
   out_5188989910390169613[285] = 1;
   out_5188989910390169613[286] = 0;
   out_5188989910390169613[287] = 0;
   out_5188989910390169613[288] = 0;
   out_5188989910390169613[289] = 0;
   out_5188989910390169613[290] = 0;
   out_5188989910390169613[291] = 0;
   out_5188989910390169613[292] = 0;
   out_5188989910390169613[293] = 0;
   out_5188989910390169613[294] = 0;
   out_5188989910390169613[295] = 0;
   out_5188989910390169613[296] = 0;
   out_5188989910390169613[297] = 0;
   out_5188989910390169613[298] = 0;
   out_5188989910390169613[299] = 0;
   out_5188989910390169613[300] = 0;
   out_5188989910390169613[301] = 0;
   out_5188989910390169613[302] = 0;
   out_5188989910390169613[303] = 0;
   out_5188989910390169613[304] = 1;
   out_5188989910390169613[305] = 0;
   out_5188989910390169613[306] = 0;
   out_5188989910390169613[307] = 0;
   out_5188989910390169613[308] = 0;
   out_5188989910390169613[309] = 0;
   out_5188989910390169613[310] = 0;
   out_5188989910390169613[311] = 0;
   out_5188989910390169613[312] = 0;
   out_5188989910390169613[313] = 0;
   out_5188989910390169613[314] = 0;
   out_5188989910390169613[315] = 0;
   out_5188989910390169613[316] = 0;
   out_5188989910390169613[317] = 0;
   out_5188989910390169613[318] = 0;
   out_5188989910390169613[319] = 0;
   out_5188989910390169613[320] = 0;
   out_5188989910390169613[321] = 0;
   out_5188989910390169613[322] = 0;
   out_5188989910390169613[323] = 1;
}
void h_4(double *state, double *unused, double *out_3185427494971646342) {
   out_3185427494971646342[0] = state[6] + state[9];
   out_3185427494971646342[1] = state[7] + state[10];
   out_3185427494971646342[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_7645653056206011068) {
   out_7645653056206011068[0] = 0;
   out_7645653056206011068[1] = 0;
   out_7645653056206011068[2] = 0;
   out_7645653056206011068[3] = 0;
   out_7645653056206011068[4] = 0;
   out_7645653056206011068[5] = 0;
   out_7645653056206011068[6] = 1;
   out_7645653056206011068[7] = 0;
   out_7645653056206011068[8] = 0;
   out_7645653056206011068[9] = 1;
   out_7645653056206011068[10] = 0;
   out_7645653056206011068[11] = 0;
   out_7645653056206011068[12] = 0;
   out_7645653056206011068[13] = 0;
   out_7645653056206011068[14] = 0;
   out_7645653056206011068[15] = 0;
   out_7645653056206011068[16] = 0;
   out_7645653056206011068[17] = 0;
   out_7645653056206011068[18] = 0;
   out_7645653056206011068[19] = 0;
   out_7645653056206011068[20] = 0;
   out_7645653056206011068[21] = 0;
   out_7645653056206011068[22] = 0;
   out_7645653056206011068[23] = 0;
   out_7645653056206011068[24] = 0;
   out_7645653056206011068[25] = 1;
   out_7645653056206011068[26] = 0;
   out_7645653056206011068[27] = 0;
   out_7645653056206011068[28] = 1;
   out_7645653056206011068[29] = 0;
   out_7645653056206011068[30] = 0;
   out_7645653056206011068[31] = 0;
   out_7645653056206011068[32] = 0;
   out_7645653056206011068[33] = 0;
   out_7645653056206011068[34] = 0;
   out_7645653056206011068[35] = 0;
   out_7645653056206011068[36] = 0;
   out_7645653056206011068[37] = 0;
   out_7645653056206011068[38] = 0;
   out_7645653056206011068[39] = 0;
   out_7645653056206011068[40] = 0;
   out_7645653056206011068[41] = 0;
   out_7645653056206011068[42] = 0;
   out_7645653056206011068[43] = 0;
   out_7645653056206011068[44] = 1;
   out_7645653056206011068[45] = 0;
   out_7645653056206011068[46] = 0;
   out_7645653056206011068[47] = 1;
   out_7645653056206011068[48] = 0;
   out_7645653056206011068[49] = 0;
   out_7645653056206011068[50] = 0;
   out_7645653056206011068[51] = 0;
   out_7645653056206011068[52] = 0;
   out_7645653056206011068[53] = 0;
}
void h_10(double *state, double *unused, double *out_8120018998606381774) {
   out_8120018998606381774[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_8120018998606381774[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_8120018998606381774[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_2849047297491274617) {
   out_2849047297491274617[0] = 0;
   out_2849047297491274617[1] = 9.8100000000000005*cos(state[1]);
   out_2849047297491274617[2] = 0;
   out_2849047297491274617[3] = 0;
   out_2849047297491274617[4] = -state[8];
   out_2849047297491274617[5] = state[7];
   out_2849047297491274617[6] = 0;
   out_2849047297491274617[7] = state[5];
   out_2849047297491274617[8] = -state[4];
   out_2849047297491274617[9] = 0;
   out_2849047297491274617[10] = 0;
   out_2849047297491274617[11] = 0;
   out_2849047297491274617[12] = 1;
   out_2849047297491274617[13] = 0;
   out_2849047297491274617[14] = 0;
   out_2849047297491274617[15] = 1;
   out_2849047297491274617[16] = 0;
   out_2849047297491274617[17] = 0;
   out_2849047297491274617[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_2849047297491274617[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_2849047297491274617[20] = 0;
   out_2849047297491274617[21] = state[8];
   out_2849047297491274617[22] = 0;
   out_2849047297491274617[23] = -state[6];
   out_2849047297491274617[24] = -state[5];
   out_2849047297491274617[25] = 0;
   out_2849047297491274617[26] = state[3];
   out_2849047297491274617[27] = 0;
   out_2849047297491274617[28] = 0;
   out_2849047297491274617[29] = 0;
   out_2849047297491274617[30] = 0;
   out_2849047297491274617[31] = 1;
   out_2849047297491274617[32] = 0;
   out_2849047297491274617[33] = 0;
   out_2849047297491274617[34] = 1;
   out_2849047297491274617[35] = 0;
   out_2849047297491274617[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_2849047297491274617[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_2849047297491274617[38] = 0;
   out_2849047297491274617[39] = -state[7];
   out_2849047297491274617[40] = state[6];
   out_2849047297491274617[41] = 0;
   out_2849047297491274617[42] = state[4];
   out_2849047297491274617[43] = -state[3];
   out_2849047297491274617[44] = 0;
   out_2849047297491274617[45] = 0;
   out_2849047297491274617[46] = 0;
   out_2849047297491274617[47] = 0;
   out_2849047297491274617[48] = 0;
   out_2849047297491274617[49] = 0;
   out_2849047297491274617[50] = 1;
   out_2849047297491274617[51] = 0;
   out_2849047297491274617[52] = 0;
   out_2849047297491274617[53] = 1;
}
void h_13(double *state, double *unused, double *out_8173327387295448263) {
   out_8173327387295448263[0] = state[3];
   out_8173327387295448263[1] = state[4];
   out_8173327387295448263[2] = state[5];
}
void H_13(double *state, double *unused, double *out_7588817192171207747) {
   out_7588817192171207747[0] = 0;
   out_7588817192171207747[1] = 0;
   out_7588817192171207747[2] = 0;
   out_7588817192171207747[3] = 1;
   out_7588817192171207747[4] = 0;
   out_7588817192171207747[5] = 0;
   out_7588817192171207747[6] = 0;
   out_7588817192171207747[7] = 0;
   out_7588817192171207747[8] = 0;
   out_7588817192171207747[9] = 0;
   out_7588817192171207747[10] = 0;
   out_7588817192171207747[11] = 0;
   out_7588817192171207747[12] = 0;
   out_7588817192171207747[13] = 0;
   out_7588817192171207747[14] = 0;
   out_7588817192171207747[15] = 0;
   out_7588817192171207747[16] = 0;
   out_7588817192171207747[17] = 0;
   out_7588817192171207747[18] = 0;
   out_7588817192171207747[19] = 0;
   out_7588817192171207747[20] = 0;
   out_7588817192171207747[21] = 0;
   out_7588817192171207747[22] = 1;
   out_7588817192171207747[23] = 0;
   out_7588817192171207747[24] = 0;
   out_7588817192171207747[25] = 0;
   out_7588817192171207747[26] = 0;
   out_7588817192171207747[27] = 0;
   out_7588817192171207747[28] = 0;
   out_7588817192171207747[29] = 0;
   out_7588817192171207747[30] = 0;
   out_7588817192171207747[31] = 0;
   out_7588817192171207747[32] = 0;
   out_7588817192171207747[33] = 0;
   out_7588817192171207747[34] = 0;
   out_7588817192171207747[35] = 0;
   out_7588817192171207747[36] = 0;
   out_7588817192171207747[37] = 0;
   out_7588817192171207747[38] = 0;
   out_7588817192171207747[39] = 0;
   out_7588817192171207747[40] = 0;
   out_7588817192171207747[41] = 1;
   out_7588817192171207747[42] = 0;
   out_7588817192171207747[43] = 0;
   out_7588817192171207747[44] = 0;
   out_7588817192171207747[45] = 0;
   out_7588817192171207747[46] = 0;
   out_7588817192171207747[47] = 0;
   out_7588817192171207747[48] = 0;
   out_7588817192171207747[49] = 0;
   out_7588817192171207747[50] = 0;
   out_7588817192171207747[51] = 0;
   out_7588817192171207747[52] = 0;
   out_7588817192171207747[53] = 0;
}
void h_14(double *state, double *unused, double *out_2707962449685458083) {
   out_2707962449685458083[0] = state[6];
   out_2707962449685458083[1] = state[7];
   out_2707962449685458083[2] = state[8];
}
void H_14(double *state, double *unused, double *out_6837850161164056019) {
   out_6837850161164056019[0] = 0;
   out_6837850161164056019[1] = 0;
   out_6837850161164056019[2] = 0;
   out_6837850161164056019[3] = 0;
   out_6837850161164056019[4] = 0;
   out_6837850161164056019[5] = 0;
   out_6837850161164056019[6] = 1;
   out_6837850161164056019[7] = 0;
   out_6837850161164056019[8] = 0;
   out_6837850161164056019[9] = 0;
   out_6837850161164056019[10] = 0;
   out_6837850161164056019[11] = 0;
   out_6837850161164056019[12] = 0;
   out_6837850161164056019[13] = 0;
   out_6837850161164056019[14] = 0;
   out_6837850161164056019[15] = 0;
   out_6837850161164056019[16] = 0;
   out_6837850161164056019[17] = 0;
   out_6837850161164056019[18] = 0;
   out_6837850161164056019[19] = 0;
   out_6837850161164056019[20] = 0;
   out_6837850161164056019[21] = 0;
   out_6837850161164056019[22] = 0;
   out_6837850161164056019[23] = 0;
   out_6837850161164056019[24] = 0;
   out_6837850161164056019[25] = 1;
   out_6837850161164056019[26] = 0;
   out_6837850161164056019[27] = 0;
   out_6837850161164056019[28] = 0;
   out_6837850161164056019[29] = 0;
   out_6837850161164056019[30] = 0;
   out_6837850161164056019[31] = 0;
   out_6837850161164056019[32] = 0;
   out_6837850161164056019[33] = 0;
   out_6837850161164056019[34] = 0;
   out_6837850161164056019[35] = 0;
   out_6837850161164056019[36] = 0;
   out_6837850161164056019[37] = 0;
   out_6837850161164056019[38] = 0;
   out_6837850161164056019[39] = 0;
   out_6837850161164056019[40] = 0;
   out_6837850161164056019[41] = 0;
   out_6837850161164056019[42] = 0;
   out_6837850161164056019[43] = 0;
   out_6837850161164056019[44] = 1;
   out_6837850161164056019[45] = 0;
   out_6837850161164056019[46] = 0;
   out_6837850161164056019[47] = 0;
   out_6837850161164056019[48] = 0;
   out_6837850161164056019[49] = 0;
   out_6837850161164056019[50] = 0;
   out_6837850161164056019[51] = 0;
   out_6837850161164056019[52] = 0;
   out_6837850161164056019[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_1454459679057110584) {
  err_fun(nom_x, delta_x, out_1454459679057110584);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_8466886164721569510) {
  inv_err_fun(nom_x, true_x, out_8466886164721569510);
}
void pose_H_mod_fun(double *state, double *out_6891492054151298461) {
  H_mod_fun(state, out_6891492054151298461);
}
void pose_f_fun(double *state, double dt, double *out_6198631950895505143) {
  f_fun(state,  dt, out_6198631950895505143);
}
void pose_F_fun(double *state, double dt, double *out_5188989910390169613) {
  F_fun(state,  dt, out_5188989910390169613);
}
void pose_h_4(double *state, double *unused, double *out_3185427494971646342) {
  h_4(state, unused, out_3185427494971646342);
}
void pose_H_4(double *state, double *unused, double *out_7645653056206011068) {
  H_4(state, unused, out_7645653056206011068);
}
void pose_h_10(double *state, double *unused, double *out_8120018998606381774) {
  h_10(state, unused, out_8120018998606381774);
}
void pose_H_10(double *state, double *unused, double *out_2849047297491274617) {
  H_10(state, unused, out_2849047297491274617);
}
void pose_h_13(double *state, double *unused, double *out_8173327387295448263) {
  h_13(state, unused, out_8173327387295448263);
}
void pose_H_13(double *state, double *unused, double *out_7588817192171207747) {
  H_13(state, unused, out_7588817192171207747);
}
void pose_h_14(double *state, double *unused, double *out_2707962449685458083) {
  h_14(state, unused, out_2707962449685458083);
}
void pose_H_14(double *state, double *unused, double *out_6837850161164056019) {
  H_14(state, unused, out_6837850161164056019);
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
