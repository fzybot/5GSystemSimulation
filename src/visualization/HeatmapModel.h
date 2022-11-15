#ifndef HEATMAPMODEL_H
#define HEATMAPMODEL_H

#include <QObject>
#include "src/visualization/data/plotData/interpolationNskStoreysHeights.cpp"
#include "src/core/CartesianCoordinates.h"
#include "src/protocols/phy/Channel/propagationModels.h"
#include <QtMath>
#include <QDebug>
#include <QVector>
#include <time.h>
#include <QImage>
#include <QCoreApplication>
#include "src/visualization/settingsTemplate.h"

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
    void setHeightUsage(int heightUsage);
    void setBuildingsUsage(int buildingsUsage);

    void createData();

protected:
    double centerFrequency;
    double h;
    double W;                   //[m]
    double shadowFading;
    double heightUT;            //[m]
    CartesianCoordinates BaseStation;
    QVector<QVector<double>> data;
    double BSPower;
    double AntennaGain;
    double pixelToMeter;
    double storeysToHeight;

    int heightUsage;
    int buildingsUsage;

    double getAvgBuildingHeight();
    bool createImage();
    int isLOSDDA(QVector <CartesianCoordinates> slice);

    QRgb signalStrengthToColor(double signalStrength);
    void calculateHeatmap3DDDA();

public slots:
    void calculateHeatmap();
    void changeSettings(void*);
};

#endif // HEATMAPMODEL_H
