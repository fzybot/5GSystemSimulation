#ifndef HEATMAPMODEL_H
#define HEATMAPMODEL_H

#include <QObject>
#include "src/visualization/data/plotData/interpolationNskStoreysHeights.cpp"
#include "src/core/CartesianCoordinates.h"
#include "src/protocols/phy/propagationModels.h"
#include <QtMath>
#include <QDebug>
#include <vector>
#include <time.h>
#include <QImage>
#include <QCoreApplication>

using namespace std;

class HeatmapModel : public QObject
{
    Q_OBJECT
public:
    HeatmapModel();

    void setBaseStation(CartesianCoordinates BS);
    void setCenterFrequency(double frequency);
    void setAvgBuildingHeight(double avgBuildingHeight);
    void setAvgStreetWidth(double avgStreetWidth);
    void setShadowFading(double shadowFading);
    void setUEHeight(double ueHeight);

    void setBSPower(double power);
    void setAntennaGain(double gain);
    void setPixelToMeter(double ptm);
    void setHeightOfStorey(double heightOfStorey);

    void createData();

protected:
    double centerFrequency = 2.4;
    double h;
    double W = 46;              //[m]
    double shadowFading = 4;
    double heightUT = 2;        //[m]
    CartesianCoordinates BaseStation;
    vector<vector<double>> data;
    double BSPower = 43;
    double AntennaGain = 12;
    double pixelToMeter = 1.25;
    double storeysToHeight = 2.7;

    double getAvgBuildingHeight();
    bool createImage();
    int isLOSDDA(vector <CartesianCoordinates> slice);

    QRgb signalStrengthToColor(double signalStrength);
    void calculateHeatmap3DDDA();

public slots:
    void calculateHeatmap();
    void changeSettings(int*);
};

#endif // HEATMAPMODEL_H
