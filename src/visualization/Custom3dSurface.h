#pragma once

#include <QtDataVisualization/Q3DSurface>
#include <QtDataVisualization/QSurfaceDataProxy>
#include <QtDataVisualization/QHeightMapSurfaceDataProxy>
#include <QtDataVisualization/QSurface3DSeries>
#include <QtWidgets/QSlider>


class Custom3dSurface : public QObject
{
    Q_OBJECT
public:
    Custom3dSurface(QtDataVisualization::Q3DSurface *surface);
    ~Custom3dSurface();

    void enableSqrtSinModel(bool enable, QtDataVisualization::QSurface3DSeries*);
    void enableDataFromFile(bool enable);


    void setBlackToYellowGradient();
    void setGreenToRedGradient();
    void setBlueToRedGradient();

    void adjustXMin(int min);
    void adjustXMax(int max);
    void adjustZMin(int min);
    void adjustZMax(int max);

private:
    QtDataVisualization::Q3DSurface *graph_;
    QtDataVisualization::QSurface3DSeries *sqrtSinSeries_;
    QtDataVisualization::QSurfaceDataProxy *sqrtSinProxy_;

    float rangeMinX_;
    float rangeMinZ_;
    float stepX_;
    float stepZ_;
    int heightMapWidth_;
    int heightMapHeight_;

    void setAxisXRange(float min, float max);
    void setAxisZRange(float min, float max);
    void fillSqrtSinProxy();
    void fillFromFileCustom(QtDataVisualization::QSurfaceDataProxy* Proxy,int);
    void fillFromFile(QtDataVisualization::QSurfaceDataProxy* Proxy);
    void handleElementSelected(QtDataVisualization::QAbstract3DGraph::ElementType type);
    int checkBuildingID(QPoint);
};
