#pragma once
#include <QVector>
#include <QString>
#include <QPair>

#include "src/protocols/phy/Channel/PropagationLossModel.h"
#include "src/visualization/Chartable.h"

void propagation_model_test_plot() {

    PropagationLossModel RMA_LOS(PropagationLossModel::PropagationModel::RMA_LOS);
    PropagationLossModel RMA_NLOS(PropagationLossModel::PropagationModel::RMA_NLOS);
    PropagationLossModel UMA_LOS(PropagationLossModel::PropagationModel::UMA_LOS);
    PropagationLossModel UMA_NLOS(PropagationLossModel::PropagationModel::UMA_NLOS);
    PropagationLossModel UMI_LOS(PropagationLossModel::PropagationModel::UMI_LOS);
    PropagationLossModel UMI_NLOS(PropagationLossModel::PropagationModel::UMI_NLOS);
    PropagationLossModel INH_LOS(PropagationLossModel::PropagationModel::INH_LOS);
    PropagationLossModel INH_NLOS(PropagationLossModel::PropagationModel::INH_NLOS);
    PropagationLossModel INF_LOS(PropagationLossModel::PropagationModel::INF_LOS);
    PropagationLossModel INF_NLOS_SL(PropagationLossModel::PropagationModel::INF_NLOS_SL);
    PropagationLossModel INF_NLOS_DL(PropagationLossModel::PropagationModel::INF_NLOS_DL);
    PropagationLossModel INF_NLOS_SH(PropagationLossModel::PropagationModel::INF_NLOS_SH);
    PropagationLossModel INF_NLOS_DH(PropagationLossModel::PropagationModel::INF_NLOS_DH);
    PropagationLossModel COST231_HATA(PropagationLossModel::PropagationModel::COST231_HATA);
    PropagationLossModel FREE_SPACE(PropagationLossModel::PropagationModel::FREE_SPACE);

    QVector<QString> series_name = {"RMA_LOS", 
                                    "RMA_NLOS", 
                                    "UMA_LOS", 
                                    "UMA_NLOS", 
                                    "UMI_LOS", 
                                    "UMI_NLOS", 
                                    "INH_LOS", 
                                    "INH_NLOS", 
                                    "INF_LOS", 
                                    "INF_NLOS_SL", 
                                    "INF_NLOS_DL", 
                                    "INF_NLOS_SH", 
                                    "INF_NLOS_DH", 
                                    "COST231_HATA", 
                                    "FREE_SPACE"
                                    };

    double distance2Dout;
    double distance2Din = 0;
    double heightBS = 60;
    double heightUT = 1.5;
    double centerFrequency = 2.6;
    double h = 5;
    double W = 20;
    double shadowFading = 3;

    Chartable chart;

    QVector<QVector<QPair<double, double>>> data;
    QVector<QPair<double, double>> pairVector;
    pairVector.resize(15);
    data.resize(15);

    for (int i = 1; i < 1000; i++)
    {
        int n = 0;
        distance2Dout = i;
        if (i >= 10 && i <= 10000){
            n = 0;
            pairVector[n].first = i;
            pairVector[n].second = RMA_LOS.calculateLosses(distance2Dout, distance2Din, heightBS, heightUT, centerFrequency, h, W, shadowFading);
            data[n].push_back(pairVector[n]);

            if (i >= 10 && i <= 5000){
                n = 1;
                pairVector[n].first = i;
                pairVector[n].second = RMA_NLOS.calculateLosses(distance2Dout, distance2Din, heightBS, heightUT, centerFrequency, h, W, shadowFading);
                data[n].push_back(pairVector[n]);

                n = 2;
                pairVector[n].first = i;
                pairVector[n].second = UMA_LOS.calculateLosses(distance2Dout, distance2Din, heightBS, heightUT, centerFrequency, h, W, shadowFading);
                data[n].push_back(pairVector[n]);

                n = 3;
                pairVector[n].first = i;
                pairVector[n].second = UMA_NLOS.calculateLosses(distance2Dout, distance2Din, heightBS, heightUT, centerFrequency, h, W, shadowFading);
                data[n].push_back(pairVector[n]);

                n = 4;
                pairVector[n].first = i;
                pairVector[n].second = UMI_LOS.calculateLosses(distance2Dout, distance2Din, heightBS, heightUT, centerFrequency, h, W, shadowFading);
                data[n].push_back(pairVector[n]);

                n = 5;
                pairVector[n].first = i;
                pairVector[n].second = UMI_NLOS.calculateLosses(distance2Dout, distance2Din, heightBS, heightUT, centerFrequency, h, W, shadowFading);
                data[n].push_back(pairVector[n]);

                n = 13;
                pairVector[n].first = i;
                pairVector[n].second = COST231_HATA.calculateLosses(distance2Dout, distance2Din, heightBS, heightUT, centerFrequency, h, W, shadowFading);
                data[n].push_back(pairVector[n]);

                n = 14;
                pairVector[n].first = i;
                pairVector[n].second = FREE_SPACE.calculateLosses(distance2Dout, distance2Din, heightBS, heightUT, centerFrequency, h, W, shadowFading);
                data[n].push_back(pairVector[n]);
            }
        }
        
        if( i >= 1 && i < 150){
            n = 6;
            pairVector[n].first = i;
            pairVector[n].second = INH_LOS.calculateLosses(distance2Dout, distance2Din, heightBS, heightUT, centerFrequency, h, W, shadowFading);
            data[n].push_back(pairVector[n]);

            n = 7;
            pairVector[n].first = i;
            pairVector[n].second = INH_NLOS.calculateLosses(distance2Dout, distance2Din, heightBS, heightUT, centerFrequency, h, W, shadowFading);
            data[n].push_back(pairVector[n]);

        }

        if( i >= 1 && i < 600){

            n = 8;
            pairVector[n].first = i;
            pairVector[n].second = INF_LOS.calculateLosses(distance2Dout, distance2Din, heightBS, heightUT, centerFrequency, h, W, shadowFading);
            data[n].push_back(pairVector[n]);

            n = 9;
            pairVector[n].first = i;
            pairVector[n].second = INF_NLOS_SL.calculateLosses(distance2Dout, distance2Din, heightBS, heightUT, centerFrequency, h, W, shadowFading);
            data[n].push_back(pairVector[n]);

            n = 10;
            pairVector[n].first = i;
            pairVector[n].second = INF_NLOS_DL.calculateLosses(distance2Dout, distance2Din, heightBS, heightUT, centerFrequency, h, W, shadowFading);
            data[n].push_back(pairVector[n]);

            n = 11;
            pairVector[n].first = i;
            pairVector[n].second = INF_NLOS_SH.calculateLosses(distance2Dout, distance2Din, heightBS, heightUT, centerFrequency, h, W, shadowFading);
            data[n].push_back(pairVector[n]);

            n = 12;
            pairVector[n].first = i;
            pairVector[n].second = INF_NLOS_DH.calculateLosses(distance2Dout, distance2Din, heightBS, heightUT, centerFrequency, h, W, shadowFading);
            data[n].push_back(pairVector[n]);
        }
    }
    int minY = 0;
    int maxY = 150;
    chart.visualize2D(data, "Propagation Model test", series_name, minY, maxY);
}
