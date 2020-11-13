#ifndef PROPAGATIONMODELS_H
#define PROPAGATIONMODELS_H
/*
 * Данный файл предоставляет доступ к функциям рассчета
 * моделей распространения радиосигнала по 3GPP TR 38.901 R16 (page 27).
 *
 */
#include <cmath>



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
 *
 */

double RMa_LOS(double distance2D, double distance3D, double heightBS, double heightUE,
               int centerFrequency, double h, double shadowFading){

    double breakPointDistance = 2 * M_PI * heightBS * heightUE / (3 * pow(10, 8));

    if (distance2D >= 10 && distance2D <= breakPointDistance) {
        return 20 * log10(40 * M_PI * distance3D * centerFrequency/3) +
                fmin(pow(0.03*h, 1.72), 10) * log10(distance3D) - fmin(pow(0.044*h, 1.72), 14.77) +
                0.002 * log10(h) * distance3D;
    } else {
        return 20 * log10(40 * M_PI * breakPointDistance * centerFrequency/3) +
                fmin(pow(0.03*h, 1.72), 10) * log10(breakPointDistance) -
                fmin(pow(0.044*h, 1.72), 14.77) + 0.002 * log10(h) * breakPointDistance +
                40 * log10(distance3D / breakPointDistance);
    }
}














#endif // PROPAGATIONMODELS_H
