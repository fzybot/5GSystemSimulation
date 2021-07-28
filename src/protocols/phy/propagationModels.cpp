#include "propagationModels.h"

#include <QDebug>
#include <QtMath>


double distance3D(double distance2Dout, double distance2Din, double heightBS, double heightUE)
{
    return sqrt(pow(distance2Dout + distance2Din, 2) + pow(heightBS - heightUE, 2));
}

double RMa_LOS(double distance2Dout, double distance2Din, double heightBS, double heightUE,
    int centerFrequency, double h, double shadowFading)
{
    //double distance3D = sqrt(pow(distance2Dout + distance2Din, 2) + pow(heightBS - heightUE, 2));
    double distanceBP = 2 * M_PI * heightBS * heightUE / (3 * pow(10, 8));

    if (distance2Dout >= 10 && distance2Dout <= distanceBP) {
        return 20 * log10(40 * M_PI * distance2Din * centerFrequency / 3) +
            fmin(pow(0.03 * h, 1.72), 10) * log10(distance2Din) - fmin(pow(0.044 * h, 1.72), 14.77) +
            0.002 * log10(h) * distance2Din;
    }
    else {
        return 20 * log10(40 * M_PI * distanceBP * centerFrequency / 3) +
            fmin(pow(0.03 * h, 1.72), 10) * log10(distanceBP) -
            fmin(pow(0.044 * h, 1.72), 14.77) + 0.002 * log10(h) * distanceBP +
            40 * log10(distance2Din / distanceBP);
    }
}

// Note: the model works for 10 [m] <= distance2D <= 5 [km]
double RMa_NLOS(double distance2Dout, double distance2Din, double heightBS, double heightUE,
    int centerFrequency, double h, double W, double shadowFading)
{
    double d_3D = distance3D(distance2Dout, distance2Din, heightBS, heightUE);
    if (distance2Dout < 10 && distance2Dout > 5000) {
        qWarning("Check the distance2D value. The model is applicable for "
            "10 [m] <= distance2D <= 5 [km]");
    }
    double PL_RMa_NLOS;
    PL_RMa_NLOS = 161.04 - 7.11 * log10(W) + 7.5 * log10(h) - (24.37 - 3.7 * pow(h / heightBS, 2)) *
        log10(heightBS) + (43.42 - 3.11 * log10(heightBS)) * (log10(d_3D) - 3) +
        20 * log10(centerFrequency) - (3.2 * pow(log10(11.75 * heightUE), 2) - 4.97);

    return fmax(RMa_LOS(distance2Dout, distance2Din, heightBS, heightUE, centerFrequency,
        h, shadowFading), PL_RMa_NLOS);
}

double UMa_LOS(double distance2Dout, double distance2Din, double heightBS, double heightUE,
    int centerFrequency, double h, double W, double shadowFading)
{

    double d_3D = distance3D(distance2Dout, distance2Din, heightBS, heightUE);;
    double heightE = 1; // see Note 1 (page 29) TS38.901
    double distanceBP = 4 * (heightBS - heightE) * (heightUE - heightE) * centerFrequency /
        3 * pow(10, 8);
    //TODO effective antenna height (see Note 1, page 29)
    if (distance2Dout >= 10 && distance2Dout <= distanceBP) {
        return 28 + 22 * log10(d_3D) + 20 * log10(centerFrequency);
    }
    else if (distance2Dout >= distanceBP && distance2Dout <= 5000) {
        return 28 + 40 * log10(d_3D) + 20 * log10(centerFrequency) -
            9 * log10(pow(distanceBP, 2) + pow(heightBS - heightUE, 2));
    }
}

double UMa_NLOS(double distance2Dout, double distance2Din, double heightBS, double heightUE,
    int centerFrequency, double h, double W, double shadowFading)
{
    double PL_UMa_NLOS;
    double d_3D = distance3D(distance2Dout, distance2Din, heightBS, heightUE);;
    PL_UMa_NLOS = 13.54 + 39.08 * log10(d_3D) + 20 * log10(centerFrequency) -
        0.6 * (heightUE - 1.5);
    return fmax(UMa_LOS(distance2Dout, distance2Din, heightBS, heightUE, centerFrequency, h,
        W, shadowFading), PL_UMa_NLOS);
}