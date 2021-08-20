#include "propagationModels.h"

#include <QDebug>
#include <QtMath>


double distance3D(double distance2Dout, double distance2Din, double heightBS, double heightUT)
{
    return sqrt(pow(distance2Dout + distance2Din, 2) + pow(heightBS - heightUT, 2));
}

double RMa_LOS(double distance2Dout, double distance2Din, double heightBS, double heightUT,
    int centerFrequency, double h, double shadowFading)
{
    //double distance3D = sqrt(pow(distance2Dout + distance2Din, 2) + pow(heightBS - heightUT, 2));
    double distanceBP = 2 * M_PI * heightBS * heightUT / (3 * pow(10, 8));

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
double RMa_NLOS(double distance2Dout, double distance2Din, double heightBS, double heightUT,
    int centerFrequency, double h, double W, double shadowFading)
{
    double d_3D = distance3D(distance2Dout, distance2Din, heightBS, heightUT);
    if (distance2Dout < 10 && distance2Dout > 5000) {
        qWarning("Check the distance2D value. The model is applicable for "
            "10 [m] <= distance2D <= 5 [km]");
    }
    double PL_RMa_NLOS;
    PL_RMa_NLOS = 161.04 - 7.11 * log10(W) + 7.5 * log10(h) - (24.37 - 3.7 * pow(h / heightBS, 2)) *
        log10(heightBS) + (43.42 - 3.11 * log10(heightBS)) * (log10(d_3D) - 3) +
        20 * log10(centerFrequency) - (3.2 * pow(log10(11.75 * heightUT), 2) - 4.97);

    return fmax(RMa_LOS(distance2Dout, distance2Din, heightBS, heightUT, centerFrequency,
        h, shadowFading), PL_RMa_NLOS);
}

double UMa_LOS(double distance2Dout, double distance2Din, double heightBS, double heightUT,
    int centerFrequency, double h, double W, double shadowFading)
{

    double d_3D = distance3D(distance2Dout, distance2Din, heightBS, heightUT);
    double heightE = 1; // see Note 1 (page 29) TS38.901
    double distanceBP = 4 * (heightBS - heightE) * (heightUT - heightE) * centerFrequency /
        3 * pow(10, 8);
    //TODO effective antenna height (see Note 1, page 29)
    if (distance2Dout >= 10 && distance2Dout <= distanceBP) {
        return 28 + 22 * log10(d_3D) + 20 * log10(centerFrequency);
    }
    else if (distance2Dout >= distanceBP && distance2Dout <= 5000) {
        return 28 + 40 * log10(d_3D) + 20 * log10(centerFrequency) -
            9 * log10(pow(distanceBP, 2) + pow(heightBS - heightUT, 2));
    }
}

double UMa_NLOS(double distance2Dout, double distance2Din, double heightBS, double heightUT,
    int centerFrequency, double h, double W, double shadowFading)
{
    double PL_UMa_NLOS;
    double d_3D = distance3D(distance2Dout, distance2Din, heightBS, heightUT);;
    PL_UMa_NLOS = 13.54 + 39.08 * log10(d_3D) + 20 * log10(centerFrequency) -
        0.6 * (heightUT - 1.5);
    return fmax(UMa_LOS(distance2Dout, distance2Din, heightBS, heightUT, centerFrequency, h,
        W, shadowFading), PL_UMa_NLOS);
}

double UMi_LOS(double distance2Dout, double distance2Din, double heightBS, double heightUT,
    int centerFrequency, double h, double W, double shadowFading)
{
    double d_3D = distance3D(distance2Dout, distance2Din, heightBS, heightUT);
    double heightE = 1; // see Note 1 (page 29) TS38.901
    double distanceBP = 4 * (heightBS - heightE) * (heightUT - heightE) * centerFrequency /
        3 * pow(10, 8);
    //TODO effective antenna height (see Note 1, page 29)
    if (distance2Dout >= 10 && distance2Dout <= distanceBP) {
        return 32.4 + 21 * log10(d_3D) + 20 * log10(centerFrequency);
    }
    else if (distance2Dout >= distanceBP && distance2Dout <= 5000) {
        return 32.4 + 40 * log10(d_3D) + 20 * log10(centerFrequency) -
            9.5 * log10(pow(distanceBP, 2) + pow(heightBS - heightUT, 2));
    }
}

double UMi_NLOS(double distance2Dout, double distance2Din, double heightBS, double heightUT,
    int centerFrequency, double h, double W, double shadowFading)
{
    double PL_UMi_NLOS;
    double d_3D = distance3D(distance2Dout, distance2Din, heightBS, heightUT);
    PL_UMi_NLOS = 35.3 * log10(d_3D) + 22.4 + 21.3 * log10(centerFrequency) -
        0.3 * (heightUT - 1.5);
    return fmax(UMi_LOS(distance2Dout, distance2Din, heightBS, heightUT, centerFrequency, h,
        W, shadowFading), PL_UMi_NLOS);
}

double InH_LOS(double distance2Dout, double distance2Din, double heightBS, double heightUT,
    int centerFrequency, double h, double W, double shadowFading)
{
    double d_3D = distance3D(distance2Dout, distance2Din, heightBS, heightUT);
    return 32.4 + 17.3 * log10(centerFrequency) + 31.9 * log10(d_3D);
}

double InH_NLOS(double distance2Dout, double distance2Din, double heightBS, double heightUT,
    int centerFrequency, double h, double W, double shadowFading)
{
    double PL_InH_NLOS;
    double d_3D = distance3D(distance2Dout, distance2Din, heightBS, heightUT);
    PL_InH_NLOS = 38.3 * log10(d_3D) + 17.30 + 24.9 * log10(centerFrequency);
    return fmax(InH_LOS(distance2Dout, distance2Din, heightBS, heightUT,
                        centerFrequency, h, W, shadowFading), PL_InH_NLOS);
}

double InF_LOS(double distance2Dout, double distance2Din, double heightBS, double heightUT,
               int centerFrequency, double h, double W, double shadowFading)
{
    double d_3D = distance3D(distance2Dout, distance2Din, heightBS, heightUT);
    return 31.84 + 21.50 * log10(d_3D) + 19.00 * log10(centerFrequency);
}

double InF_NLOS_SL(double distance2Dout, double distance2Din, double heightBS, double heightUT,
               int centerFrequency, double h, double W, double shadowFading)
{
    double PL_InF_NLOS_SL;
    double d_3D = distance3D(distance2Dout, distance2Din, heightBS, heightUT);
    PL_InF_NLOS_SL = 33 + 25.5 * log10(d_3D) + 20 * log10(centerFrequency);
    return fmax(InF_LOS(distance2Dout, distance2Din, heightBS, heightUT,
                       centerFrequency, h, W, shadowFading), PL_InF_NLOS_SL);
}

double InF_NLOS_DL(double distance2Dout, double distance2Din, double heightBS, double heightUT,
               int centerFrequency, double h, double W, double shadowFading)
{
    double PL_InF_NLOS_DL;
    double PL_InF_NLOS_SL;
    double d_3D = distance3D(distance2Dout, distance2Din, heightBS, heightUT);
    PL_InF_NLOS_DL = 18.6 + 35.7 * log10(d_3D) + 20 * log10(centerFrequency);
    PL_InF_NLOS_SL = 33 + 25.5 * log10(d_3D) + 20 * log10(centerFrequency);
    double tempMax = fmax(InF_LOS(distance2Dout, distance2Din, heightBS, heightUT,
                       centerFrequency, h, W, shadowFading), PL_InF_NLOS_DL);
    return fmax(tempMax, PL_InF_NLOS_SL);
}

double InF_NLOS_SH(double distance2Dout, double distance2Din, double heightBS, double heightUT,
               int centerFrequency, double h, double W, double shadowFading)
{
    double PL_InF_NLOS_SH;
    double d_3D = distance3D(distance2Dout, distance2Din, heightBS, heightUT);
    PL_InF_NLOS_SH = 32.4 + 23.0 * log10(d_3D) + 20 * log10(centerFrequency);
    return fmax(InF_LOS(distance2Dout, distance2Din, heightBS, heightUT,
                       centerFrequency, h, W, shadowFading), PL_InF_NLOS_SH);
}

double InF_NLOS_DH(double distance2Dout, double distance2Din, double heightBS, double heightUT,
               int centerFrequency, double h, double W, double shadowFading)
{
    double PL_InF_NLOS_DH;
    double d_3D = distance3D(distance2Dout, distance2Din, heightBS, heightUT);
    PL_InF_NLOS_DH = 33.63 + 21.9 * log10(d_3D) + 20 * log10(centerFrequency);
    return fmax(InF_LOS(distance2Dout, distance2Din, heightBS, heightUT,
                       centerFrequency, h, W, shadowFading), PL_InF_NLOS_DH);
}



//LOS probabilitys
double RMa_LOS_probability(double distance2Dout, double distance2Din, double heightBS, double heightUT)
{
    if(distance2Dout <= 10){
        return 1;
    }
    else{
        return (exp(-(distance2Dout - 10)/(1000)));
    }
}

double UMi_LOS_probability(double distance2Dout, double distance2Din, double heightBS, double heightUT)
{
    if(distance2Dout <= 18){
        return 1;
    }
    else{
        return (18/distance2Dout + exp(-(distance2Dout/36)) * (1 - 18/distance2Dout));
    }
}

double UMa_LOS_probability(double distance2Dout, double distance2Din, double heightBS, double heightUT)
{
    double C_hUT;

    if(heightUT <= 13){
        C_hUT = 0;
    }
    else{
        if(heightUT <= 23){
            C_hUT = pow((heightUT - 13)/10, 1.5);
        }//else
    }

    if(distance2Dout <= 18){
        return 1;
    }
    else{
        return ((18/distance2Dout + exp(-(distance2Dout/63)) * (1 - 18/distance2Dout)) *
                (1 + C_hUT * 5/4 * pow(distance2Dout/100, 3) * exp(-distance2Dout/150)));
    }
}

double Indoor_MixedOffice_LOS_probability(double distance2Dout, double distance2Din, double heightBS, double heightUT)
{
    if(distance2Din <= 1.2){
        return 1;
    }
    else{
        if(distance2Din < 6.5){
            return exp(-(distance2Din - 1.2)/4.7);
        }
        else{
            return exp(-(distance2Din - 6.5)/32.6) * 0.32;
        }
    }
}

double Indoor_OpenOffice_LOS_probability(double distance2Dout, double distance2Din, double heightBS, double heightUT)
{
    if(distance2Din <= 5){
        return 1;
    }
    else{
        if(distance2Din <= 49){
            return exp(-(distance2Din - 5)/70.8);
        }
        else{
            return exp(-(distance2Din - 49)/211.7) * 0.54;
        }
    }
}

double InF_SL_LOS_probability(double distance2Dout, double distance2Din, double heightBS, double heightUT)
{
    double k_subsce;

    double d_clutter = INF_SL_D_CLUTTER;
    double r  = INF_SL_R;
    double h_c = INF_SL_H_C;

    k_subsce = -d_clutter/(log(1 - r));

    double d_2D = distance2Din + distance2Dout;
    return exp(-(d_2D)/k_subsce);
}

double InF_DL_LOS_probability(double distance2Dout, double distance2Din, double heightBS, double heightUT)
{
    double k_subsce;

    double d_clutter = INF_DL_D_CLUTTER;
    double r  = INF_DL_R;
    double h_c = INF_DL_H_C;

    k_subsce = -d_clutter/(log(1 - r));

    double d_2D = distance2Din + distance2Dout;
    return exp(-(d_2D)/k_subsce);
}

double InF_SH_LOS_probability(double distance2Dout, double distance2Din, double heightBS, double heightUT)
{
    double k_subsce;

    double d_clutter = INF_SH_D_CLUTTER;
    double r  = INF_SH_R;
    double h_c = INF_SH_H_C;

    k_subsce = -d_clutter/(log(1 - r)) * (heightBS - heightUT)/(h_c - heightUT);

    double d_2D = distance2Din + distance2Dout;
    return exp(-(d_2D)/k_subsce);
}

double InF_DH_LOS_probability(double distance2Dout, double distance2Din, double heightBS, double heightUT)
{
    double k_subsce;

    double d_clutter = INF_DH_D_CLUTTER;
    double r  = INF_DH_R;
    double h_c = INF_DH_H_C;

    k_subsce = -d_clutter/(log(1 - r)) * (heightBS - heightUT)/(h_c - heightUT);

    double d_2D = distance2Din + distance2Dout;
    return exp(-(d_2D)/k_subsce);
}

double InF_HH_LOS_probability(double distance2Dout, double distance2Din, double heightBS, double heightUT)
{
    return 1;
}
