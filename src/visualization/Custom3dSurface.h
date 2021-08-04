#pragma once

#include <QtDataVisualization/Q3DSurface>
#include <QtDataVisualization/QSurfaceDataProxy>
#include <QtDataVisualization/QHeightMapSurfaceDataProxy>
#include <QtDataVisualization/QSurface3DSeries>
#include <QtWidgets/QSlider>
#include <QtWidgets>
//#include <stdarg.h>

class Custom3dSurface : public QObject
{
    Q_OBJECT
public:
    Custom3dSurface(QtDataVisualization::Q3DSurface *surface);
    ~Custom3dSurface();

    void enableModel(bool enable);
    //void enableDataFromFile(bool enable);


    void setBlackToYellowGradient();
    void setGreenToRedGradient();
    void setBlueToRedGradient();

    void adjustXMin(int min);
    void adjustXMax(int max);
    void adjustZMin(int min);
    void adjustZMax(int max);

    void toggleItem();
    void handleElementSelected(QtDataVisualization::QAbstract3DGraph::ElementType type);

private:
    QtDataVisualization::Q3DSurface *graph_;
    QtDataVisualization::QSurface3DSeries *series_;
    QtDataVisualization::QSurfaceDataProxy *proxy_;

    float rangeMinX_;
    float rangeMinZ_;
    float stepX_;
    float stepZ_;
    int heightMapWidth_;
    int heightMapHeight_;
    int* sets_=NULL;
    int setsCount_;

    void setAxisXRange(float min, float max);
    void setAxisZRange(float min, float max);
    void fillSqrtSinProxy();
    void fillFromFileCustom(int num);
    void fillFromFile();
    int checkBuildingID(QPoint);
};
