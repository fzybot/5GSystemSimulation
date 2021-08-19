/*
 * Данный файл предоставляет доступ к функциям рассчета
 * моделей распространения радиосигнала по 3GPP TR 38.901 R16 (page 27).
 *
 */


#pragma once



/* According to TR 38.901 Table 7.4.1-1: Pathloss models (page 26):
 * centerFrequency - 'Fc' [Hz]
 * breakPointDistance - d_BP [m]
 * heightBS - h_BS [m]
 * heightUE - h_UT [m]
 * c - speed of light [m/s]
 *
 * Applicable assumptions:
 * 10 [m] <= h_bs <= 150 [m]
 * 1 [m] <= h_UT <= 10 [m]
 * h = avg. building height (5 [m] <= h <= 50 [m])
 * W = avg. street width (5 [m] <= W <= 50 [m])
 * shadowFading could be equal to 4 [dB] or 6 [dB] according to table
 */

double distance3D(double distance2Dout, double distance2Din, double heightBS, double heightUE);

double RMa_LOS(double distance2Dout, double distance2Din, double heightBS, double heightUE,
    int centerFrequency, double h, double shadowFading);

// Note: the model works for 10 [m] <= distance2D <= 5 [km]
double RMa_NLOS(double distance2Dout, double distance2Din, double heightBS, double heightUE,
    int centerFrequency, double h, double W, double shadowFading);

double UMa_LOS(double distance2Dout, double distance2Din, double heightBS, double heightUE,
    int centerFrequency, double h, double W, double shadowFading);

double UMa_NLOS(double distance2Dout, double distance2Din, double heightBS, double heightUE,
    int centerFrequency, double h, double W, double shadowFading);

//Note: UMi_LOS and UMi_NLOS models' range of values: 1.5 [m] <= heightUT <= 22.5 [m]
double UMi_LOS(double distance2Dout, double distance2Din, double heightBS, double heightUE,
    int centerFrequency, double h, double W, double shadowFading);

double UMi_NLOS(double distance2Dout, double distance2Din, double heightBS, double heightUE,
    int centerFrequency, double h, double W, double shadowFading);

//Note: InH_LOS and InH_NLOS models' range of values: 1 [m] <= distance3D <= 150 [m]
double InH_LOS(double distance2Dout, double distance2Din, double heightBS, double heightUE,
    int centerFrequency, double h, double W, double shadowFading);

double InH_NLOS(double distance2Dout, double distance2Din, double heightBS, double heightUE,
    int centerFrequency, double h, double W, double shadowFading);

//Note: InF_LOS and InF_NLOS_(...) models' range of values: 1 [m] <= distance3D <= 600 [m]
double InF_LOS(double distance2Dout, double distance2Din, double heightBS, double heightUE,
               int centerFrequency, double h, double W, double shadowFading);

double InF_NLOS_SL(double distance2Dout, double distance2Din, double heightBS, double heightUE,
               int centerFrequency, double h, double W, double shadowFading);

double InF_NLOS_DL(double distance2Dout, double distance2Din, double heightBS, double heightUE,
               int centerFrequency, double h, double W, double shadowFading);

double InF_NLOS_SH(double distance2Dout, double distance2Din, double heightBS, double heightUE,
               int centerFrequency, double h, double W, double shadowFading);

double InF_NLOS_DH(double distance2Dout, double distance2Din, double heightBS, double heightUE,
               int centerFrequency, double h, double W, double shadowFading);
