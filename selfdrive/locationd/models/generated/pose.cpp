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
void err_fun(double *nom_x, double *delta_x, double *out_4317960585787832547) {
   out_4317960585787832547[0] = delta_x[0] + nom_x[0];
   out_4317960585787832547[1] = delta_x[1] + nom_x[1];
   out_4317960585787832547[2] = delta_x[2] + nom_x[2];
   out_4317960585787832547[3] = delta_x[3] + nom_x[3];
   out_4317960585787832547[4] = delta_x[4] + nom_x[4];
   out_4317960585787832547[5] = delta_x[5] + nom_x[5];
   out_4317960585787832547[6] = delta_x[6] + nom_x[6];
   out_4317960585787832547[7] = delta_x[7] + nom_x[7];
   out_4317960585787832547[8] = delta_x[8] + nom_x[8];
   out_4317960585787832547[9] = delta_x[9] + nom_x[9];
   out_4317960585787832547[10] = delta_x[10] + nom_x[10];
   out_4317960585787832547[11] = delta_x[11] + nom_x[11];
   out_4317960585787832547[12] = delta_x[12] + nom_x[12];
   out_4317960585787832547[13] = delta_x[13] + nom_x[13];
   out_4317960585787832547[14] = delta_x[14] + nom_x[14];
   out_4317960585787832547[15] = delta_x[15] + nom_x[15];
   out_4317960585787832547[16] = delta_x[16] + nom_x[16];
   out_4317960585787832547[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_8646049298616345457) {
   out_8646049298616345457[0] = -nom_x[0] + true_x[0];
   out_8646049298616345457[1] = -nom_x[1] + true_x[1];
   out_8646049298616345457[2] = -nom_x[2] + true_x[2];
   out_8646049298616345457[3] = -nom_x[3] + true_x[3];
   out_8646049298616345457[4] = -nom_x[4] + true_x[4];
   out_8646049298616345457[5] = -nom_x[5] + true_x[5];
   out_8646049298616345457[6] = -nom_x[6] + true_x[6];
   out_8646049298616345457[7] = -nom_x[7] + true_x[7];
   out_8646049298616345457[8] = -nom_x[8] + true_x[8];
   out_8646049298616345457[9] = -nom_x[9] + true_x[9];
   out_8646049298616345457[10] = -nom_x[10] + true_x[10];
   out_8646049298616345457[11] = -nom_x[11] + true_x[11];
   out_8646049298616345457[12] = -nom_x[12] + true_x[12];
   out_8646049298616345457[13] = -nom_x[13] + true_x[13];
   out_8646049298616345457[14] = -nom_x[14] + true_x[14];
   out_8646049298616345457[15] = -nom_x[15] + true_x[15];
   out_8646049298616345457[16] = -nom_x[16] + true_x[16];
   out_8646049298616345457[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_3862875448409277979) {
   out_3862875448409277979[0] = 1.0;
   out_3862875448409277979[1] = 0.0;
   out_3862875448409277979[2] = 0.0;
   out_3862875448409277979[3] = 0.0;
   out_3862875448409277979[4] = 0.0;
   out_3862875448409277979[5] = 0.0;
   out_3862875448409277979[6] = 0.0;
   out_3862875448409277979[7] = 0.0;
   out_3862875448409277979[8] = 0.0;
   out_3862875448409277979[9] = 0.0;
   out_3862875448409277979[10] = 0.0;
   out_3862875448409277979[11] = 0.0;
   out_3862875448409277979[12] = 0.0;
   out_3862875448409277979[13] = 0.0;
   out_3862875448409277979[14] = 0.0;
   out_3862875448409277979[15] = 0.0;
   out_3862875448409277979[16] = 0.0;
   out_3862875448409277979[17] = 0.0;
   out_3862875448409277979[18] = 0.0;
   out_3862875448409277979[19] = 1.0;
   out_3862875448409277979[20] = 0.0;
   out_3862875448409277979[21] = 0.0;
   out_3862875448409277979[22] = 0.0;
   out_3862875448409277979[23] = 0.0;
   out_3862875448409277979[24] = 0.0;
   out_3862875448409277979[25] = 0.0;
   out_3862875448409277979[26] = 0.0;
   out_3862875448409277979[27] = 0.0;
   out_3862875448409277979[28] = 0.0;
   out_3862875448409277979[29] = 0.0;
   out_3862875448409277979[30] = 0.0;
   out_3862875448409277979[31] = 0.0;
   out_3862875448409277979[32] = 0.0;
   out_3862875448409277979[33] = 0.0;
   out_3862875448409277979[34] = 0.0;
   out_3862875448409277979[35] = 0.0;
   out_3862875448409277979[36] = 0.0;
   out_3862875448409277979[37] = 0.0;
   out_3862875448409277979[38] = 1.0;
   out_3862875448409277979[39] = 0.0;
   out_3862875448409277979[40] = 0.0;
   out_3862875448409277979[41] = 0.0;
   out_3862875448409277979[42] = 0.0;
   out_3862875448409277979[43] = 0.0;
   out_3862875448409277979[44] = 0.0;
   out_3862875448409277979[45] = 0.0;
   out_3862875448409277979[46] = 0.0;
   out_3862875448409277979[47] = 0.0;
   out_3862875448409277979[48] = 0.0;
   out_3862875448409277979[49] = 0.0;
   out_3862875448409277979[50] = 0.0;
   out_3862875448409277979[51] = 0.0;
   out_3862875448409277979[52] = 0.0;
   out_3862875448409277979[53] = 0.0;
   out_3862875448409277979[54] = 0.0;
   out_3862875448409277979[55] = 0.0;
   out_3862875448409277979[56] = 0.0;
   out_3862875448409277979[57] = 1.0;
   out_3862875448409277979[58] = 0.0;
   out_3862875448409277979[59] = 0.0;
   out_3862875448409277979[60] = 0.0;
   out_3862875448409277979[61] = 0.0;
   out_3862875448409277979[62] = 0.0;
   out_3862875448409277979[63] = 0.0;
   out_3862875448409277979[64] = 0.0;
   out_3862875448409277979[65] = 0.0;
   out_3862875448409277979[66] = 0.0;
   out_3862875448409277979[67] = 0.0;
   out_3862875448409277979[68] = 0.0;
   out_3862875448409277979[69] = 0.0;
   out_3862875448409277979[70] = 0.0;
   out_3862875448409277979[71] = 0.0;
   out_3862875448409277979[72] = 0.0;
   out_3862875448409277979[73] = 0.0;
   out_3862875448409277979[74] = 0.0;
   out_3862875448409277979[75] = 0.0;
   out_3862875448409277979[76] = 1.0;
   out_3862875448409277979[77] = 0.0;
   out_3862875448409277979[78] = 0.0;
   out_3862875448409277979[79] = 0.0;
   out_3862875448409277979[80] = 0.0;
   out_3862875448409277979[81] = 0.0;
   out_3862875448409277979[82] = 0.0;
   out_3862875448409277979[83] = 0.0;
   out_3862875448409277979[84] = 0.0;
   out_3862875448409277979[85] = 0.0;
   out_3862875448409277979[86] = 0.0;
   out_3862875448409277979[87] = 0.0;
   out_3862875448409277979[88] = 0.0;
   out_3862875448409277979[89] = 0.0;
   out_3862875448409277979[90] = 0.0;
   out_3862875448409277979[91] = 0.0;
   out_3862875448409277979[92] = 0.0;
   out_3862875448409277979[93] = 0.0;
   out_3862875448409277979[94] = 0.0;
   out_3862875448409277979[95] = 1.0;
   out_3862875448409277979[96] = 0.0;
   out_3862875448409277979[97] = 0.0;
   out_3862875448409277979[98] = 0.0;
   out_3862875448409277979[99] = 0.0;
   out_3862875448409277979[100] = 0.0;
   out_3862875448409277979[101] = 0.0;
   out_3862875448409277979[102] = 0.0;
   out_3862875448409277979[103] = 0.0;
   out_3862875448409277979[104] = 0.0;
   out_3862875448409277979[105] = 0.0;
   out_3862875448409277979[106] = 0.0;
   out_3862875448409277979[107] = 0.0;
   out_3862875448409277979[108] = 0.0;
   out_3862875448409277979[109] = 0.0;
   out_3862875448409277979[110] = 0.0;
   out_3862875448409277979[111] = 0.0;
   out_3862875448409277979[112] = 0.0;
   out_3862875448409277979[113] = 0.0;
   out_3862875448409277979[114] = 1.0;
   out_3862875448409277979[115] = 0.0;
   out_3862875448409277979[116] = 0.0;
   out_3862875448409277979[117] = 0.0;
   out_3862875448409277979[118] = 0.0;
   out_3862875448409277979[119] = 0.0;
   out_3862875448409277979[120] = 0.0;
   out_3862875448409277979[121] = 0.0;
   out_3862875448409277979[122] = 0.0;
   out_3862875448409277979[123] = 0.0;
   out_3862875448409277979[124] = 0.0;
   out_3862875448409277979[125] = 0.0;
   out_3862875448409277979[126] = 0.0;
   out_3862875448409277979[127] = 0.0;
   out_3862875448409277979[128] = 0.0;
   out_3862875448409277979[129] = 0.0;
   out_3862875448409277979[130] = 0.0;
   out_3862875448409277979[131] = 0.0;
   out_3862875448409277979[132] = 0.0;
   out_3862875448409277979[133] = 1.0;
   out_3862875448409277979[134] = 0.0;
   out_3862875448409277979[135] = 0.0;
   out_3862875448409277979[136] = 0.0;
   out_3862875448409277979[137] = 0.0;
   out_3862875448409277979[138] = 0.0;
   out_3862875448409277979[139] = 0.0;
   out_3862875448409277979[140] = 0.0;
   out_3862875448409277979[141] = 0.0;
   out_3862875448409277979[142] = 0.0;
   out_3862875448409277979[143] = 0.0;
   out_3862875448409277979[144] = 0.0;
   out_3862875448409277979[145] = 0.0;
   out_3862875448409277979[146] = 0.0;
   out_3862875448409277979[147] = 0.0;
   out_3862875448409277979[148] = 0.0;
   out_3862875448409277979[149] = 0.0;
   out_3862875448409277979[150] = 0.0;
   out_3862875448409277979[151] = 0.0;
   out_3862875448409277979[152] = 1.0;
   out_3862875448409277979[153] = 0.0;
   out_3862875448409277979[154] = 0.0;
   out_3862875448409277979[155] = 0.0;
   out_3862875448409277979[156] = 0.0;
   out_3862875448409277979[157] = 0.0;
   out_3862875448409277979[158] = 0.0;
   out_3862875448409277979[159] = 0.0;
   out_3862875448409277979[160] = 0.0;
   out_3862875448409277979[161] = 0.0;
   out_3862875448409277979[162] = 0.0;
   out_3862875448409277979[163] = 0.0;
   out_3862875448409277979[164] = 0.0;
   out_3862875448409277979[165] = 0.0;
   out_3862875448409277979[166] = 0.0;
   out_3862875448409277979[167] = 0.0;
   out_3862875448409277979[168] = 0.0;
   out_3862875448409277979[169] = 0.0;
   out_3862875448409277979[170] = 0.0;
   out_3862875448409277979[171] = 1.0;
   out_3862875448409277979[172] = 0.0;
   out_3862875448409277979[173] = 0.0;
   out_3862875448409277979[174] = 0.0;
   out_3862875448409277979[175] = 0.0;
   out_3862875448409277979[176] = 0.0;
   out_3862875448409277979[177] = 0.0;
   out_3862875448409277979[178] = 0.0;
   out_3862875448409277979[179] = 0.0;
   out_3862875448409277979[180] = 0.0;
   out_3862875448409277979[181] = 0.0;
   out_3862875448409277979[182] = 0.0;
   out_3862875448409277979[183] = 0.0;
   out_3862875448409277979[184] = 0.0;
   out_3862875448409277979[185] = 0.0;
   out_3862875448409277979[186] = 0.0;
   out_3862875448409277979[187] = 0.0;
   out_3862875448409277979[188] = 0.0;
   out_3862875448409277979[189] = 0.0;
   out_3862875448409277979[190] = 1.0;
   out_3862875448409277979[191] = 0.0;
   out_3862875448409277979[192] = 0.0;
   out_3862875448409277979[193] = 0.0;
   out_3862875448409277979[194] = 0.0;
   out_3862875448409277979[195] = 0.0;
   out_3862875448409277979[196] = 0.0;
   out_3862875448409277979[197] = 0.0;
   out_3862875448409277979[198] = 0.0;
   out_3862875448409277979[199] = 0.0;
   out_3862875448409277979[200] = 0.0;
   out_3862875448409277979[201] = 0.0;
   out_3862875448409277979[202] = 0.0;
   out_3862875448409277979[203] = 0.0;
   out_3862875448409277979[204] = 0.0;
   out_3862875448409277979[205] = 0.0;
   out_3862875448409277979[206] = 0.0;
   out_3862875448409277979[207] = 0.0;
   out_3862875448409277979[208] = 0.0;
   out_3862875448409277979[209] = 1.0;
   out_3862875448409277979[210] = 0.0;
   out_3862875448409277979[211] = 0.0;
   out_3862875448409277979[212] = 0.0;
   out_3862875448409277979[213] = 0.0;
   out_3862875448409277979[214] = 0.0;
   out_3862875448409277979[215] = 0.0;
   out_3862875448409277979[216] = 0.0;
   out_3862875448409277979[217] = 0.0;
   out_3862875448409277979[218] = 0.0;
   out_3862875448409277979[219] = 0.0;
   out_3862875448409277979[220] = 0.0;
   out_3862875448409277979[221] = 0.0;
   out_3862875448409277979[222] = 0.0;
   out_3862875448409277979[223] = 0.0;
   out_3862875448409277979[224] = 0.0;
   out_3862875448409277979[225] = 0.0;
   out_3862875448409277979[226] = 0.0;
   out_3862875448409277979[227] = 0.0;
   out_3862875448409277979[228] = 1.0;
   out_3862875448409277979[229] = 0.0;
   out_3862875448409277979[230] = 0.0;
   out_3862875448409277979[231] = 0.0;
   out_3862875448409277979[232] = 0.0;
   out_3862875448409277979[233] = 0.0;
   out_3862875448409277979[234] = 0.0;
   out_3862875448409277979[235] = 0.0;
   out_3862875448409277979[236] = 0.0;
   out_3862875448409277979[237] = 0.0;
   out_3862875448409277979[238] = 0.0;
   out_3862875448409277979[239] = 0.0;
   out_3862875448409277979[240] = 0.0;
   out_3862875448409277979[241] = 0.0;
   out_3862875448409277979[242] = 0.0;
   out_3862875448409277979[243] = 0.0;
   out_3862875448409277979[244] = 0.0;
   out_3862875448409277979[245] = 0.0;
   out_3862875448409277979[246] = 0.0;
   out_3862875448409277979[247] = 1.0;
   out_3862875448409277979[248] = 0.0;
   out_3862875448409277979[249] = 0.0;
   out_3862875448409277979[250] = 0.0;
   out_3862875448409277979[251] = 0.0;
   out_3862875448409277979[252] = 0.0;
   out_3862875448409277979[253] = 0.0;
   out_3862875448409277979[254] = 0.0;
   out_3862875448409277979[255] = 0.0;
   out_3862875448409277979[256] = 0.0;
   out_3862875448409277979[257] = 0.0;
   out_3862875448409277979[258] = 0.0;
   out_3862875448409277979[259] = 0.0;
   out_3862875448409277979[260] = 0.0;
   out_3862875448409277979[261] = 0.0;
   out_3862875448409277979[262] = 0.0;
   out_3862875448409277979[263] = 0.0;
   out_3862875448409277979[264] = 0.0;
   out_3862875448409277979[265] = 0.0;
   out_3862875448409277979[266] = 1.0;
   out_3862875448409277979[267] = 0.0;
   out_3862875448409277979[268] = 0.0;
   out_3862875448409277979[269] = 0.0;
   out_3862875448409277979[270] = 0.0;
   out_3862875448409277979[271] = 0.0;
   out_3862875448409277979[272] = 0.0;
   out_3862875448409277979[273] = 0.0;
   out_3862875448409277979[274] = 0.0;
   out_3862875448409277979[275] = 0.0;
   out_3862875448409277979[276] = 0.0;
   out_3862875448409277979[277] = 0.0;
   out_3862875448409277979[278] = 0.0;
   out_3862875448409277979[279] = 0.0;
   out_3862875448409277979[280] = 0.0;
   out_3862875448409277979[281] = 0.0;
   out_3862875448409277979[282] = 0.0;
   out_3862875448409277979[283] = 0.0;
   out_3862875448409277979[284] = 0.0;
   out_3862875448409277979[285] = 1.0;
   out_3862875448409277979[286] = 0.0;
   out_3862875448409277979[287] = 0.0;
   out_3862875448409277979[288] = 0.0;
   out_3862875448409277979[289] = 0.0;
   out_3862875448409277979[290] = 0.0;
   out_3862875448409277979[291] = 0.0;
   out_3862875448409277979[292] = 0.0;
   out_3862875448409277979[293] = 0.0;
   out_3862875448409277979[294] = 0.0;
   out_3862875448409277979[295] = 0.0;
   out_3862875448409277979[296] = 0.0;
   out_3862875448409277979[297] = 0.0;
   out_3862875448409277979[298] = 0.0;
   out_3862875448409277979[299] = 0.0;
   out_3862875448409277979[300] = 0.0;
   out_3862875448409277979[301] = 0.0;
   out_3862875448409277979[302] = 0.0;
   out_3862875448409277979[303] = 0.0;
   out_3862875448409277979[304] = 1.0;
   out_3862875448409277979[305] = 0.0;
   out_3862875448409277979[306] = 0.0;
   out_3862875448409277979[307] = 0.0;
   out_3862875448409277979[308] = 0.0;
   out_3862875448409277979[309] = 0.0;
   out_3862875448409277979[310] = 0.0;
   out_3862875448409277979[311] = 0.0;
   out_3862875448409277979[312] = 0.0;
   out_3862875448409277979[313] = 0.0;
   out_3862875448409277979[314] = 0.0;
   out_3862875448409277979[315] = 0.0;
   out_3862875448409277979[316] = 0.0;
   out_3862875448409277979[317] = 0.0;
   out_3862875448409277979[318] = 0.0;
   out_3862875448409277979[319] = 0.0;
   out_3862875448409277979[320] = 0.0;
   out_3862875448409277979[321] = 0.0;
   out_3862875448409277979[322] = 0.0;
   out_3862875448409277979[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_4189184797940026891) {
   out_4189184797940026891[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_4189184797940026891[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_4189184797940026891[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_4189184797940026891[3] = dt*state[12] + state[3];
   out_4189184797940026891[4] = dt*state[13] + state[4];
   out_4189184797940026891[5] = dt*state[14] + state[5];
   out_4189184797940026891[6] = state[6];
   out_4189184797940026891[7] = state[7];
   out_4189184797940026891[8] = state[8];
   out_4189184797940026891[9] = state[9];
   out_4189184797940026891[10] = state[10];
   out_4189184797940026891[11] = state[11];
   out_4189184797940026891[12] = state[12];
   out_4189184797940026891[13] = state[13];
   out_4189184797940026891[14] = state[14];
   out_4189184797940026891[15] = state[15];
   out_4189184797940026891[16] = state[16];
   out_4189184797940026891[17] = state[17];
}
void F_fun(double *state, double dt, double *out_92299593068743238) {
   out_92299593068743238[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_92299593068743238[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_92299593068743238[2] = 0;
   out_92299593068743238[3] = 0;
   out_92299593068743238[4] = 0;
   out_92299593068743238[5] = 0;
   out_92299593068743238[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_92299593068743238[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_92299593068743238[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_92299593068743238[9] = 0;
   out_92299593068743238[10] = 0;
   out_92299593068743238[11] = 0;
   out_92299593068743238[12] = 0;
   out_92299593068743238[13] = 0;
   out_92299593068743238[14] = 0;
   out_92299593068743238[15] = 0;
   out_92299593068743238[16] = 0;
   out_92299593068743238[17] = 0;
   out_92299593068743238[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_92299593068743238[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_92299593068743238[20] = 0;
   out_92299593068743238[21] = 0;
   out_92299593068743238[22] = 0;
   out_92299593068743238[23] = 0;
   out_92299593068743238[24] = 0;
   out_92299593068743238[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_92299593068743238[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_92299593068743238[27] = 0;
   out_92299593068743238[28] = 0;
   out_92299593068743238[29] = 0;
   out_92299593068743238[30] = 0;
   out_92299593068743238[31] = 0;
   out_92299593068743238[32] = 0;
   out_92299593068743238[33] = 0;
   out_92299593068743238[34] = 0;
   out_92299593068743238[35] = 0;
   out_92299593068743238[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_92299593068743238[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_92299593068743238[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_92299593068743238[39] = 0;
   out_92299593068743238[40] = 0;
   out_92299593068743238[41] = 0;
   out_92299593068743238[42] = 0;
   out_92299593068743238[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_92299593068743238[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_92299593068743238[45] = 0;
   out_92299593068743238[46] = 0;
   out_92299593068743238[47] = 0;
   out_92299593068743238[48] = 0;
   out_92299593068743238[49] = 0;
   out_92299593068743238[50] = 0;
   out_92299593068743238[51] = 0;
   out_92299593068743238[52] = 0;
   out_92299593068743238[53] = 0;
   out_92299593068743238[54] = 0;
   out_92299593068743238[55] = 0;
   out_92299593068743238[56] = 0;
   out_92299593068743238[57] = 1;
   out_92299593068743238[58] = 0;
   out_92299593068743238[59] = 0;
   out_92299593068743238[60] = 0;
   out_92299593068743238[61] = 0;
   out_92299593068743238[62] = 0;
   out_92299593068743238[63] = 0;
   out_92299593068743238[64] = 0;
   out_92299593068743238[65] = 0;
   out_92299593068743238[66] = dt;
   out_92299593068743238[67] = 0;
   out_92299593068743238[68] = 0;
   out_92299593068743238[69] = 0;
   out_92299593068743238[70] = 0;
   out_92299593068743238[71] = 0;
   out_92299593068743238[72] = 0;
   out_92299593068743238[73] = 0;
   out_92299593068743238[74] = 0;
   out_92299593068743238[75] = 0;
   out_92299593068743238[76] = 1;
   out_92299593068743238[77] = 0;
   out_92299593068743238[78] = 0;
   out_92299593068743238[79] = 0;
   out_92299593068743238[80] = 0;
   out_92299593068743238[81] = 0;
   out_92299593068743238[82] = 0;
   out_92299593068743238[83] = 0;
   out_92299593068743238[84] = 0;
   out_92299593068743238[85] = dt;
   out_92299593068743238[86] = 0;
   out_92299593068743238[87] = 0;
   out_92299593068743238[88] = 0;
   out_92299593068743238[89] = 0;
   out_92299593068743238[90] = 0;
   out_92299593068743238[91] = 0;
   out_92299593068743238[92] = 0;
   out_92299593068743238[93] = 0;
   out_92299593068743238[94] = 0;
   out_92299593068743238[95] = 1;
   out_92299593068743238[96] = 0;
   out_92299593068743238[97] = 0;
   out_92299593068743238[98] = 0;
   out_92299593068743238[99] = 0;
   out_92299593068743238[100] = 0;
   out_92299593068743238[101] = 0;
   out_92299593068743238[102] = 0;
   out_92299593068743238[103] = 0;
   out_92299593068743238[104] = dt;
   out_92299593068743238[105] = 0;
   out_92299593068743238[106] = 0;
   out_92299593068743238[107] = 0;
   out_92299593068743238[108] = 0;
   out_92299593068743238[109] = 0;
   out_92299593068743238[110] = 0;
   out_92299593068743238[111] = 0;
   out_92299593068743238[112] = 0;
   out_92299593068743238[113] = 0;
   out_92299593068743238[114] = 1;
   out_92299593068743238[115] = 0;
   out_92299593068743238[116] = 0;
   out_92299593068743238[117] = 0;
   out_92299593068743238[118] = 0;
   out_92299593068743238[119] = 0;
   out_92299593068743238[120] = 0;
   out_92299593068743238[121] = 0;
   out_92299593068743238[122] = 0;
   out_92299593068743238[123] = 0;
   out_92299593068743238[124] = 0;
   out_92299593068743238[125] = 0;
   out_92299593068743238[126] = 0;
   out_92299593068743238[127] = 0;
   out_92299593068743238[128] = 0;
   out_92299593068743238[129] = 0;
   out_92299593068743238[130] = 0;
   out_92299593068743238[131] = 0;
   out_92299593068743238[132] = 0;
   out_92299593068743238[133] = 1;
   out_92299593068743238[134] = 0;
   out_92299593068743238[135] = 0;
   out_92299593068743238[136] = 0;
   out_92299593068743238[137] = 0;
   out_92299593068743238[138] = 0;
   out_92299593068743238[139] = 0;
   out_92299593068743238[140] = 0;
   out_92299593068743238[141] = 0;
   out_92299593068743238[142] = 0;
   out_92299593068743238[143] = 0;
   out_92299593068743238[144] = 0;
   out_92299593068743238[145] = 0;
   out_92299593068743238[146] = 0;
   out_92299593068743238[147] = 0;
   out_92299593068743238[148] = 0;
   out_92299593068743238[149] = 0;
   out_92299593068743238[150] = 0;
   out_92299593068743238[151] = 0;
   out_92299593068743238[152] = 1;
   out_92299593068743238[153] = 0;
   out_92299593068743238[154] = 0;
   out_92299593068743238[155] = 0;
   out_92299593068743238[156] = 0;
   out_92299593068743238[157] = 0;
   out_92299593068743238[158] = 0;
   out_92299593068743238[159] = 0;
   out_92299593068743238[160] = 0;
   out_92299593068743238[161] = 0;
   out_92299593068743238[162] = 0;
   out_92299593068743238[163] = 0;
   out_92299593068743238[164] = 0;
   out_92299593068743238[165] = 0;
   out_92299593068743238[166] = 0;
   out_92299593068743238[167] = 0;
   out_92299593068743238[168] = 0;
   out_92299593068743238[169] = 0;
   out_92299593068743238[170] = 0;
   out_92299593068743238[171] = 1;
   out_92299593068743238[172] = 0;
   out_92299593068743238[173] = 0;
   out_92299593068743238[174] = 0;
   out_92299593068743238[175] = 0;
   out_92299593068743238[176] = 0;
   out_92299593068743238[177] = 0;
   out_92299593068743238[178] = 0;
   out_92299593068743238[179] = 0;
   out_92299593068743238[180] = 0;
   out_92299593068743238[181] = 0;
   out_92299593068743238[182] = 0;
   out_92299593068743238[183] = 0;
   out_92299593068743238[184] = 0;
   out_92299593068743238[185] = 0;
   out_92299593068743238[186] = 0;
   out_92299593068743238[187] = 0;
   out_92299593068743238[188] = 0;
   out_92299593068743238[189] = 0;
   out_92299593068743238[190] = 1;
   out_92299593068743238[191] = 0;
   out_92299593068743238[192] = 0;
   out_92299593068743238[193] = 0;
   out_92299593068743238[194] = 0;
   out_92299593068743238[195] = 0;
   out_92299593068743238[196] = 0;
   out_92299593068743238[197] = 0;
   out_92299593068743238[198] = 0;
   out_92299593068743238[199] = 0;
   out_92299593068743238[200] = 0;
   out_92299593068743238[201] = 0;
   out_92299593068743238[202] = 0;
   out_92299593068743238[203] = 0;
   out_92299593068743238[204] = 0;
   out_92299593068743238[205] = 0;
   out_92299593068743238[206] = 0;
   out_92299593068743238[207] = 0;
   out_92299593068743238[208] = 0;
   out_92299593068743238[209] = 1;
   out_92299593068743238[210] = 0;
   out_92299593068743238[211] = 0;
   out_92299593068743238[212] = 0;
   out_92299593068743238[213] = 0;
   out_92299593068743238[214] = 0;
   out_92299593068743238[215] = 0;
   out_92299593068743238[216] = 0;
   out_92299593068743238[217] = 0;
   out_92299593068743238[218] = 0;
   out_92299593068743238[219] = 0;
   out_92299593068743238[220] = 0;
   out_92299593068743238[221] = 0;
   out_92299593068743238[222] = 0;
   out_92299593068743238[223] = 0;
   out_92299593068743238[224] = 0;
   out_92299593068743238[225] = 0;
   out_92299593068743238[226] = 0;
   out_92299593068743238[227] = 0;
   out_92299593068743238[228] = 1;
   out_92299593068743238[229] = 0;
   out_92299593068743238[230] = 0;
   out_92299593068743238[231] = 0;
   out_92299593068743238[232] = 0;
   out_92299593068743238[233] = 0;
   out_92299593068743238[234] = 0;
   out_92299593068743238[235] = 0;
   out_92299593068743238[236] = 0;
   out_92299593068743238[237] = 0;
   out_92299593068743238[238] = 0;
   out_92299593068743238[239] = 0;
   out_92299593068743238[240] = 0;
   out_92299593068743238[241] = 0;
   out_92299593068743238[242] = 0;
   out_92299593068743238[243] = 0;
   out_92299593068743238[244] = 0;
   out_92299593068743238[245] = 0;
   out_92299593068743238[246] = 0;
   out_92299593068743238[247] = 1;
   out_92299593068743238[248] = 0;
   out_92299593068743238[249] = 0;
   out_92299593068743238[250] = 0;
   out_92299593068743238[251] = 0;
   out_92299593068743238[252] = 0;
   out_92299593068743238[253] = 0;
   out_92299593068743238[254] = 0;
   out_92299593068743238[255] = 0;
   out_92299593068743238[256] = 0;
   out_92299593068743238[257] = 0;
   out_92299593068743238[258] = 0;
   out_92299593068743238[259] = 0;
   out_92299593068743238[260] = 0;
   out_92299593068743238[261] = 0;
   out_92299593068743238[262] = 0;
   out_92299593068743238[263] = 0;
   out_92299593068743238[264] = 0;
   out_92299593068743238[265] = 0;
   out_92299593068743238[266] = 1;
   out_92299593068743238[267] = 0;
   out_92299593068743238[268] = 0;
   out_92299593068743238[269] = 0;
   out_92299593068743238[270] = 0;
   out_92299593068743238[271] = 0;
   out_92299593068743238[272] = 0;
   out_92299593068743238[273] = 0;
   out_92299593068743238[274] = 0;
   out_92299593068743238[275] = 0;
   out_92299593068743238[276] = 0;
   out_92299593068743238[277] = 0;
   out_92299593068743238[278] = 0;
   out_92299593068743238[279] = 0;
   out_92299593068743238[280] = 0;
   out_92299593068743238[281] = 0;
   out_92299593068743238[282] = 0;
   out_92299593068743238[283] = 0;
   out_92299593068743238[284] = 0;
   out_92299593068743238[285] = 1;
   out_92299593068743238[286] = 0;
   out_92299593068743238[287] = 0;
   out_92299593068743238[288] = 0;
   out_92299593068743238[289] = 0;
   out_92299593068743238[290] = 0;
   out_92299593068743238[291] = 0;
   out_92299593068743238[292] = 0;
   out_92299593068743238[293] = 0;
   out_92299593068743238[294] = 0;
   out_92299593068743238[295] = 0;
   out_92299593068743238[296] = 0;
   out_92299593068743238[297] = 0;
   out_92299593068743238[298] = 0;
   out_92299593068743238[299] = 0;
   out_92299593068743238[300] = 0;
   out_92299593068743238[301] = 0;
   out_92299593068743238[302] = 0;
   out_92299593068743238[303] = 0;
   out_92299593068743238[304] = 1;
   out_92299593068743238[305] = 0;
   out_92299593068743238[306] = 0;
   out_92299593068743238[307] = 0;
   out_92299593068743238[308] = 0;
   out_92299593068743238[309] = 0;
   out_92299593068743238[310] = 0;
   out_92299593068743238[311] = 0;
   out_92299593068743238[312] = 0;
   out_92299593068743238[313] = 0;
   out_92299593068743238[314] = 0;
   out_92299593068743238[315] = 0;
   out_92299593068743238[316] = 0;
   out_92299593068743238[317] = 0;
   out_92299593068743238[318] = 0;
   out_92299593068743238[319] = 0;
   out_92299593068743238[320] = 0;
   out_92299593068743238[321] = 0;
   out_92299593068743238[322] = 0;
   out_92299593068743238[323] = 1;
}
void h_4(double *state, double *unused, double *out_40016825818469097) {
   out_40016825818469097[0] = state[6] + state[9];
   out_40016825818469097[1] = state[7] + state[10];
   out_40016825818469097[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_7137097527200227232) {
   out_7137097527200227232[0] = 0;
   out_7137097527200227232[1] = 0;
   out_7137097527200227232[2] = 0;
   out_7137097527200227232[3] = 0;
   out_7137097527200227232[4] = 0;
   out_7137097527200227232[5] = 0;
   out_7137097527200227232[6] = 1;
   out_7137097527200227232[7] = 0;
   out_7137097527200227232[8] = 0;
   out_7137097527200227232[9] = 1;
   out_7137097527200227232[10] = 0;
   out_7137097527200227232[11] = 0;
   out_7137097527200227232[12] = 0;
   out_7137097527200227232[13] = 0;
   out_7137097527200227232[14] = 0;
   out_7137097527200227232[15] = 0;
   out_7137097527200227232[16] = 0;
   out_7137097527200227232[17] = 0;
   out_7137097527200227232[18] = 0;
   out_7137097527200227232[19] = 0;
   out_7137097527200227232[20] = 0;
   out_7137097527200227232[21] = 0;
   out_7137097527200227232[22] = 0;
   out_7137097527200227232[23] = 0;
   out_7137097527200227232[24] = 0;
   out_7137097527200227232[25] = 1;
   out_7137097527200227232[26] = 0;
   out_7137097527200227232[27] = 0;
   out_7137097527200227232[28] = 1;
   out_7137097527200227232[29] = 0;
   out_7137097527200227232[30] = 0;
   out_7137097527200227232[31] = 0;
   out_7137097527200227232[32] = 0;
   out_7137097527200227232[33] = 0;
   out_7137097527200227232[34] = 0;
   out_7137097527200227232[35] = 0;
   out_7137097527200227232[36] = 0;
   out_7137097527200227232[37] = 0;
   out_7137097527200227232[38] = 0;
   out_7137097527200227232[39] = 0;
   out_7137097527200227232[40] = 0;
   out_7137097527200227232[41] = 0;
   out_7137097527200227232[42] = 0;
   out_7137097527200227232[43] = 0;
   out_7137097527200227232[44] = 1;
   out_7137097527200227232[45] = 0;
   out_7137097527200227232[46] = 0;
   out_7137097527200227232[47] = 1;
   out_7137097527200227232[48] = 0;
   out_7137097527200227232[49] = 0;
   out_7137097527200227232[50] = 0;
   out_7137097527200227232[51] = 0;
   out_7137097527200227232[52] = 0;
   out_7137097527200227232[53] = 0;
}
void h_10(double *state, double *unused, double *out_8717338601611353402) {
   out_8717338601611353402[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_8717338601611353402[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_8717338601611353402[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_3547541820256081924) {
   out_3547541820256081924[0] = 0;
   out_3547541820256081924[1] = 9.8100000000000005*cos(state[1]);
   out_3547541820256081924[2] = 0;
   out_3547541820256081924[3] = 0;
   out_3547541820256081924[4] = -state[8];
   out_3547541820256081924[5] = state[7];
   out_3547541820256081924[6] = 0;
   out_3547541820256081924[7] = state[5];
   out_3547541820256081924[8] = -state[4];
   out_3547541820256081924[9] = 0;
   out_3547541820256081924[10] = 0;
   out_3547541820256081924[11] = 0;
   out_3547541820256081924[12] = 1;
   out_3547541820256081924[13] = 0;
   out_3547541820256081924[14] = 0;
   out_3547541820256081924[15] = 1;
   out_3547541820256081924[16] = 0;
   out_3547541820256081924[17] = 0;
   out_3547541820256081924[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_3547541820256081924[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_3547541820256081924[20] = 0;
   out_3547541820256081924[21] = state[8];
   out_3547541820256081924[22] = 0;
   out_3547541820256081924[23] = -state[6];
   out_3547541820256081924[24] = -state[5];
   out_3547541820256081924[25] = 0;
   out_3547541820256081924[26] = state[3];
   out_3547541820256081924[27] = 0;
   out_3547541820256081924[28] = 0;
   out_3547541820256081924[29] = 0;
   out_3547541820256081924[30] = 0;
   out_3547541820256081924[31] = 1;
   out_3547541820256081924[32] = 0;
   out_3547541820256081924[33] = 0;
   out_3547541820256081924[34] = 1;
   out_3547541820256081924[35] = 0;
   out_3547541820256081924[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_3547541820256081924[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_3547541820256081924[38] = 0;
   out_3547541820256081924[39] = -state[7];
   out_3547541820256081924[40] = state[6];
   out_3547541820256081924[41] = 0;
   out_3547541820256081924[42] = state[4];
   out_3547541820256081924[43] = -state[3];
   out_3547541820256081924[44] = 0;
   out_3547541820256081924[45] = 0;
   out_3547541820256081924[46] = 0;
   out_3547541820256081924[47] = 0;
   out_3547541820256081924[48] = 0;
   out_3547541820256081924[49] = 0;
   out_3547541820256081924[50] = 1;
   out_3547541820256081924[51] = 0;
   out_3547541820256081924[52] = 0;
   out_3547541820256081924[53] = 1;
}
void h_13(double *state, double *unused, double *out_3019458539864484205) {
   out_3019458539864484205[0] = state[3];
   out_3019458539864484205[1] = state[4];
   out_3019458539864484205[2] = state[5];
}
void H_13(double *state, double *unused, double *out_3924823701867894431) {
   out_3924823701867894431[0] = 0;
   out_3924823701867894431[1] = 0;
   out_3924823701867894431[2] = 0;
   out_3924823701867894431[3] = 1;
   out_3924823701867894431[4] = 0;
   out_3924823701867894431[5] = 0;
   out_3924823701867894431[6] = 0;
   out_3924823701867894431[7] = 0;
   out_3924823701867894431[8] = 0;
   out_3924823701867894431[9] = 0;
   out_3924823701867894431[10] = 0;
   out_3924823701867894431[11] = 0;
   out_3924823701867894431[12] = 0;
   out_3924823701867894431[13] = 0;
   out_3924823701867894431[14] = 0;
   out_3924823701867894431[15] = 0;
   out_3924823701867894431[16] = 0;
   out_3924823701867894431[17] = 0;
   out_3924823701867894431[18] = 0;
   out_3924823701867894431[19] = 0;
   out_3924823701867894431[20] = 0;
   out_3924823701867894431[21] = 0;
   out_3924823701867894431[22] = 1;
   out_3924823701867894431[23] = 0;
   out_3924823701867894431[24] = 0;
   out_3924823701867894431[25] = 0;
   out_3924823701867894431[26] = 0;
   out_3924823701867894431[27] = 0;
   out_3924823701867894431[28] = 0;
   out_3924823701867894431[29] = 0;
   out_3924823701867894431[30] = 0;
   out_3924823701867894431[31] = 0;
   out_3924823701867894431[32] = 0;
   out_3924823701867894431[33] = 0;
   out_3924823701867894431[34] = 0;
   out_3924823701867894431[35] = 0;
   out_3924823701867894431[36] = 0;
   out_3924823701867894431[37] = 0;
   out_3924823701867894431[38] = 0;
   out_3924823701867894431[39] = 0;
   out_3924823701867894431[40] = 0;
   out_3924823701867894431[41] = 1;
   out_3924823701867894431[42] = 0;
   out_3924823701867894431[43] = 0;
   out_3924823701867894431[44] = 0;
   out_3924823701867894431[45] = 0;
   out_3924823701867894431[46] = 0;
   out_3924823701867894431[47] = 0;
   out_3924823701867894431[48] = 0;
   out_3924823701867894431[49] = 0;
   out_3924823701867894431[50] = 0;
   out_3924823701867894431[51] = 0;
   out_3924823701867894431[52] = 0;
   out_3924823701867894431[53] = 0;
}
void h_14(double *state, double *unused, double *out_925858555095681395) {
   out_925858555095681395[0] = state[6];
   out_925858555095681395[1] = state[7];
   out_925858555095681395[2] = state[8];
}
void H_14(double *state, double *unused, double *out_3173856670860742703) {
   out_3173856670860742703[0] = 0;
   out_3173856670860742703[1] = 0;
   out_3173856670860742703[2] = 0;
   out_3173856670860742703[3] = 0;
   out_3173856670860742703[4] = 0;
   out_3173856670860742703[5] = 0;
   out_3173856670860742703[6] = 1;
   out_3173856670860742703[7] = 0;
   out_3173856670860742703[8] = 0;
   out_3173856670860742703[9] = 0;
   out_3173856670860742703[10] = 0;
   out_3173856670860742703[11] = 0;
   out_3173856670860742703[12] = 0;
   out_3173856670860742703[13] = 0;
   out_3173856670860742703[14] = 0;
   out_3173856670860742703[15] = 0;
   out_3173856670860742703[16] = 0;
   out_3173856670860742703[17] = 0;
   out_3173856670860742703[18] = 0;
   out_3173856670860742703[19] = 0;
   out_3173856670860742703[20] = 0;
   out_3173856670860742703[21] = 0;
   out_3173856670860742703[22] = 0;
   out_3173856670860742703[23] = 0;
   out_3173856670860742703[24] = 0;
   out_3173856670860742703[25] = 1;
   out_3173856670860742703[26] = 0;
   out_3173856670860742703[27] = 0;
   out_3173856670860742703[28] = 0;
   out_3173856670860742703[29] = 0;
   out_3173856670860742703[30] = 0;
   out_3173856670860742703[31] = 0;
   out_3173856670860742703[32] = 0;
   out_3173856670860742703[33] = 0;
   out_3173856670860742703[34] = 0;
   out_3173856670860742703[35] = 0;
   out_3173856670860742703[36] = 0;
   out_3173856670860742703[37] = 0;
   out_3173856670860742703[38] = 0;
   out_3173856670860742703[39] = 0;
   out_3173856670860742703[40] = 0;
   out_3173856670860742703[41] = 0;
   out_3173856670860742703[42] = 0;
   out_3173856670860742703[43] = 0;
   out_3173856670860742703[44] = 1;
   out_3173856670860742703[45] = 0;
   out_3173856670860742703[46] = 0;
   out_3173856670860742703[47] = 0;
   out_3173856670860742703[48] = 0;
   out_3173856670860742703[49] = 0;
   out_3173856670860742703[50] = 0;
   out_3173856670860742703[51] = 0;
   out_3173856670860742703[52] = 0;
   out_3173856670860742703[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_4317960585787832547) {
  err_fun(nom_x, delta_x, out_4317960585787832547);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_8646049298616345457) {
  inv_err_fun(nom_x, true_x, out_8646049298616345457);
}
void pose_H_mod_fun(double *state, double *out_3862875448409277979) {
  H_mod_fun(state, out_3862875448409277979);
}
void pose_f_fun(double *state, double dt, double *out_4189184797940026891) {
  f_fun(state,  dt, out_4189184797940026891);
}
void pose_F_fun(double *state, double dt, double *out_92299593068743238) {
  F_fun(state,  dt, out_92299593068743238);
}
void pose_h_4(double *state, double *unused, double *out_40016825818469097) {
  h_4(state, unused, out_40016825818469097);
}
void pose_H_4(double *state, double *unused, double *out_7137097527200227232) {
  H_4(state, unused, out_7137097527200227232);
}
void pose_h_10(double *state, double *unused, double *out_8717338601611353402) {
  h_10(state, unused, out_8717338601611353402);
}
void pose_H_10(double *state, double *unused, double *out_3547541820256081924) {
  H_10(state, unused, out_3547541820256081924);
}
void pose_h_13(double *state, double *unused, double *out_3019458539864484205) {
  h_13(state, unused, out_3019458539864484205);
}
void pose_H_13(double *state, double *unused, double *out_3924823701867894431) {
  H_13(state, unused, out_3924823701867894431);
}
void pose_h_14(double *state, double *unused, double *out_925858555095681395) {
  h_14(state, unused, out_925858555095681395);
}
void pose_H_14(double *state, double *unused, double *out_3173856670860742703) {
  H_14(state, unused, out_3173856670860742703);
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
