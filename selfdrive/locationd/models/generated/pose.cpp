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
void err_fun(double *nom_x, double *delta_x, double *out_529622895560387506) {
   out_529622895560387506[0] = delta_x[0] + nom_x[0];
   out_529622895560387506[1] = delta_x[1] + nom_x[1];
   out_529622895560387506[2] = delta_x[2] + nom_x[2];
   out_529622895560387506[3] = delta_x[3] + nom_x[3];
   out_529622895560387506[4] = delta_x[4] + nom_x[4];
   out_529622895560387506[5] = delta_x[5] + nom_x[5];
   out_529622895560387506[6] = delta_x[6] + nom_x[6];
   out_529622895560387506[7] = delta_x[7] + nom_x[7];
   out_529622895560387506[8] = delta_x[8] + nom_x[8];
   out_529622895560387506[9] = delta_x[9] + nom_x[9];
   out_529622895560387506[10] = delta_x[10] + nom_x[10];
   out_529622895560387506[11] = delta_x[11] + nom_x[11];
   out_529622895560387506[12] = delta_x[12] + nom_x[12];
   out_529622895560387506[13] = delta_x[13] + nom_x[13];
   out_529622895560387506[14] = delta_x[14] + nom_x[14];
   out_529622895560387506[15] = delta_x[15] + nom_x[15];
   out_529622895560387506[16] = delta_x[16] + nom_x[16];
   out_529622895560387506[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_5635522996089764755) {
   out_5635522996089764755[0] = -nom_x[0] + true_x[0];
   out_5635522996089764755[1] = -nom_x[1] + true_x[1];
   out_5635522996089764755[2] = -nom_x[2] + true_x[2];
   out_5635522996089764755[3] = -nom_x[3] + true_x[3];
   out_5635522996089764755[4] = -nom_x[4] + true_x[4];
   out_5635522996089764755[5] = -nom_x[5] + true_x[5];
   out_5635522996089764755[6] = -nom_x[6] + true_x[6];
   out_5635522996089764755[7] = -nom_x[7] + true_x[7];
   out_5635522996089764755[8] = -nom_x[8] + true_x[8];
   out_5635522996089764755[9] = -nom_x[9] + true_x[9];
   out_5635522996089764755[10] = -nom_x[10] + true_x[10];
   out_5635522996089764755[11] = -nom_x[11] + true_x[11];
   out_5635522996089764755[12] = -nom_x[12] + true_x[12];
   out_5635522996089764755[13] = -nom_x[13] + true_x[13];
   out_5635522996089764755[14] = -nom_x[14] + true_x[14];
   out_5635522996089764755[15] = -nom_x[15] + true_x[15];
   out_5635522996089764755[16] = -nom_x[16] + true_x[16];
   out_5635522996089764755[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_3534116985585266661) {
   out_3534116985585266661[0] = 1.0;
   out_3534116985585266661[1] = 0.0;
   out_3534116985585266661[2] = 0.0;
   out_3534116985585266661[3] = 0.0;
   out_3534116985585266661[4] = 0.0;
   out_3534116985585266661[5] = 0.0;
   out_3534116985585266661[6] = 0.0;
   out_3534116985585266661[7] = 0.0;
   out_3534116985585266661[8] = 0.0;
   out_3534116985585266661[9] = 0.0;
   out_3534116985585266661[10] = 0.0;
   out_3534116985585266661[11] = 0.0;
   out_3534116985585266661[12] = 0.0;
   out_3534116985585266661[13] = 0.0;
   out_3534116985585266661[14] = 0.0;
   out_3534116985585266661[15] = 0.0;
   out_3534116985585266661[16] = 0.0;
   out_3534116985585266661[17] = 0.0;
   out_3534116985585266661[18] = 0.0;
   out_3534116985585266661[19] = 1.0;
   out_3534116985585266661[20] = 0.0;
   out_3534116985585266661[21] = 0.0;
   out_3534116985585266661[22] = 0.0;
   out_3534116985585266661[23] = 0.0;
   out_3534116985585266661[24] = 0.0;
   out_3534116985585266661[25] = 0.0;
   out_3534116985585266661[26] = 0.0;
   out_3534116985585266661[27] = 0.0;
   out_3534116985585266661[28] = 0.0;
   out_3534116985585266661[29] = 0.0;
   out_3534116985585266661[30] = 0.0;
   out_3534116985585266661[31] = 0.0;
   out_3534116985585266661[32] = 0.0;
   out_3534116985585266661[33] = 0.0;
   out_3534116985585266661[34] = 0.0;
   out_3534116985585266661[35] = 0.0;
   out_3534116985585266661[36] = 0.0;
   out_3534116985585266661[37] = 0.0;
   out_3534116985585266661[38] = 1.0;
   out_3534116985585266661[39] = 0.0;
   out_3534116985585266661[40] = 0.0;
   out_3534116985585266661[41] = 0.0;
   out_3534116985585266661[42] = 0.0;
   out_3534116985585266661[43] = 0.0;
   out_3534116985585266661[44] = 0.0;
   out_3534116985585266661[45] = 0.0;
   out_3534116985585266661[46] = 0.0;
   out_3534116985585266661[47] = 0.0;
   out_3534116985585266661[48] = 0.0;
   out_3534116985585266661[49] = 0.0;
   out_3534116985585266661[50] = 0.0;
   out_3534116985585266661[51] = 0.0;
   out_3534116985585266661[52] = 0.0;
   out_3534116985585266661[53] = 0.0;
   out_3534116985585266661[54] = 0.0;
   out_3534116985585266661[55] = 0.0;
   out_3534116985585266661[56] = 0.0;
   out_3534116985585266661[57] = 1.0;
   out_3534116985585266661[58] = 0.0;
   out_3534116985585266661[59] = 0.0;
   out_3534116985585266661[60] = 0.0;
   out_3534116985585266661[61] = 0.0;
   out_3534116985585266661[62] = 0.0;
   out_3534116985585266661[63] = 0.0;
   out_3534116985585266661[64] = 0.0;
   out_3534116985585266661[65] = 0.0;
   out_3534116985585266661[66] = 0.0;
   out_3534116985585266661[67] = 0.0;
   out_3534116985585266661[68] = 0.0;
   out_3534116985585266661[69] = 0.0;
   out_3534116985585266661[70] = 0.0;
   out_3534116985585266661[71] = 0.0;
   out_3534116985585266661[72] = 0.0;
   out_3534116985585266661[73] = 0.0;
   out_3534116985585266661[74] = 0.0;
   out_3534116985585266661[75] = 0.0;
   out_3534116985585266661[76] = 1.0;
   out_3534116985585266661[77] = 0.0;
   out_3534116985585266661[78] = 0.0;
   out_3534116985585266661[79] = 0.0;
   out_3534116985585266661[80] = 0.0;
   out_3534116985585266661[81] = 0.0;
   out_3534116985585266661[82] = 0.0;
   out_3534116985585266661[83] = 0.0;
   out_3534116985585266661[84] = 0.0;
   out_3534116985585266661[85] = 0.0;
   out_3534116985585266661[86] = 0.0;
   out_3534116985585266661[87] = 0.0;
   out_3534116985585266661[88] = 0.0;
   out_3534116985585266661[89] = 0.0;
   out_3534116985585266661[90] = 0.0;
   out_3534116985585266661[91] = 0.0;
   out_3534116985585266661[92] = 0.0;
   out_3534116985585266661[93] = 0.0;
   out_3534116985585266661[94] = 0.0;
   out_3534116985585266661[95] = 1.0;
   out_3534116985585266661[96] = 0.0;
   out_3534116985585266661[97] = 0.0;
   out_3534116985585266661[98] = 0.0;
   out_3534116985585266661[99] = 0.0;
   out_3534116985585266661[100] = 0.0;
   out_3534116985585266661[101] = 0.0;
   out_3534116985585266661[102] = 0.0;
   out_3534116985585266661[103] = 0.0;
   out_3534116985585266661[104] = 0.0;
   out_3534116985585266661[105] = 0.0;
   out_3534116985585266661[106] = 0.0;
   out_3534116985585266661[107] = 0.0;
   out_3534116985585266661[108] = 0.0;
   out_3534116985585266661[109] = 0.0;
   out_3534116985585266661[110] = 0.0;
   out_3534116985585266661[111] = 0.0;
   out_3534116985585266661[112] = 0.0;
   out_3534116985585266661[113] = 0.0;
   out_3534116985585266661[114] = 1.0;
   out_3534116985585266661[115] = 0.0;
   out_3534116985585266661[116] = 0.0;
   out_3534116985585266661[117] = 0.0;
   out_3534116985585266661[118] = 0.0;
   out_3534116985585266661[119] = 0.0;
   out_3534116985585266661[120] = 0.0;
   out_3534116985585266661[121] = 0.0;
   out_3534116985585266661[122] = 0.0;
   out_3534116985585266661[123] = 0.0;
   out_3534116985585266661[124] = 0.0;
   out_3534116985585266661[125] = 0.0;
   out_3534116985585266661[126] = 0.0;
   out_3534116985585266661[127] = 0.0;
   out_3534116985585266661[128] = 0.0;
   out_3534116985585266661[129] = 0.0;
   out_3534116985585266661[130] = 0.0;
   out_3534116985585266661[131] = 0.0;
   out_3534116985585266661[132] = 0.0;
   out_3534116985585266661[133] = 1.0;
   out_3534116985585266661[134] = 0.0;
   out_3534116985585266661[135] = 0.0;
   out_3534116985585266661[136] = 0.0;
   out_3534116985585266661[137] = 0.0;
   out_3534116985585266661[138] = 0.0;
   out_3534116985585266661[139] = 0.0;
   out_3534116985585266661[140] = 0.0;
   out_3534116985585266661[141] = 0.0;
   out_3534116985585266661[142] = 0.0;
   out_3534116985585266661[143] = 0.0;
   out_3534116985585266661[144] = 0.0;
   out_3534116985585266661[145] = 0.0;
   out_3534116985585266661[146] = 0.0;
   out_3534116985585266661[147] = 0.0;
   out_3534116985585266661[148] = 0.0;
   out_3534116985585266661[149] = 0.0;
   out_3534116985585266661[150] = 0.0;
   out_3534116985585266661[151] = 0.0;
   out_3534116985585266661[152] = 1.0;
   out_3534116985585266661[153] = 0.0;
   out_3534116985585266661[154] = 0.0;
   out_3534116985585266661[155] = 0.0;
   out_3534116985585266661[156] = 0.0;
   out_3534116985585266661[157] = 0.0;
   out_3534116985585266661[158] = 0.0;
   out_3534116985585266661[159] = 0.0;
   out_3534116985585266661[160] = 0.0;
   out_3534116985585266661[161] = 0.0;
   out_3534116985585266661[162] = 0.0;
   out_3534116985585266661[163] = 0.0;
   out_3534116985585266661[164] = 0.0;
   out_3534116985585266661[165] = 0.0;
   out_3534116985585266661[166] = 0.0;
   out_3534116985585266661[167] = 0.0;
   out_3534116985585266661[168] = 0.0;
   out_3534116985585266661[169] = 0.0;
   out_3534116985585266661[170] = 0.0;
   out_3534116985585266661[171] = 1.0;
   out_3534116985585266661[172] = 0.0;
   out_3534116985585266661[173] = 0.0;
   out_3534116985585266661[174] = 0.0;
   out_3534116985585266661[175] = 0.0;
   out_3534116985585266661[176] = 0.0;
   out_3534116985585266661[177] = 0.0;
   out_3534116985585266661[178] = 0.0;
   out_3534116985585266661[179] = 0.0;
   out_3534116985585266661[180] = 0.0;
   out_3534116985585266661[181] = 0.0;
   out_3534116985585266661[182] = 0.0;
   out_3534116985585266661[183] = 0.0;
   out_3534116985585266661[184] = 0.0;
   out_3534116985585266661[185] = 0.0;
   out_3534116985585266661[186] = 0.0;
   out_3534116985585266661[187] = 0.0;
   out_3534116985585266661[188] = 0.0;
   out_3534116985585266661[189] = 0.0;
   out_3534116985585266661[190] = 1.0;
   out_3534116985585266661[191] = 0.0;
   out_3534116985585266661[192] = 0.0;
   out_3534116985585266661[193] = 0.0;
   out_3534116985585266661[194] = 0.0;
   out_3534116985585266661[195] = 0.0;
   out_3534116985585266661[196] = 0.0;
   out_3534116985585266661[197] = 0.0;
   out_3534116985585266661[198] = 0.0;
   out_3534116985585266661[199] = 0.0;
   out_3534116985585266661[200] = 0.0;
   out_3534116985585266661[201] = 0.0;
   out_3534116985585266661[202] = 0.0;
   out_3534116985585266661[203] = 0.0;
   out_3534116985585266661[204] = 0.0;
   out_3534116985585266661[205] = 0.0;
   out_3534116985585266661[206] = 0.0;
   out_3534116985585266661[207] = 0.0;
   out_3534116985585266661[208] = 0.0;
   out_3534116985585266661[209] = 1.0;
   out_3534116985585266661[210] = 0.0;
   out_3534116985585266661[211] = 0.0;
   out_3534116985585266661[212] = 0.0;
   out_3534116985585266661[213] = 0.0;
   out_3534116985585266661[214] = 0.0;
   out_3534116985585266661[215] = 0.0;
   out_3534116985585266661[216] = 0.0;
   out_3534116985585266661[217] = 0.0;
   out_3534116985585266661[218] = 0.0;
   out_3534116985585266661[219] = 0.0;
   out_3534116985585266661[220] = 0.0;
   out_3534116985585266661[221] = 0.0;
   out_3534116985585266661[222] = 0.0;
   out_3534116985585266661[223] = 0.0;
   out_3534116985585266661[224] = 0.0;
   out_3534116985585266661[225] = 0.0;
   out_3534116985585266661[226] = 0.0;
   out_3534116985585266661[227] = 0.0;
   out_3534116985585266661[228] = 1.0;
   out_3534116985585266661[229] = 0.0;
   out_3534116985585266661[230] = 0.0;
   out_3534116985585266661[231] = 0.0;
   out_3534116985585266661[232] = 0.0;
   out_3534116985585266661[233] = 0.0;
   out_3534116985585266661[234] = 0.0;
   out_3534116985585266661[235] = 0.0;
   out_3534116985585266661[236] = 0.0;
   out_3534116985585266661[237] = 0.0;
   out_3534116985585266661[238] = 0.0;
   out_3534116985585266661[239] = 0.0;
   out_3534116985585266661[240] = 0.0;
   out_3534116985585266661[241] = 0.0;
   out_3534116985585266661[242] = 0.0;
   out_3534116985585266661[243] = 0.0;
   out_3534116985585266661[244] = 0.0;
   out_3534116985585266661[245] = 0.0;
   out_3534116985585266661[246] = 0.0;
   out_3534116985585266661[247] = 1.0;
   out_3534116985585266661[248] = 0.0;
   out_3534116985585266661[249] = 0.0;
   out_3534116985585266661[250] = 0.0;
   out_3534116985585266661[251] = 0.0;
   out_3534116985585266661[252] = 0.0;
   out_3534116985585266661[253] = 0.0;
   out_3534116985585266661[254] = 0.0;
   out_3534116985585266661[255] = 0.0;
   out_3534116985585266661[256] = 0.0;
   out_3534116985585266661[257] = 0.0;
   out_3534116985585266661[258] = 0.0;
   out_3534116985585266661[259] = 0.0;
   out_3534116985585266661[260] = 0.0;
   out_3534116985585266661[261] = 0.0;
   out_3534116985585266661[262] = 0.0;
   out_3534116985585266661[263] = 0.0;
   out_3534116985585266661[264] = 0.0;
   out_3534116985585266661[265] = 0.0;
   out_3534116985585266661[266] = 1.0;
   out_3534116985585266661[267] = 0.0;
   out_3534116985585266661[268] = 0.0;
   out_3534116985585266661[269] = 0.0;
   out_3534116985585266661[270] = 0.0;
   out_3534116985585266661[271] = 0.0;
   out_3534116985585266661[272] = 0.0;
   out_3534116985585266661[273] = 0.0;
   out_3534116985585266661[274] = 0.0;
   out_3534116985585266661[275] = 0.0;
   out_3534116985585266661[276] = 0.0;
   out_3534116985585266661[277] = 0.0;
   out_3534116985585266661[278] = 0.0;
   out_3534116985585266661[279] = 0.0;
   out_3534116985585266661[280] = 0.0;
   out_3534116985585266661[281] = 0.0;
   out_3534116985585266661[282] = 0.0;
   out_3534116985585266661[283] = 0.0;
   out_3534116985585266661[284] = 0.0;
   out_3534116985585266661[285] = 1.0;
   out_3534116985585266661[286] = 0.0;
   out_3534116985585266661[287] = 0.0;
   out_3534116985585266661[288] = 0.0;
   out_3534116985585266661[289] = 0.0;
   out_3534116985585266661[290] = 0.0;
   out_3534116985585266661[291] = 0.0;
   out_3534116985585266661[292] = 0.0;
   out_3534116985585266661[293] = 0.0;
   out_3534116985585266661[294] = 0.0;
   out_3534116985585266661[295] = 0.0;
   out_3534116985585266661[296] = 0.0;
   out_3534116985585266661[297] = 0.0;
   out_3534116985585266661[298] = 0.0;
   out_3534116985585266661[299] = 0.0;
   out_3534116985585266661[300] = 0.0;
   out_3534116985585266661[301] = 0.0;
   out_3534116985585266661[302] = 0.0;
   out_3534116985585266661[303] = 0.0;
   out_3534116985585266661[304] = 1.0;
   out_3534116985585266661[305] = 0.0;
   out_3534116985585266661[306] = 0.0;
   out_3534116985585266661[307] = 0.0;
   out_3534116985585266661[308] = 0.0;
   out_3534116985585266661[309] = 0.0;
   out_3534116985585266661[310] = 0.0;
   out_3534116985585266661[311] = 0.0;
   out_3534116985585266661[312] = 0.0;
   out_3534116985585266661[313] = 0.0;
   out_3534116985585266661[314] = 0.0;
   out_3534116985585266661[315] = 0.0;
   out_3534116985585266661[316] = 0.0;
   out_3534116985585266661[317] = 0.0;
   out_3534116985585266661[318] = 0.0;
   out_3534116985585266661[319] = 0.0;
   out_3534116985585266661[320] = 0.0;
   out_3534116985585266661[321] = 0.0;
   out_3534116985585266661[322] = 0.0;
   out_3534116985585266661[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_4412251706839144439) {
   out_4412251706839144439[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_4412251706839144439[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_4412251706839144439[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_4412251706839144439[3] = dt*state[12] + state[3];
   out_4412251706839144439[4] = dt*state[13] + state[4];
   out_4412251706839144439[5] = dt*state[14] + state[5];
   out_4412251706839144439[6] = state[6];
   out_4412251706839144439[7] = state[7];
   out_4412251706839144439[8] = state[8];
   out_4412251706839144439[9] = state[9];
   out_4412251706839144439[10] = state[10];
   out_4412251706839144439[11] = state[11];
   out_4412251706839144439[12] = state[12];
   out_4412251706839144439[13] = state[13];
   out_4412251706839144439[14] = state[14];
   out_4412251706839144439[15] = state[15];
   out_4412251706839144439[16] = state[16];
   out_4412251706839144439[17] = state[17];
}
void F_fun(double *state, double dt, double *out_1358445773394405128) {
   out_1358445773394405128[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1358445773394405128[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1358445773394405128[2] = 0;
   out_1358445773394405128[3] = 0;
   out_1358445773394405128[4] = 0;
   out_1358445773394405128[5] = 0;
   out_1358445773394405128[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1358445773394405128[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1358445773394405128[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1358445773394405128[9] = 0;
   out_1358445773394405128[10] = 0;
   out_1358445773394405128[11] = 0;
   out_1358445773394405128[12] = 0;
   out_1358445773394405128[13] = 0;
   out_1358445773394405128[14] = 0;
   out_1358445773394405128[15] = 0;
   out_1358445773394405128[16] = 0;
   out_1358445773394405128[17] = 0;
   out_1358445773394405128[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1358445773394405128[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1358445773394405128[20] = 0;
   out_1358445773394405128[21] = 0;
   out_1358445773394405128[22] = 0;
   out_1358445773394405128[23] = 0;
   out_1358445773394405128[24] = 0;
   out_1358445773394405128[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1358445773394405128[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1358445773394405128[27] = 0;
   out_1358445773394405128[28] = 0;
   out_1358445773394405128[29] = 0;
   out_1358445773394405128[30] = 0;
   out_1358445773394405128[31] = 0;
   out_1358445773394405128[32] = 0;
   out_1358445773394405128[33] = 0;
   out_1358445773394405128[34] = 0;
   out_1358445773394405128[35] = 0;
   out_1358445773394405128[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1358445773394405128[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1358445773394405128[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1358445773394405128[39] = 0;
   out_1358445773394405128[40] = 0;
   out_1358445773394405128[41] = 0;
   out_1358445773394405128[42] = 0;
   out_1358445773394405128[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1358445773394405128[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1358445773394405128[45] = 0;
   out_1358445773394405128[46] = 0;
   out_1358445773394405128[47] = 0;
   out_1358445773394405128[48] = 0;
   out_1358445773394405128[49] = 0;
   out_1358445773394405128[50] = 0;
   out_1358445773394405128[51] = 0;
   out_1358445773394405128[52] = 0;
   out_1358445773394405128[53] = 0;
   out_1358445773394405128[54] = 0;
   out_1358445773394405128[55] = 0;
   out_1358445773394405128[56] = 0;
   out_1358445773394405128[57] = 1;
   out_1358445773394405128[58] = 0;
   out_1358445773394405128[59] = 0;
   out_1358445773394405128[60] = 0;
   out_1358445773394405128[61] = 0;
   out_1358445773394405128[62] = 0;
   out_1358445773394405128[63] = 0;
   out_1358445773394405128[64] = 0;
   out_1358445773394405128[65] = 0;
   out_1358445773394405128[66] = dt;
   out_1358445773394405128[67] = 0;
   out_1358445773394405128[68] = 0;
   out_1358445773394405128[69] = 0;
   out_1358445773394405128[70] = 0;
   out_1358445773394405128[71] = 0;
   out_1358445773394405128[72] = 0;
   out_1358445773394405128[73] = 0;
   out_1358445773394405128[74] = 0;
   out_1358445773394405128[75] = 0;
   out_1358445773394405128[76] = 1;
   out_1358445773394405128[77] = 0;
   out_1358445773394405128[78] = 0;
   out_1358445773394405128[79] = 0;
   out_1358445773394405128[80] = 0;
   out_1358445773394405128[81] = 0;
   out_1358445773394405128[82] = 0;
   out_1358445773394405128[83] = 0;
   out_1358445773394405128[84] = 0;
   out_1358445773394405128[85] = dt;
   out_1358445773394405128[86] = 0;
   out_1358445773394405128[87] = 0;
   out_1358445773394405128[88] = 0;
   out_1358445773394405128[89] = 0;
   out_1358445773394405128[90] = 0;
   out_1358445773394405128[91] = 0;
   out_1358445773394405128[92] = 0;
   out_1358445773394405128[93] = 0;
   out_1358445773394405128[94] = 0;
   out_1358445773394405128[95] = 1;
   out_1358445773394405128[96] = 0;
   out_1358445773394405128[97] = 0;
   out_1358445773394405128[98] = 0;
   out_1358445773394405128[99] = 0;
   out_1358445773394405128[100] = 0;
   out_1358445773394405128[101] = 0;
   out_1358445773394405128[102] = 0;
   out_1358445773394405128[103] = 0;
   out_1358445773394405128[104] = dt;
   out_1358445773394405128[105] = 0;
   out_1358445773394405128[106] = 0;
   out_1358445773394405128[107] = 0;
   out_1358445773394405128[108] = 0;
   out_1358445773394405128[109] = 0;
   out_1358445773394405128[110] = 0;
   out_1358445773394405128[111] = 0;
   out_1358445773394405128[112] = 0;
   out_1358445773394405128[113] = 0;
   out_1358445773394405128[114] = 1;
   out_1358445773394405128[115] = 0;
   out_1358445773394405128[116] = 0;
   out_1358445773394405128[117] = 0;
   out_1358445773394405128[118] = 0;
   out_1358445773394405128[119] = 0;
   out_1358445773394405128[120] = 0;
   out_1358445773394405128[121] = 0;
   out_1358445773394405128[122] = 0;
   out_1358445773394405128[123] = 0;
   out_1358445773394405128[124] = 0;
   out_1358445773394405128[125] = 0;
   out_1358445773394405128[126] = 0;
   out_1358445773394405128[127] = 0;
   out_1358445773394405128[128] = 0;
   out_1358445773394405128[129] = 0;
   out_1358445773394405128[130] = 0;
   out_1358445773394405128[131] = 0;
   out_1358445773394405128[132] = 0;
   out_1358445773394405128[133] = 1;
   out_1358445773394405128[134] = 0;
   out_1358445773394405128[135] = 0;
   out_1358445773394405128[136] = 0;
   out_1358445773394405128[137] = 0;
   out_1358445773394405128[138] = 0;
   out_1358445773394405128[139] = 0;
   out_1358445773394405128[140] = 0;
   out_1358445773394405128[141] = 0;
   out_1358445773394405128[142] = 0;
   out_1358445773394405128[143] = 0;
   out_1358445773394405128[144] = 0;
   out_1358445773394405128[145] = 0;
   out_1358445773394405128[146] = 0;
   out_1358445773394405128[147] = 0;
   out_1358445773394405128[148] = 0;
   out_1358445773394405128[149] = 0;
   out_1358445773394405128[150] = 0;
   out_1358445773394405128[151] = 0;
   out_1358445773394405128[152] = 1;
   out_1358445773394405128[153] = 0;
   out_1358445773394405128[154] = 0;
   out_1358445773394405128[155] = 0;
   out_1358445773394405128[156] = 0;
   out_1358445773394405128[157] = 0;
   out_1358445773394405128[158] = 0;
   out_1358445773394405128[159] = 0;
   out_1358445773394405128[160] = 0;
   out_1358445773394405128[161] = 0;
   out_1358445773394405128[162] = 0;
   out_1358445773394405128[163] = 0;
   out_1358445773394405128[164] = 0;
   out_1358445773394405128[165] = 0;
   out_1358445773394405128[166] = 0;
   out_1358445773394405128[167] = 0;
   out_1358445773394405128[168] = 0;
   out_1358445773394405128[169] = 0;
   out_1358445773394405128[170] = 0;
   out_1358445773394405128[171] = 1;
   out_1358445773394405128[172] = 0;
   out_1358445773394405128[173] = 0;
   out_1358445773394405128[174] = 0;
   out_1358445773394405128[175] = 0;
   out_1358445773394405128[176] = 0;
   out_1358445773394405128[177] = 0;
   out_1358445773394405128[178] = 0;
   out_1358445773394405128[179] = 0;
   out_1358445773394405128[180] = 0;
   out_1358445773394405128[181] = 0;
   out_1358445773394405128[182] = 0;
   out_1358445773394405128[183] = 0;
   out_1358445773394405128[184] = 0;
   out_1358445773394405128[185] = 0;
   out_1358445773394405128[186] = 0;
   out_1358445773394405128[187] = 0;
   out_1358445773394405128[188] = 0;
   out_1358445773394405128[189] = 0;
   out_1358445773394405128[190] = 1;
   out_1358445773394405128[191] = 0;
   out_1358445773394405128[192] = 0;
   out_1358445773394405128[193] = 0;
   out_1358445773394405128[194] = 0;
   out_1358445773394405128[195] = 0;
   out_1358445773394405128[196] = 0;
   out_1358445773394405128[197] = 0;
   out_1358445773394405128[198] = 0;
   out_1358445773394405128[199] = 0;
   out_1358445773394405128[200] = 0;
   out_1358445773394405128[201] = 0;
   out_1358445773394405128[202] = 0;
   out_1358445773394405128[203] = 0;
   out_1358445773394405128[204] = 0;
   out_1358445773394405128[205] = 0;
   out_1358445773394405128[206] = 0;
   out_1358445773394405128[207] = 0;
   out_1358445773394405128[208] = 0;
   out_1358445773394405128[209] = 1;
   out_1358445773394405128[210] = 0;
   out_1358445773394405128[211] = 0;
   out_1358445773394405128[212] = 0;
   out_1358445773394405128[213] = 0;
   out_1358445773394405128[214] = 0;
   out_1358445773394405128[215] = 0;
   out_1358445773394405128[216] = 0;
   out_1358445773394405128[217] = 0;
   out_1358445773394405128[218] = 0;
   out_1358445773394405128[219] = 0;
   out_1358445773394405128[220] = 0;
   out_1358445773394405128[221] = 0;
   out_1358445773394405128[222] = 0;
   out_1358445773394405128[223] = 0;
   out_1358445773394405128[224] = 0;
   out_1358445773394405128[225] = 0;
   out_1358445773394405128[226] = 0;
   out_1358445773394405128[227] = 0;
   out_1358445773394405128[228] = 1;
   out_1358445773394405128[229] = 0;
   out_1358445773394405128[230] = 0;
   out_1358445773394405128[231] = 0;
   out_1358445773394405128[232] = 0;
   out_1358445773394405128[233] = 0;
   out_1358445773394405128[234] = 0;
   out_1358445773394405128[235] = 0;
   out_1358445773394405128[236] = 0;
   out_1358445773394405128[237] = 0;
   out_1358445773394405128[238] = 0;
   out_1358445773394405128[239] = 0;
   out_1358445773394405128[240] = 0;
   out_1358445773394405128[241] = 0;
   out_1358445773394405128[242] = 0;
   out_1358445773394405128[243] = 0;
   out_1358445773394405128[244] = 0;
   out_1358445773394405128[245] = 0;
   out_1358445773394405128[246] = 0;
   out_1358445773394405128[247] = 1;
   out_1358445773394405128[248] = 0;
   out_1358445773394405128[249] = 0;
   out_1358445773394405128[250] = 0;
   out_1358445773394405128[251] = 0;
   out_1358445773394405128[252] = 0;
   out_1358445773394405128[253] = 0;
   out_1358445773394405128[254] = 0;
   out_1358445773394405128[255] = 0;
   out_1358445773394405128[256] = 0;
   out_1358445773394405128[257] = 0;
   out_1358445773394405128[258] = 0;
   out_1358445773394405128[259] = 0;
   out_1358445773394405128[260] = 0;
   out_1358445773394405128[261] = 0;
   out_1358445773394405128[262] = 0;
   out_1358445773394405128[263] = 0;
   out_1358445773394405128[264] = 0;
   out_1358445773394405128[265] = 0;
   out_1358445773394405128[266] = 1;
   out_1358445773394405128[267] = 0;
   out_1358445773394405128[268] = 0;
   out_1358445773394405128[269] = 0;
   out_1358445773394405128[270] = 0;
   out_1358445773394405128[271] = 0;
   out_1358445773394405128[272] = 0;
   out_1358445773394405128[273] = 0;
   out_1358445773394405128[274] = 0;
   out_1358445773394405128[275] = 0;
   out_1358445773394405128[276] = 0;
   out_1358445773394405128[277] = 0;
   out_1358445773394405128[278] = 0;
   out_1358445773394405128[279] = 0;
   out_1358445773394405128[280] = 0;
   out_1358445773394405128[281] = 0;
   out_1358445773394405128[282] = 0;
   out_1358445773394405128[283] = 0;
   out_1358445773394405128[284] = 0;
   out_1358445773394405128[285] = 1;
   out_1358445773394405128[286] = 0;
   out_1358445773394405128[287] = 0;
   out_1358445773394405128[288] = 0;
   out_1358445773394405128[289] = 0;
   out_1358445773394405128[290] = 0;
   out_1358445773394405128[291] = 0;
   out_1358445773394405128[292] = 0;
   out_1358445773394405128[293] = 0;
   out_1358445773394405128[294] = 0;
   out_1358445773394405128[295] = 0;
   out_1358445773394405128[296] = 0;
   out_1358445773394405128[297] = 0;
   out_1358445773394405128[298] = 0;
   out_1358445773394405128[299] = 0;
   out_1358445773394405128[300] = 0;
   out_1358445773394405128[301] = 0;
   out_1358445773394405128[302] = 0;
   out_1358445773394405128[303] = 0;
   out_1358445773394405128[304] = 1;
   out_1358445773394405128[305] = 0;
   out_1358445773394405128[306] = 0;
   out_1358445773394405128[307] = 0;
   out_1358445773394405128[308] = 0;
   out_1358445773394405128[309] = 0;
   out_1358445773394405128[310] = 0;
   out_1358445773394405128[311] = 0;
   out_1358445773394405128[312] = 0;
   out_1358445773394405128[313] = 0;
   out_1358445773394405128[314] = 0;
   out_1358445773394405128[315] = 0;
   out_1358445773394405128[316] = 0;
   out_1358445773394405128[317] = 0;
   out_1358445773394405128[318] = 0;
   out_1358445773394405128[319] = 0;
   out_1358445773394405128[320] = 0;
   out_1358445773394405128[321] = 0;
   out_1358445773394405128[322] = 0;
   out_1358445773394405128[323] = 1;
}
void h_4(double *state, double *unused, double *out_5199898530632523440) {
   out_5199898530632523440[0] = state[6] + state[9];
   out_5199898530632523440[1] = state[7] + state[10];
   out_5199898530632523440[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_1714418259678969800) {
   out_1714418259678969800[0] = 0;
   out_1714418259678969800[1] = 0;
   out_1714418259678969800[2] = 0;
   out_1714418259678969800[3] = 0;
   out_1714418259678969800[4] = 0;
   out_1714418259678969800[5] = 0;
   out_1714418259678969800[6] = 1;
   out_1714418259678969800[7] = 0;
   out_1714418259678969800[8] = 0;
   out_1714418259678969800[9] = 1;
   out_1714418259678969800[10] = 0;
   out_1714418259678969800[11] = 0;
   out_1714418259678969800[12] = 0;
   out_1714418259678969800[13] = 0;
   out_1714418259678969800[14] = 0;
   out_1714418259678969800[15] = 0;
   out_1714418259678969800[16] = 0;
   out_1714418259678969800[17] = 0;
   out_1714418259678969800[18] = 0;
   out_1714418259678969800[19] = 0;
   out_1714418259678969800[20] = 0;
   out_1714418259678969800[21] = 0;
   out_1714418259678969800[22] = 0;
   out_1714418259678969800[23] = 0;
   out_1714418259678969800[24] = 0;
   out_1714418259678969800[25] = 1;
   out_1714418259678969800[26] = 0;
   out_1714418259678969800[27] = 0;
   out_1714418259678969800[28] = 1;
   out_1714418259678969800[29] = 0;
   out_1714418259678969800[30] = 0;
   out_1714418259678969800[31] = 0;
   out_1714418259678969800[32] = 0;
   out_1714418259678969800[33] = 0;
   out_1714418259678969800[34] = 0;
   out_1714418259678969800[35] = 0;
   out_1714418259678969800[36] = 0;
   out_1714418259678969800[37] = 0;
   out_1714418259678969800[38] = 0;
   out_1714418259678969800[39] = 0;
   out_1714418259678969800[40] = 0;
   out_1714418259678969800[41] = 0;
   out_1714418259678969800[42] = 0;
   out_1714418259678969800[43] = 0;
   out_1714418259678969800[44] = 1;
   out_1714418259678969800[45] = 0;
   out_1714418259678969800[46] = 0;
   out_1714418259678969800[47] = 1;
   out_1714418259678969800[48] = 0;
   out_1714418259678969800[49] = 0;
   out_1714418259678969800[50] = 0;
   out_1714418259678969800[51] = 0;
   out_1714418259678969800[52] = 0;
   out_1714418259678969800[53] = 0;
}
void h_10(double *state, double *unused, double *out_2062123331753171462) {
   out_2062123331753171462[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_2062123331753171462[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_2062123331753171462[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_2475279207439212631) {
   out_2475279207439212631[0] = 0;
   out_2475279207439212631[1] = 9.8100000000000005*cos(state[1]);
   out_2475279207439212631[2] = 0;
   out_2475279207439212631[3] = 0;
   out_2475279207439212631[4] = -state[8];
   out_2475279207439212631[5] = state[7];
   out_2475279207439212631[6] = 0;
   out_2475279207439212631[7] = state[5];
   out_2475279207439212631[8] = -state[4];
   out_2475279207439212631[9] = 0;
   out_2475279207439212631[10] = 0;
   out_2475279207439212631[11] = 0;
   out_2475279207439212631[12] = 1;
   out_2475279207439212631[13] = 0;
   out_2475279207439212631[14] = 0;
   out_2475279207439212631[15] = 1;
   out_2475279207439212631[16] = 0;
   out_2475279207439212631[17] = 0;
   out_2475279207439212631[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_2475279207439212631[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_2475279207439212631[20] = 0;
   out_2475279207439212631[21] = state[8];
   out_2475279207439212631[22] = 0;
   out_2475279207439212631[23] = -state[6];
   out_2475279207439212631[24] = -state[5];
   out_2475279207439212631[25] = 0;
   out_2475279207439212631[26] = state[3];
   out_2475279207439212631[27] = 0;
   out_2475279207439212631[28] = 0;
   out_2475279207439212631[29] = 0;
   out_2475279207439212631[30] = 0;
   out_2475279207439212631[31] = 1;
   out_2475279207439212631[32] = 0;
   out_2475279207439212631[33] = 0;
   out_2475279207439212631[34] = 1;
   out_2475279207439212631[35] = 0;
   out_2475279207439212631[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_2475279207439212631[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_2475279207439212631[38] = 0;
   out_2475279207439212631[39] = -state[7];
   out_2475279207439212631[40] = state[6];
   out_2475279207439212631[41] = 0;
   out_2475279207439212631[42] = state[4];
   out_2475279207439212631[43] = -state[3];
   out_2475279207439212631[44] = 0;
   out_2475279207439212631[45] = 0;
   out_2475279207439212631[46] = 0;
   out_2475279207439212631[47] = 0;
   out_2475279207439212631[48] = 0;
   out_2475279207439212631[49] = 0;
   out_2475279207439212631[50] = 1;
   out_2475279207439212631[51] = 0;
   out_2475279207439212631[52] = 0;
   out_2475279207439212631[53] = 1;
}
void h_13(double *state, double *unused, double *out_6998539107268807122) {
   out_6998539107268807122[0] = state[3];
   out_6998539107268807122[1] = state[4];
   out_6998539107268807122[2] = state[5];
}
void H_13(double *state, double *unused, double *out_9121694605713880887) {
   out_9121694605713880887[0] = 0;
   out_9121694605713880887[1] = 0;
   out_9121694605713880887[2] = 0;
   out_9121694605713880887[3] = 1;
   out_9121694605713880887[4] = 0;
   out_9121694605713880887[5] = 0;
   out_9121694605713880887[6] = 0;
   out_9121694605713880887[7] = 0;
   out_9121694605713880887[8] = 0;
   out_9121694605713880887[9] = 0;
   out_9121694605713880887[10] = 0;
   out_9121694605713880887[11] = 0;
   out_9121694605713880887[12] = 0;
   out_9121694605713880887[13] = 0;
   out_9121694605713880887[14] = 0;
   out_9121694605713880887[15] = 0;
   out_9121694605713880887[16] = 0;
   out_9121694605713880887[17] = 0;
   out_9121694605713880887[18] = 0;
   out_9121694605713880887[19] = 0;
   out_9121694605713880887[20] = 0;
   out_9121694605713880887[21] = 0;
   out_9121694605713880887[22] = 1;
   out_9121694605713880887[23] = 0;
   out_9121694605713880887[24] = 0;
   out_9121694605713880887[25] = 0;
   out_9121694605713880887[26] = 0;
   out_9121694605713880887[27] = 0;
   out_9121694605713880887[28] = 0;
   out_9121694605713880887[29] = 0;
   out_9121694605713880887[30] = 0;
   out_9121694605713880887[31] = 0;
   out_9121694605713880887[32] = 0;
   out_9121694605713880887[33] = 0;
   out_9121694605713880887[34] = 0;
   out_9121694605713880887[35] = 0;
   out_9121694605713880887[36] = 0;
   out_9121694605713880887[37] = 0;
   out_9121694605713880887[38] = 0;
   out_9121694605713880887[39] = 0;
   out_9121694605713880887[40] = 0;
   out_9121694605713880887[41] = 1;
   out_9121694605713880887[42] = 0;
   out_9121694605713880887[43] = 0;
   out_9121694605713880887[44] = 0;
   out_9121694605713880887[45] = 0;
   out_9121694605713880887[46] = 0;
   out_9121694605713880887[47] = 0;
   out_9121694605713880887[48] = 0;
   out_9121694605713880887[49] = 0;
   out_9121694605713880887[50] = 0;
   out_9121694605713880887[51] = 0;
   out_9121694605713880887[52] = 0;
   out_9121694605713880887[53] = 0;
}
void h_14(double *state, double *unused, double *out_1892429868369893879) {
   out_1892429868369893879[0] = state[6];
   out_1892429868369893879[1] = state[7];
   out_1892429868369893879[2] = state[8];
}
void H_14(double *state, double *unused, double *out_5677659116018454329) {
   out_5677659116018454329[0] = 0;
   out_5677659116018454329[1] = 0;
   out_5677659116018454329[2] = 0;
   out_5677659116018454329[3] = 0;
   out_5677659116018454329[4] = 0;
   out_5677659116018454329[5] = 0;
   out_5677659116018454329[6] = 1;
   out_5677659116018454329[7] = 0;
   out_5677659116018454329[8] = 0;
   out_5677659116018454329[9] = 0;
   out_5677659116018454329[10] = 0;
   out_5677659116018454329[11] = 0;
   out_5677659116018454329[12] = 0;
   out_5677659116018454329[13] = 0;
   out_5677659116018454329[14] = 0;
   out_5677659116018454329[15] = 0;
   out_5677659116018454329[16] = 0;
   out_5677659116018454329[17] = 0;
   out_5677659116018454329[18] = 0;
   out_5677659116018454329[19] = 0;
   out_5677659116018454329[20] = 0;
   out_5677659116018454329[21] = 0;
   out_5677659116018454329[22] = 0;
   out_5677659116018454329[23] = 0;
   out_5677659116018454329[24] = 0;
   out_5677659116018454329[25] = 1;
   out_5677659116018454329[26] = 0;
   out_5677659116018454329[27] = 0;
   out_5677659116018454329[28] = 0;
   out_5677659116018454329[29] = 0;
   out_5677659116018454329[30] = 0;
   out_5677659116018454329[31] = 0;
   out_5677659116018454329[32] = 0;
   out_5677659116018454329[33] = 0;
   out_5677659116018454329[34] = 0;
   out_5677659116018454329[35] = 0;
   out_5677659116018454329[36] = 0;
   out_5677659116018454329[37] = 0;
   out_5677659116018454329[38] = 0;
   out_5677659116018454329[39] = 0;
   out_5677659116018454329[40] = 0;
   out_5677659116018454329[41] = 0;
   out_5677659116018454329[42] = 0;
   out_5677659116018454329[43] = 0;
   out_5677659116018454329[44] = 1;
   out_5677659116018454329[45] = 0;
   out_5677659116018454329[46] = 0;
   out_5677659116018454329[47] = 0;
   out_5677659116018454329[48] = 0;
   out_5677659116018454329[49] = 0;
   out_5677659116018454329[50] = 0;
   out_5677659116018454329[51] = 0;
   out_5677659116018454329[52] = 0;
   out_5677659116018454329[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_529622895560387506) {
  err_fun(nom_x, delta_x, out_529622895560387506);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_5635522996089764755) {
  inv_err_fun(nom_x, true_x, out_5635522996089764755);
}
void pose_H_mod_fun(double *state, double *out_3534116985585266661) {
  H_mod_fun(state, out_3534116985585266661);
}
void pose_f_fun(double *state, double dt, double *out_4412251706839144439) {
  f_fun(state,  dt, out_4412251706839144439);
}
void pose_F_fun(double *state, double dt, double *out_1358445773394405128) {
  F_fun(state,  dt, out_1358445773394405128);
}
void pose_h_4(double *state, double *unused, double *out_5199898530632523440) {
  h_4(state, unused, out_5199898530632523440);
}
void pose_H_4(double *state, double *unused, double *out_1714418259678969800) {
  H_4(state, unused, out_1714418259678969800);
}
void pose_h_10(double *state, double *unused, double *out_2062123331753171462) {
  h_10(state, unused, out_2062123331753171462);
}
void pose_H_10(double *state, double *unused, double *out_2475279207439212631) {
  H_10(state, unused, out_2475279207439212631);
}
void pose_h_13(double *state, double *unused, double *out_6998539107268807122) {
  h_13(state, unused, out_6998539107268807122);
}
void pose_H_13(double *state, double *unused, double *out_9121694605713880887) {
  H_13(state, unused, out_9121694605713880887);
}
void pose_h_14(double *state, double *unused, double *out_1892429868369893879) {
  h_14(state, unused, out_1892429868369893879);
}
void pose_H_14(double *state, double *unused, double *out_5677659116018454329) {
  H_14(state, unused, out_5677659116018454329);
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
