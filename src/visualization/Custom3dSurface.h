#pragma once

#include <QtDataVisualization/Q3DSurface>
#include <QtDataVisualization/QSurfaceDataProxy>
#include <QtDataVisualization/QHeightMapSurfaceDataProxy>
#include <QtDataVisualization/QSurface3DSeries>
#include <QtWidgets/QSlider>

//using namespace QtDataVisualization;

class Custom3dSurface : public QObject
{
    Q_OBJECT

public:
    Custom3dSurface(QtDataVisualization::Q3DSurface *surface);
    ~Custom3dSurface();

    void enableSqrtSinModel(bool enable);

    void setBlackToYellowGradient();
    void setGreenToRedGradient();

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




};

