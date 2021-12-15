#pragma once

#include <QObject>
#include <QWidget>
#include <QVector>
#include <QtDataVisualization/Q3DSurface>
#include <QtDataVisualization/QSurfaceDataProxy>
#include <QtDataVisualization/QHeightMapSurfaceDataProxy>
#include <QtDataVisualization/QSurface3DSeries>

class Custom3dSurface;

class Chartable
{
protected:
    Custom3dSurface* surface_;
    QtDataVisualization::QSurfaceDataArray *dataArray3d_;
    QtDataVisualization::QSurfaceDataArray *dataArray2d_;
public:
    Chartable();

    void visualize3D();
    void visualize2D(float elevation);
};

