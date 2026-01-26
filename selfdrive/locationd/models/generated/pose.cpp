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
void err_fun(double *nom_x, double *delta_x, double *out_7790108905973441094) {
   out_7790108905973441094[0] = delta_x[0] + nom_x[0];
   out_7790108905973441094[1] = delta_x[1] + nom_x[1];
   out_7790108905973441094[2] = delta_x[2] + nom_x[2];
   out_7790108905973441094[3] = delta_x[3] + nom_x[3];
   out_7790108905973441094[4] = delta_x[4] + nom_x[4];
   out_7790108905973441094[5] = delta_x[5] + nom_x[5];
   out_7790108905973441094[6] = delta_x[6] + nom_x[6];
   out_7790108905973441094[7] = delta_x[7] + nom_x[7];
   out_7790108905973441094[8] = delta_x[8] + nom_x[8];
   out_7790108905973441094[9] = delta_x[9] + nom_x[9];
   out_7790108905973441094[10] = delta_x[10] + nom_x[10];
   out_7790108905973441094[11] = delta_x[11] + nom_x[11];
   out_7790108905973441094[12] = delta_x[12] + nom_x[12];
   out_7790108905973441094[13] = delta_x[13] + nom_x[13];
   out_7790108905973441094[14] = delta_x[14] + nom_x[14];
   out_7790108905973441094[15] = delta_x[15] + nom_x[15];
   out_7790108905973441094[16] = delta_x[16] + nom_x[16];
   out_7790108905973441094[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_3044307321253503213) {
   out_3044307321253503213[0] = -nom_x[0] + true_x[0];
   out_3044307321253503213[1] = -nom_x[1] + true_x[1];
   out_3044307321253503213[2] = -nom_x[2] + true_x[2];
   out_3044307321253503213[3] = -nom_x[3] + true_x[3];
   out_3044307321253503213[4] = -nom_x[4] + true_x[4];
   out_3044307321253503213[5] = -nom_x[5] + true_x[5];
   out_3044307321253503213[6] = -nom_x[6] + true_x[6];
   out_3044307321253503213[7] = -nom_x[7] + true_x[7];
   out_3044307321253503213[8] = -nom_x[8] + true_x[8];
   out_3044307321253503213[9] = -nom_x[9] + true_x[9];
   out_3044307321253503213[10] = -nom_x[10] + true_x[10];
   out_3044307321253503213[11] = -nom_x[11] + true_x[11];
   out_3044307321253503213[12] = -nom_x[12] + true_x[12];
   out_3044307321253503213[13] = -nom_x[13] + true_x[13];
   out_3044307321253503213[14] = -nom_x[14] + true_x[14];
   out_3044307321253503213[15] = -nom_x[15] + true_x[15];
   out_3044307321253503213[16] = -nom_x[16] + true_x[16];
   out_3044307321253503213[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_2507391073749515951) {
   out_2507391073749515951[0] = 1.0;
   out_2507391073749515951[1] = 0.0;
   out_2507391073749515951[2] = 0.0;
   out_2507391073749515951[3] = 0.0;
   out_2507391073749515951[4] = 0.0;
   out_2507391073749515951[5] = 0.0;
   out_2507391073749515951[6] = 0.0;
   out_2507391073749515951[7] = 0.0;
   out_2507391073749515951[8] = 0.0;
   out_2507391073749515951[9] = 0.0;
   out_2507391073749515951[10] = 0.0;
   out_2507391073749515951[11] = 0.0;
   out_2507391073749515951[12] = 0.0;
   out_2507391073749515951[13] = 0.0;
   out_2507391073749515951[14] = 0.0;
   out_2507391073749515951[15] = 0.0;
   out_2507391073749515951[16] = 0.0;
   out_2507391073749515951[17] = 0.0;
   out_2507391073749515951[18] = 0.0;
   out_2507391073749515951[19] = 1.0;
   out_2507391073749515951[20] = 0.0;
   out_2507391073749515951[21] = 0.0;
   out_2507391073749515951[22] = 0.0;
   out_2507391073749515951[23] = 0.0;
   out_2507391073749515951[24] = 0.0;
   out_2507391073749515951[25] = 0.0;
   out_2507391073749515951[26] = 0.0;
   out_2507391073749515951[27] = 0.0;
   out_2507391073749515951[28] = 0.0;
   out_2507391073749515951[29] = 0.0;
   out_2507391073749515951[30] = 0.0;
   out_2507391073749515951[31] = 0.0;
   out_2507391073749515951[32] = 0.0;
   out_2507391073749515951[33] = 0.0;
   out_2507391073749515951[34] = 0.0;
   out_2507391073749515951[35] = 0.0;
   out_2507391073749515951[36] = 0.0;
   out_2507391073749515951[37] = 0.0;
   out_2507391073749515951[38] = 1.0;
   out_2507391073749515951[39] = 0.0;
   out_2507391073749515951[40] = 0.0;
   out_2507391073749515951[41] = 0.0;
   out_2507391073749515951[42] = 0.0;
   out_2507391073749515951[43] = 0.0;
   out_2507391073749515951[44] = 0.0;
   out_2507391073749515951[45] = 0.0;
   out_2507391073749515951[46] = 0.0;
   out_2507391073749515951[47] = 0.0;
   out_2507391073749515951[48] = 0.0;
   out_2507391073749515951[49] = 0.0;
   out_2507391073749515951[50] = 0.0;
   out_2507391073749515951[51] = 0.0;
   out_2507391073749515951[52] = 0.0;
   out_2507391073749515951[53] = 0.0;
   out_2507391073749515951[54] = 0.0;
   out_2507391073749515951[55] = 0.0;
   out_2507391073749515951[56] = 0.0;
   out_2507391073749515951[57] = 1.0;
   out_2507391073749515951[58] = 0.0;
   out_2507391073749515951[59] = 0.0;
   out_2507391073749515951[60] = 0.0;
   out_2507391073749515951[61] = 0.0;
   out_2507391073749515951[62] = 0.0;
   out_2507391073749515951[63] = 0.0;
   out_2507391073749515951[64] = 0.0;
   out_2507391073749515951[65] = 0.0;
   out_2507391073749515951[66] = 0.0;
   out_2507391073749515951[67] = 0.0;
   out_2507391073749515951[68] = 0.0;
   out_2507391073749515951[69] = 0.0;
   out_2507391073749515951[70] = 0.0;
   out_2507391073749515951[71] = 0.0;
   out_2507391073749515951[72] = 0.0;
   out_2507391073749515951[73] = 0.0;
   out_2507391073749515951[74] = 0.0;
   out_2507391073749515951[75] = 0.0;
   out_2507391073749515951[76] = 1.0;
   out_2507391073749515951[77] = 0.0;
   out_2507391073749515951[78] = 0.0;
   out_2507391073749515951[79] = 0.0;
   out_2507391073749515951[80] = 0.0;
   out_2507391073749515951[81] = 0.0;
   out_2507391073749515951[82] = 0.0;
   out_2507391073749515951[83] = 0.0;
   out_2507391073749515951[84] = 0.0;
   out_2507391073749515951[85] = 0.0;
   out_2507391073749515951[86] = 0.0;
   out_2507391073749515951[87] = 0.0;
   out_2507391073749515951[88] = 0.0;
   out_2507391073749515951[89] = 0.0;
   out_2507391073749515951[90] = 0.0;
   out_2507391073749515951[91] = 0.0;
   out_2507391073749515951[92] = 0.0;
   out_2507391073749515951[93] = 0.0;
   out_2507391073749515951[94] = 0.0;
   out_2507391073749515951[95] = 1.0;
   out_2507391073749515951[96] = 0.0;
   out_2507391073749515951[97] = 0.0;
   out_2507391073749515951[98] = 0.0;
   out_2507391073749515951[99] = 0.0;
   out_2507391073749515951[100] = 0.0;
   out_2507391073749515951[101] = 0.0;
   out_2507391073749515951[102] = 0.0;
   out_2507391073749515951[103] = 0.0;
   out_2507391073749515951[104] = 0.0;
   out_2507391073749515951[105] = 0.0;
   out_2507391073749515951[106] = 0.0;
   out_2507391073749515951[107] = 0.0;
   out_2507391073749515951[108] = 0.0;
   out_2507391073749515951[109] = 0.0;
   out_2507391073749515951[110] = 0.0;
   out_2507391073749515951[111] = 0.0;
   out_2507391073749515951[112] = 0.0;
   out_2507391073749515951[113] = 0.0;
   out_2507391073749515951[114] = 1.0;
   out_2507391073749515951[115] = 0.0;
   out_2507391073749515951[116] = 0.0;
   out_2507391073749515951[117] = 0.0;
   out_2507391073749515951[118] = 0.0;
   out_2507391073749515951[119] = 0.0;
   out_2507391073749515951[120] = 0.0;
   out_2507391073749515951[121] = 0.0;
   out_2507391073749515951[122] = 0.0;
   out_2507391073749515951[123] = 0.0;
   out_2507391073749515951[124] = 0.0;
   out_2507391073749515951[125] = 0.0;
   out_2507391073749515951[126] = 0.0;
   out_2507391073749515951[127] = 0.0;
   out_2507391073749515951[128] = 0.0;
   out_2507391073749515951[129] = 0.0;
   out_2507391073749515951[130] = 0.0;
   out_2507391073749515951[131] = 0.0;
   out_2507391073749515951[132] = 0.0;
   out_2507391073749515951[133] = 1.0;
   out_2507391073749515951[134] = 0.0;
   out_2507391073749515951[135] = 0.0;
   out_2507391073749515951[136] = 0.0;
   out_2507391073749515951[137] = 0.0;
   out_2507391073749515951[138] = 0.0;
   out_2507391073749515951[139] = 0.0;
   out_2507391073749515951[140] = 0.0;
   out_2507391073749515951[141] = 0.0;
   out_2507391073749515951[142] = 0.0;
   out_2507391073749515951[143] = 0.0;
   out_2507391073749515951[144] = 0.0;
   out_2507391073749515951[145] = 0.0;
   out_2507391073749515951[146] = 0.0;
   out_2507391073749515951[147] = 0.0;
   out_2507391073749515951[148] = 0.0;
   out_2507391073749515951[149] = 0.0;
   out_2507391073749515951[150] = 0.0;
   out_2507391073749515951[151] = 0.0;
   out_2507391073749515951[152] = 1.0;
   out_2507391073749515951[153] = 0.0;
   out_2507391073749515951[154] = 0.0;
   out_2507391073749515951[155] = 0.0;
   out_2507391073749515951[156] = 0.0;
   out_2507391073749515951[157] = 0.0;
   out_2507391073749515951[158] = 0.0;
   out_2507391073749515951[159] = 0.0;
   out_2507391073749515951[160] = 0.0;
   out_2507391073749515951[161] = 0.0;
   out_2507391073749515951[162] = 0.0;
   out_2507391073749515951[163] = 0.0;
   out_2507391073749515951[164] = 0.0;
   out_2507391073749515951[165] = 0.0;
   out_2507391073749515951[166] = 0.0;
   out_2507391073749515951[167] = 0.0;
   out_2507391073749515951[168] = 0.0;
   out_2507391073749515951[169] = 0.0;
   out_2507391073749515951[170] = 0.0;
   out_2507391073749515951[171] = 1.0;
   out_2507391073749515951[172] = 0.0;
   out_2507391073749515951[173] = 0.0;
   out_2507391073749515951[174] = 0.0;
   out_2507391073749515951[175] = 0.0;
   out_2507391073749515951[176] = 0.0;
   out_2507391073749515951[177] = 0.0;
   out_2507391073749515951[178] = 0.0;
   out_2507391073749515951[179] = 0.0;
   out_2507391073749515951[180] = 0.0;
   out_2507391073749515951[181] = 0.0;
   out_2507391073749515951[182] = 0.0;
   out_2507391073749515951[183] = 0.0;
   out_2507391073749515951[184] = 0.0;
   out_2507391073749515951[185] = 0.0;
   out_2507391073749515951[186] = 0.0;
   out_2507391073749515951[187] = 0.0;
   out_2507391073749515951[188] = 0.0;
   out_2507391073749515951[189] = 0.0;
   out_2507391073749515951[190] = 1.0;
   out_2507391073749515951[191] = 0.0;
   out_2507391073749515951[192] = 0.0;
   out_2507391073749515951[193] = 0.0;
   out_2507391073749515951[194] = 0.0;
   out_2507391073749515951[195] = 0.0;
   out_2507391073749515951[196] = 0.0;
   out_2507391073749515951[197] = 0.0;
   out_2507391073749515951[198] = 0.0;
   out_2507391073749515951[199] = 0.0;
   out_2507391073749515951[200] = 0.0;
   out_2507391073749515951[201] = 0.0;
   out_2507391073749515951[202] = 0.0;
   out_2507391073749515951[203] = 0.0;
   out_2507391073749515951[204] = 0.0;
   out_2507391073749515951[205] = 0.0;
   out_2507391073749515951[206] = 0.0;
   out_2507391073749515951[207] = 0.0;
   out_2507391073749515951[208] = 0.0;
   out_2507391073749515951[209] = 1.0;
   out_2507391073749515951[210] = 0.0;
   out_2507391073749515951[211] = 0.0;
   out_2507391073749515951[212] = 0.0;
   out_2507391073749515951[213] = 0.0;
   out_2507391073749515951[214] = 0.0;
   out_2507391073749515951[215] = 0.0;
   out_2507391073749515951[216] = 0.0;
   out_2507391073749515951[217] = 0.0;
   out_2507391073749515951[218] = 0.0;
   out_2507391073749515951[219] = 0.0;
   out_2507391073749515951[220] = 0.0;
   out_2507391073749515951[221] = 0.0;
   out_2507391073749515951[222] = 0.0;
   out_2507391073749515951[223] = 0.0;
   out_2507391073749515951[224] = 0.0;
   out_2507391073749515951[225] = 0.0;
   out_2507391073749515951[226] = 0.0;
   out_2507391073749515951[227] = 0.0;
   out_2507391073749515951[228] = 1.0;
   out_2507391073749515951[229] = 0.0;
   out_2507391073749515951[230] = 0.0;
   out_2507391073749515951[231] = 0.0;
   out_2507391073749515951[232] = 0.0;
   out_2507391073749515951[233] = 0.0;
   out_2507391073749515951[234] = 0.0;
   out_2507391073749515951[235] = 0.0;
   out_2507391073749515951[236] = 0.0;
   out_2507391073749515951[237] = 0.0;
   out_2507391073749515951[238] = 0.0;
   out_2507391073749515951[239] = 0.0;
   out_2507391073749515951[240] = 0.0;
   out_2507391073749515951[241] = 0.0;
   out_2507391073749515951[242] = 0.0;
   out_2507391073749515951[243] = 0.0;
   out_2507391073749515951[244] = 0.0;
   out_2507391073749515951[245] = 0.0;
   out_2507391073749515951[246] = 0.0;
   out_2507391073749515951[247] = 1.0;
   out_2507391073749515951[248] = 0.0;
   out_2507391073749515951[249] = 0.0;
   out_2507391073749515951[250] = 0.0;
   out_2507391073749515951[251] = 0.0;
   out_2507391073749515951[252] = 0.0;
   out_2507391073749515951[253] = 0.0;
   out_2507391073749515951[254] = 0.0;
   out_2507391073749515951[255] = 0.0;
   out_2507391073749515951[256] = 0.0;
   out_2507391073749515951[257] = 0.0;
   out_2507391073749515951[258] = 0.0;
   out_2507391073749515951[259] = 0.0;
   out_2507391073749515951[260] = 0.0;
   out_2507391073749515951[261] = 0.0;
   out_2507391073749515951[262] = 0.0;
   out_2507391073749515951[263] = 0.0;
   out_2507391073749515951[264] = 0.0;
   out_2507391073749515951[265] = 0.0;
   out_2507391073749515951[266] = 1.0;
   out_2507391073749515951[267] = 0.0;
   out_2507391073749515951[268] = 0.0;
   out_2507391073749515951[269] = 0.0;
   out_2507391073749515951[270] = 0.0;
   out_2507391073749515951[271] = 0.0;
   out_2507391073749515951[272] = 0.0;
   out_2507391073749515951[273] = 0.0;
   out_2507391073749515951[274] = 0.0;
   out_2507391073749515951[275] = 0.0;
   out_2507391073749515951[276] = 0.0;
   out_2507391073749515951[277] = 0.0;
   out_2507391073749515951[278] = 0.0;
   out_2507391073749515951[279] = 0.0;
   out_2507391073749515951[280] = 0.0;
   out_2507391073749515951[281] = 0.0;
   out_2507391073749515951[282] = 0.0;
   out_2507391073749515951[283] = 0.0;
   out_2507391073749515951[284] = 0.0;
   out_2507391073749515951[285] = 1.0;
   out_2507391073749515951[286] = 0.0;
   out_2507391073749515951[287] = 0.0;
   out_2507391073749515951[288] = 0.0;
   out_2507391073749515951[289] = 0.0;
   out_2507391073749515951[290] = 0.0;
   out_2507391073749515951[291] = 0.0;
   out_2507391073749515951[292] = 0.0;
   out_2507391073749515951[293] = 0.0;
   out_2507391073749515951[294] = 0.0;
   out_2507391073749515951[295] = 0.0;
   out_2507391073749515951[296] = 0.0;
   out_2507391073749515951[297] = 0.0;
   out_2507391073749515951[298] = 0.0;
   out_2507391073749515951[299] = 0.0;
   out_2507391073749515951[300] = 0.0;
   out_2507391073749515951[301] = 0.0;
   out_2507391073749515951[302] = 0.0;
   out_2507391073749515951[303] = 0.0;
   out_2507391073749515951[304] = 1.0;
   out_2507391073749515951[305] = 0.0;
   out_2507391073749515951[306] = 0.0;
   out_2507391073749515951[307] = 0.0;
   out_2507391073749515951[308] = 0.0;
   out_2507391073749515951[309] = 0.0;
   out_2507391073749515951[310] = 0.0;
   out_2507391073749515951[311] = 0.0;
   out_2507391073749515951[312] = 0.0;
   out_2507391073749515951[313] = 0.0;
   out_2507391073749515951[314] = 0.0;
   out_2507391073749515951[315] = 0.0;
   out_2507391073749515951[316] = 0.0;
   out_2507391073749515951[317] = 0.0;
   out_2507391073749515951[318] = 0.0;
   out_2507391073749515951[319] = 0.0;
   out_2507391073749515951[320] = 0.0;
   out_2507391073749515951[321] = 0.0;
   out_2507391073749515951[322] = 0.0;
   out_2507391073749515951[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_8106374632162380060) {
   out_8106374632162380060[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_8106374632162380060[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_8106374632162380060[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_8106374632162380060[3] = dt*state[12] + state[3];
   out_8106374632162380060[4] = dt*state[13] + state[4];
   out_8106374632162380060[5] = dt*state[14] + state[5];
   out_8106374632162380060[6] = state[6];
   out_8106374632162380060[7] = state[7];
   out_8106374632162380060[8] = state[8];
   out_8106374632162380060[9] = state[9];
   out_8106374632162380060[10] = state[10];
   out_8106374632162380060[11] = state[11];
   out_8106374632162380060[12] = state[12];
   out_8106374632162380060[13] = state[13];
   out_8106374632162380060[14] = state[14];
   out_8106374632162380060[15] = state[15];
   out_8106374632162380060[16] = state[16];
   out_8106374632162380060[17] = state[17];
}
void F_fun(double *state, double dt, double *out_8926088300008410432) {
   out_8926088300008410432[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8926088300008410432[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8926088300008410432[2] = 0;
   out_8926088300008410432[3] = 0;
   out_8926088300008410432[4] = 0;
   out_8926088300008410432[5] = 0;
   out_8926088300008410432[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8926088300008410432[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8926088300008410432[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8926088300008410432[9] = 0;
   out_8926088300008410432[10] = 0;
   out_8926088300008410432[11] = 0;
   out_8926088300008410432[12] = 0;
   out_8926088300008410432[13] = 0;
   out_8926088300008410432[14] = 0;
   out_8926088300008410432[15] = 0;
   out_8926088300008410432[16] = 0;
   out_8926088300008410432[17] = 0;
   out_8926088300008410432[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8926088300008410432[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8926088300008410432[20] = 0;
   out_8926088300008410432[21] = 0;
   out_8926088300008410432[22] = 0;
   out_8926088300008410432[23] = 0;
   out_8926088300008410432[24] = 0;
   out_8926088300008410432[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8926088300008410432[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8926088300008410432[27] = 0;
   out_8926088300008410432[28] = 0;
   out_8926088300008410432[29] = 0;
   out_8926088300008410432[30] = 0;
   out_8926088300008410432[31] = 0;
   out_8926088300008410432[32] = 0;
   out_8926088300008410432[33] = 0;
   out_8926088300008410432[34] = 0;
   out_8926088300008410432[35] = 0;
   out_8926088300008410432[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8926088300008410432[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8926088300008410432[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8926088300008410432[39] = 0;
   out_8926088300008410432[40] = 0;
   out_8926088300008410432[41] = 0;
   out_8926088300008410432[42] = 0;
   out_8926088300008410432[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8926088300008410432[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8926088300008410432[45] = 0;
   out_8926088300008410432[46] = 0;
   out_8926088300008410432[47] = 0;
   out_8926088300008410432[48] = 0;
   out_8926088300008410432[49] = 0;
   out_8926088300008410432[50] = 0;
   out_8926088300008410432[51] = 0;
   out_8926088300008410432[52] = 0;
   out_8926088300008410432[53] = 0;
   out_8926088300008410432[54] = 0;
   out_8926088300008410432[55] = 0;
   out_8926088300008410432[56] = 0;
   out_8926088300008410432[57] = 1;
   out_8926088300008410432[58] = 0;
   out_8926088300008410432[59] = 0;
   out_8926088300008410432[60] = 0;
   out_8926088300008410432[61] = 0;
   out_8926088300008410432[62] = 0;
   out_8926088300008410432[63] = 0;
   out_8926088300008410432[64] = 0;
   out_8926088300008410432[65] = 0;
   out_8926088300008410432[66] = dt;
   out_8926088300008410432[67] = 0;
   out_8926088300008410432[68] = 0;
   out_8926088300008410432[69] = 0;
   out_8926088300008410432[70] = 0;
   out_8926088300008410432[71] = 0;
   out_8926088300008410432[72] = 0;
   out_8926088300008410432[73] = 0;
   out_8926088300008410432[74] = 0;
   out_8926088300008410432[75] = 0;
   out_8926088300008410432[76] = 1;
   out_8926088300008410432[77] = 0;
   out_8926088300008410432[78] = 0;
   out_8926088300008410432[79] = 0;
   out_8926088300008410432[80] = 0;
   out_8926088300008410432[81] = 0;
   out_8926088300008410432[82] = 0;
   out_8926088300008410432[83] = 0;
   out_8926088300008410432[84] = 0;
   out_8926088300008410432[85] = dt;
   out_8926088300008410432[86] = 0;
   out_8926088300008410432[87] = 0;
   out_8926088300008410432[88] = 0;
   out_8926088300008410432[89] = 0;
   out_8926088300008410432[90] = 0;
   out_8926088300008410432[91] = 0;
   out_8926088300008410432[92] = 0;
   out_8926088300008410432[93] = 0;
   out_8926088300008410432[94] = 0;
   out_8926088300008410432[95] = 1;
   out_8926088300008410432[96] = 0;
   out_8926088300008410432[97] = 0;
   out_8926088300008410432[98] = 0;
   out_8926088300008410432[99] = 0;
   out_8926088300008410432[100] = 0;
   out_8926088300008410432[101] = 0;
   out_8926088300008410432[102] = 0;
   out_8926088300008410432[103] = 0;
   out_8926088300008410432[104] = dt;
   out_8926088300008410432[105] = 0;
   out_8926088300008410432[106] = 0;
   out_8926088300008410432[107] = 0;
   out_8926088300008410432[108] = 0;
   out_8926088300008410432[109] = 0;
   out_8926088300008410432[110] = 0;
   out_8926088300008410432[111] = 0;
   out_8926088300008410432[112] = 0;
   out_8926088300008410432[113] = 0;
   out_8926088300008410432[114] = 1;
   out_8926088300008410432[115] = 0;
   out_8926088300008410432[116] = 0;
   out_8926088300008410432[117] = 0;
   out_8926088300008410432[118] = 0;
   out_8926088300008410432[119] = 0;
   out_8926088300008410432[120] = 0;
   out_8926088300008410432[121] = 0;
   out_8926088300008410432[122] = 0;
   out_8926088300008410432[123] = 0;
   out_8926088300008410432[124] = 0;
   out_8926088300008410432[125] = 0;
   out_8926088300008410432[126] = 0;
   out_8926088300008410432[127] = 0;
   out_8926088300008410432[128] = 0;
   out_8926088300008410432[129] = 0;
   out_8926088300008410432[130] = 0;
   out_8926088300008410432[131] = 0;
   out_8926088300008410432[132] = 0;
   out_8926088300008410432[133] = 1;
   out_8926088300008410432[134] = 0;
   out_8926088300008410432[135] = 0;
   out_8926088300008410432[136] = 0;
   out_8926088300008410432[137] = 0;
   out_8926088300008410432[138] = 0;
   out_8926088300008410432[139] = 0;
   out_8926088300008410432[140] = 0;
   out_8926088300008410432[141] = 0;
   out_8926088300008410432[142] = 0;
   out_8926088300008410432[143] = 0;
   out_8926088300008410432[144] = 0;
   out_8926088300008410432[145] = 0;
   out_8926088300008410432[146] = 0;
   out_8926088300008410432[147] = 0;
   out_8926088300008410432[148] = 0;
   out_8926088300008410432[149] = 0;
   out_8926088300008410432[150] = 0;
   out_8926088300008410432[151] = 0;
   out_8926088300008410432[152] = 1;
   out_8926088300008410432[153] = 0;
   out_8926088300008410432[154] = 0;
   out_8926088300008410432[155] = 0;
   out_8926088300008410432[156] = 0;
   out_8926088300008410432[157] = 0;
   out_8926088300008410432[158] = 0;
   out_8926088300008410432[159] = 0;
   out_8926088300008410432[160] = 0;
   out_8926088300008410432[161] = 0;
   out_8926088300008410432[162] = 0;
   out_8926088300008410432[163] = 0;
   out_8926088300008410432[164] = 0;
   out_8926088300008410432[165] = 0;
   out_8926088300008410432[166] = 0;
   out_8926088300008410432[167] = 0;
   out_8926088300008410432[168] = 0;
   out_8926088300008410432[169] = 0;
   out_8926088300008410432[170] = 0;
   out_8926088300008410432[171] = 1;
   out_8926088300008410432[172] = 0;
   out_8926088300008410432[173] = 0;
   out_8926088300008410432[174] = 0;
   out_8926088300008410432[175] = 0;
   out_8926088300008410432[176] = 0;
   out_8926088300008410432[177] = 0;
   out_8926088300008410432[178] = 0;
   out_8926088300008410432[179] = 0;
   out_8926088300008410432[180] = 0;
   out_8926088300008410432[181] = 0;
   out_8926088300008410432[182] = 0;
   out_8926088300008410432[183] = 0;
   out_8926088300008410432[184] = 0;
   out_8926088300008410432[185] = 0;
   out_8926088300008410432[186] = 0;
   out_8926088300008410432[187] = 0;
   out_8926088300008410432[188] = 0;
   out_8926088300008410432[189] = 0;
   out_8926088300008410432[190] = 1;
   out_8926088300008410432[191] = 0;
   out_8926088300008410432[192] = 0;
   out_8926088300008410432[193] = 0;
   out_8926088300008410432[194] = 0;
   out_8926088300008410432[195] = 0;
   out_8926088300008410432[196] = 0;
   out_8926088300008410432[197] = 0;
   out_8926088300008410432[198] = 0;
   out_8926088300008410432[199] = 0;
   out_8926088300008410432[200] = 0;
   out_8926088300008410432[201] = 0;
   out_8926088300008410432[202] = 0;
   out_8926088300008410432[203] = 0;
   out_8926088300008410432[204] = 0;
   out_8926088300008410432[205] = 0;
   out_8926088300008410432[206] = 0;
   out_8926088300008410432[207] = 0;
   out_8926088300008410432[208] = 0;
   out_8926088300008410432[209] = 1;
   out_8926088300008410432[210] = 0;
   out_8926088300008410432[211] = 0;
   out_8926088300008410432[212] = 0;
   out_8926088300008410432[213] = 0;
   out_8926088300008410432[214] = 0;
   out_8926088300008410432[215] = 0;
   out_8926088300008410432[216] = 0;
   out_8926088300008410432[217] = 0;
   out_8926088300008410432[218] = 0;
   out_8926088300008410432[219] = 0;
   out_8926088300008410432[220] = 0;
   out_8926088300008410432[221] = 0;
   out_8926088300008410432[222] = 0;
   out_8926088300008410432[223] = 0;
   out_8926088300008410432[224] = 0;
   out_8926088300008410432[225] = 0;
   out_8926088300008410432[226] = 0;
   out_8926088300008410432[227] = 0;
   out_8926088300008410432[228] = 1;
   out_8926088300008410432[229] = 0;
   out_8926088300008410432[230] = 0;
   out_8926088300008410432[231] = 0;
   out_8926088300008410432[232] = 0;
   out_8926088300008410432[233] = 0;
   out_8926088300008410432[234] = 0;
   out_8926088300008410432[235] = 0;
   out_8926088300008410432[236] = 0;
   out_8926088300008410432[237] = 0;
   out_8926088300008410432[238] = 0;
   out_8926088300008410432[239] = 0;
   out_8926088300008410432[240] = 0;
   out_8926088300008410432[241] = 0;
   out_8926088300008410432[242] = 0;
   out_8926088300008410432[243] = 0;
   out_8926088300008410432[244] = 0;
   out_8926088300008410432[245] = 0;
   out_8926088300008410432[246] = 0;
   out_8926088300008410432[247] = 1;
   out_8926088300008410432[248] = 0;
   out_8926088300008410432[249] = 0;
   out_8926088300008410432[250] = 0;
   out_8926088300008410432[251] = 0;
   out_8926088300008410432[252] = 0;
   out_8926088300008410432[253] = 0;
   out_8926088300008410432[254] = 0;
   out_8926088300008410432[255] = 0;
   out_8926088300008410432[256] = 0;
   out_8926088300008410432[257] = 0;
   out_8926088300008410432[258] = 0;
   out_8926088300008410432[259] = 0;
   out_8926088300008410432[260] = 0;
   out_8926088300008410432[261] = 0;
   out_8926088300008410432[262] = 0;
   out_8926088300008410432[263] = 0;
   out_8926088300008410432[264] = 0;
   out_8926088300008410432[265] = 0;
   out_8926088300008410432[266] = 1;
   out_8926088300008410432[267] = 0;
   out_8926088300008410432[268] = 0;
   out_8926088300008410432[269] = 0;
   out_8926088300008410432[270] = 0;
   out_8926088300008410432[271] = 0;
   out_8926088300008410432[272] = 0;
   out_8926088300008410432[273] = 0;
   out_8926088300008410432[274] = 0;
   out_8926088300008410432[275] = 0;
   out_8926088300008410432[276] = 0;
   out_8926088300008410432[277] = 0;
   out_8926088300008410432[278] = 0;
   out_8926088300008410432[279] = 0;
   out_8926088300008410432[280] = 0;
   out_8926088300008410432[281] = 0;
   out_8926088300008410432[282] = 0;
   out_8926088300008410432[283] = 0;
   out_8926088300008410432[284] = 0;
   out_8926088300008410432[285] = 1;
   out_8926088300008410432[286] = 0;
   out_8926088300008410432[287] = 0;
   out_8926088300008410432[288] = 0;
   out_8926088300008410432[289] = 0;
   out_8926088300008410432[290] = 0;
   out_8926088300008410432[291] = 0;
   out_8926088300008410432[292] = 0;
   out_8926088300008410432[293] = 0;
   out_8926088300008410432[294] = 0;
   out_8926088300008410432[295] = 0;
   out_8926088300008410432[296] = 0;
   out_8926088300008410432[297] = 0;
   out_8926088300008410432[298] = 0;
   out_8926088300008410432[299] = 0;
   out_8926088300008410432[300] = 0;
   out_8926088300008410432[301] = 0;
   out_8926088300008410432[302] = 0;
   out_8926088300008410432[303] = 0;
   out_8926088300008410432[304] = 1;
   out_8926088300008410432[305] = 0;
   out_8926088300008410432[306] = 0;
   out_8926088300008410432[307] = 0;
   out_8926088300008410432[308] = 0;
   out_8926088300008410432[309] = 0;
   out_8926088300008410432[310] = 0;
   out_8926088300008410432[311] = 0;
   out_8926088300008410432[312] = 0;
   out_8926088300008410432[313] = 0;
   out_8926088300008410432[314] = 0;
   out_8926088300008410432[315] = 0;
   out_8926088300008410432[316] = 0;
   out_8926088300008410432[317] = 0;
   out_8926088300008410432[318] = 0;
   out_8926088300008410432[319] = 0;
   out_8926088300008410432[320] = 0;
   out_8926088300008410432[321] = 0;
   out_8926088300008410432[322] = 0;
   out_8926088300008410432[323] = 1;
}
void h_4(double *state, double *unused, double *out_439005716197027433) {
   out_439005716197027433[0] = state[6] + state[9];
   out_439005716197027433[1] = state[7] + state[10];
   out_439005716197027433[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_6358336940791637735) {
   out_6358336940791637735[0] = 0;
   out_6358336940791637735[1] = 0;
   out_6358336940791637735[2] = 0;
   out_6358336940791637735[3] = 0;
   out_6358336940791637735[4] = 0;
   out_6358336940791637735[5] = 0;
   out_6358336940791637735[6] = 1;
   out_6358336940791637735[7] = 0;
   out_6358336940791637735[8] = 0;
   out_6358336940791637735[9] = 1;
   out_6358336940791637735[10] = 0;
   out_6358336940791637735[11] = 0;
   out_6358336940791637735[12] = 0;
   out_6358336940791637735[13] = 0;
   out_6358336940791637735[14] = 0;
   out_6358336940791637735[15] = 0;
   out_6358336940791637735[16] = 0;
   out_6358336940791637735[17] = 0;
   out_6358336940791637735[18] = 0;
   out_6358336940791637735[19] = 0;
   out_6358336940791637735[20] = 0;
   out_6358336940791637735[21] = 0;
   out_6358336940791637735[22] = 0;
   out_6358336940791637735[23] = 0;
   out_6358336940791637735[24] = 0;
   out_6358336940791637735[25] = 1;
   out_6358336940791637735[26] = 0;
   out_6358336940791637735[27] = 0;
   out_6358336940791637735[28] = 1;
   out_6358336940791637735[29] = 0;
   out_6358336940791637735[30] = 0;
   out_6358336940791637735[31] = 0;
   out_6358336940791637735[32] = 0;
   out_6358336940791637735[33] = 0;
   out_6358336940791637735[34] = 0;
   out_6358336940791637735[35] = 0;
   out_6358336940791637735[36] = 0;
   out_6358336940791637735[37] = 0;
   out_6358336940791637735[38] = 0;
   out_6358336940791637735[39] = 0;
   out_6358336940791637735[40] = 0;
   out_6358336940791637735[41] = 0;
   out_6358336940791637735[42] = 0;
   out_6358336940791637735[43] = 0;
   out_6358336940791637735[44] = 1;
   out_6358336940791637735[45] = 0;
   out_6358336940791637735[46] = 0;
   out_6358336940791637735[47] = 1;
   out_6358336940791637735[48] = 0;
   out_6358336940791637735[49] = 0;
   out_6358336940791637735[50] = 0;
   out_6358336940791637735[51] = 0;
   out_6358336940791637735[52] = 0;
   out_6358336940791637735[53] = 0;
}
void h_10(double *state, double *unused, double *out_7231930289041195534) {
   out_7231930289041195534[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_7231930289041195534[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_7231930289041195534[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_584809807697225583) {
   out_584809807697225583[0] = 0;
   out_584809807697225583[1] = 9.8100000000000005*cos(state[1]);
   out_584809807697225583[2] = 0;
   out_584809807697225583[3] = 0;
   out_584809807697225583[4] = -state[8];
   out_584809807697225583[5] = state[7];
   out_584809807697225583[6] = 0;
   out_584809807697225583[7] = state[5];
   out_584809807697225583[8] = -state[4];
   out_584809807697225583[9] = 0;
   out_584809807697225583[10] = 0;
   out_584809807697225583[11] = 0;
   out_584809807697225583[12] = 1;
   out_584809807697225583[13] = 0;
   out_584809807697225583[14] = 0;
   out_584809807697225583[15] = 1;
   out_584809807697225583[16] = 0;
   out_584809807697225583[17] = 0;
   out_584809807697225583[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_584809807697225583[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_584809807697225583[20] = 0;
   out_584809807697225583[21] = state[8];
   out_584809807697225583[22] = 0;
   out_584809807697225583[23] = -state[6];
   out_584809807697225583[24] = -state[5];
   out_584809807697225583[25] = 0;
   out_584809807697225583[26] = state[3];
   out_584809807697225583[27] = 0;
   out_584809807697225583[28] = 0;
   out_584809807697225583[29] = 0;
   out_584809807697225583[30] = 0;
   out_584809807697225583[31] = 1;
   out_584809807697225583[32] = 0;
   out_584809807697225583[33] = 0;
   out_584809807697225583[34] = 1;
   out_584809807697225583[35] = 0;
   out_584809807697225583[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_584809807697225583[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_584809807697225583[38] = 0;
   out_584809807697225583[39] = -state[7];
   out_584809807697225583[40] = state[6];
   out_584809807697225583[41] = 0;
   out_584809807697225583[42] = state[4];
   out_584809807697225583[43] = -state[3];
   out_584809807697225583[44] = 0;
   out_584809807697225583[45] = 0;
   out_584809807697225583[46] = 0;
   out_584809807697225583[47] = 0;
   out_584809807697225583[48] = 0;
   out_584809807697225583[49] = 0;
   out_584809807697225583[50] = 1;
   out_584809807697225583[51] = 0;
   out_584809807697225583[52] = 0;
   out_584809807697225583[53] = 1;
}
void h_13(double *state, double *unused, double *out_6287159899549881063) {
   out_6287159899549881063[0] = state[3];
   out_6287159899549881063[1] = state[4];
   out_6287159899549881063[2] = state[5];
}
void H_13(double *state, double *unused, double *out_3146063115459304934) {
   out_3146063115459304934[0] = 0;
   out_3146063115459304934[1] = 0;
   out_3146063115459304934[2] = 0;
   out_3146063115459304934[3] = 1;
   out_3146063115459304934[4] = 0;
   out_3146063115459304934[5] = 0;
   out_3146063115459304934[6] = 0;
   out_3146063115459304934[7] = 0;
   out_3146063115459304934[8] = 0;
   out_3146063115459304934[9] = 0;
   out_3146063115459304934[10] = 0;
   out_3146063115459304934[11] = 0;
   out_3146063115459304934[12] = 0;
   out_3146063115459304934[13] = 0;
   out_3146063115459304934[14] = 0;
   out_3146063115459304934[15] = 0;
   out_3146063115459304934[16] = 0;
   out_3146063115459304934[17] = 0;
   out_3146063115459304934[18] = 0;
   out_3146063115459304934[19] = 0;
   out_3146063115459304934[20] = 0;
   out_3146063115459304934[21] = 0;
   out_3146063115459304934[22] = 1;
   out_3146063115459304934[23] = 0;
   out_3146063115459304934[24] = 0;
   out_3146063115459304934[25] = 0;
   out_3146063115459304934[26] = 0;
   out_3146063115459304934[27] = 0;
   out_3146063115459304934[28] = 0;
   out_3146063115459304934[29] = 0;
   out_3146063115459304934[30] = 0;
   out_3146063115459304934[31] = 0;
   out_3146063115459304934[32] = 0;
   out_3146063115459304934[33] = 0;
   out_3146063115459304934[34] = 0;
   out_3146063115459304934[35] = 0;
   out_3146063115459304934[36] = 0;
   out_3146063115459304934[37] = 0;
   out_3146063115459304934[38] = 0;
   out_3146063115459304934[39] = 0;
   out_3146063115459304934[40] = 0;
   out_3146063115459304934[41] = 1;
   out_3146063115459304934[42] = 0;
   out_3146063115459304934[43] = 0;
   out_3146063115459304934[44] = 0;
   out_3146063115459304934[45] = 0;
   out_3146063115459304934[46] = 0;
   out_3146063115459304934[47] = 0;
   out_3146063115459304934[48] = 0;
   out_3146063115459304934[49] = 0;
   out_3146063115459304934[50] = 0;
   out_3146063115459304934[51] = 0;
   out_3146063115459304934[52] = 0;
   out_3146063115459304934[53] = 0;
}
void h_14(double *state, double *unused, double *out_8265255736014954242) {
   out_8265255736014954242[0] = state[6];
   out_8265255736014954242[1] = state[7];
   out_8265255736014954242[2] = state[8];
}
void H_14(double *state, double *unused, double *out_2395096084452153206) {
   out_2395096084452153206[0] = 0;
   out_2395096084452153206[1] = 0;
   out_2395096084452153206[2] = 0;
   out_2395096084452153206[3] = 0;
   out_2395096084452153206[4] = 0;
   out_2395096084452153206[5] = 0;
   out_2395096084452153206[6] = 1;
   out_2395096084452153206[7] = 0;
   out_2395096084452153206[8] = 0;
   out_2395096084452153206[9] = 0;
   out_2395096084452153206[10] = 0;
   out_2395096084452153206[11] = 0;
   out_2395096084452153206[12] = 0;
   out_2395096084452153206[13] = 0;
   out_2395096084452153206[14] = 0;
   out_2395096084452153206[15] = 0;
   out_2395096084452153206[16] = 0;
   out_2395096084452153206[17] = 0;
   out_2395096084452153206[18] = 0;
   out_2395096084452153206[19] = 0;
   out_2395096084452153206[20] = 0;
   out_2395096084452153206[21] = 0;
   out_2395096084452153206[22] = 0;
   out_2395096084452153206[23] = 0;
   out_2395096084452153206[24] = 0;
   out_2395096084452153206[25] = 1;
   out_2395096084452153206[26] = 0;
   out_2395096084452153206[27] = 0;
   out_2395096084452153206[28] = 0;
   out_2395096084452153206[29] = 0;
   out_2395096084452153206[30] = 0;
   out_2395096084452153206[31] = 0;
   out_2395096084452153206[32] = 0;
   out_2395096084452153206[33] = 0;
   out_2395096084452153206[34] = 0;
   out_2395096084452153206[35] = 0;
   out_2395096084452153206[36] = 0;
   out_2395096084452153206[37] = 0;
   out_2395096084452153206[38] = 0;
   out_2395096084452153206[39] = 0;
   out_2395096084452153206[40] = 0;
   out_2395096084452153206[41] = 0;
   out_2395096084452153206[42] = 0;
   out_2395096084452153206[43] = 0;
   out_2395096084452153206[44] = 1;
   out_2395096084452153206[45] = 0;
   out_2395096084452153206[46] = 0;
   out_2395096084452153206[47] = 0;
   out_2395096084452153206[48] = 0;
   out_2395096084452153206[49] = 0;
   out_2395096084452153206[50] = 0;
   out_2395096084452153206[51] = 0;
   out_2395096084452153206[52] = 0;
   out_2395096084452153206[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_7790108905973441094) {
  err_fun(nom_x, delta_x, out_7790108905973441094);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_3044307321253503213) {
  inv_err_fun(nom_x, true_x, out_3044307321253503213);
}
void pose_H_mod_fun(double *state, double *out_2507391073749515951) {
  H_mod_fun(state, out_2507391073749515951);
}
void pose_f_fun(double *state, double dt, double *out_8106374632162380060) {
  f_fun(state,  dt, out_8106374632162380060);
}
void pose_F_fun(double *state, double dt, double *out_8926088300008410432) {
  F_fun(state,  dt, out_8926088300008410432);
}
void pose_h_4(double *state, double *unused, double *out_439005716197027433) {
  h_4(state, unused, out_439005716197027433);
}
void pose_H_4(double *state, double *unused, double *out_6358336940791637735) {
  H_4(state, unused, out_6358336940791637735);
}
void pose_h_10(double *state, double *unused, double *out_7231930289041195534) {
  h_10(state, unused, out_7231930289041195534);
}
void pose_H_10(double *state, double *unused, double *out_584809807697225583) {
  H_10(state, unused, out_584809807697225583);
}
void pose_h_13(double *state, double *unused, double *out_6287159899549881063) {
  h_13(state, unused, out_6287159899549881063);
}
void pose_H_13(double *state, double *unused, double *out_3146063115459304934) {
  H_13(state, unused, out_3146063115459304934);
}
void pose_h_14(double *state, double *unused, double *out_8265255736014954242) {
  h_14(state, unused, out_8265255736014954242);
}
void pose_H_14(double *state, double *unused, double *out_2395096084452153206) {
  H_14(state, unused, out_2395096084452153206);
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
