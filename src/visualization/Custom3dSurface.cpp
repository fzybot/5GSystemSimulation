#include "Custom3dSurface.h"

#include <QtDataVisualization/QValue3DAxis>
#include <QtDataVisualization/Q3DTheme>
#include <QtGui/QImage>
#include <QtCore/qmath.h>
#include "src/visualization/data/plotData/Novosibirsk_storeys_heights.cpp"

const int sampleCountX = lonc;
const int sampleCountZ = latc;
const int heightMapGridStepX = 6;
const int heightMapGridStepZ = 6;
const float sampleMin = -8.0f;
const float sampleMax = 8.0f;

Custom3dSurface::Custom3dSurface(QtDataVisualization::Q3DSurface *surface)
    :graph_(surface)
{
    graph_->setAxisX(new QtDataVisualization::QValue3DAxis);
    graph_->setAxisY(new QtDataVisualization::QValue3DAxis);
    graph_->setAxisZ(new QtDataVisualization::QValue3DAxis);

    sqrtSinProxy_ = new QtDataVisualization::QSurfaceDataProxy();
    sqrtSinSeries_ = new QtDataVisualization::QSurface3DSeries(sqrtSinProxy_);

    fillFromFile();
    enableSqrtSinModel(true);
}

Custom3dSurface::~Custom3dSurface()
{
    delete graph_;
}

void Custom3dSurface::fillSqrtSinProxy()
{
    float stepX = (sampleMax - sampleMin) / float(sampleCountX - 1);
    float stepZ = (sampleMax - sampleMin) / float(sampleCountZ - 1);

    QtDataVisualization::QSurfaceDataArray *dataArray = new QtDataVisualization::QSurfaceDataArray;
    dataArray->reserve(sampleCountZ);
    for (int i = 0; i < sampleCountZ; i++) {
        QtDataVisualization::QSurfaceDataRow *newRow = new QtDataVisualization::QSurfaceDataRow(sampleCountX);
        float z = qMin(sampleMax, (i * stepZ + sampleMin));
        int index = 0;
        for (int j = 0; j < sampleCountX; j++) {
            float x = qMin(sampleMax, (j * stepX + sampleMin));
            float R = qSqrt(z * z + x * x) + 0.01f;
            float y = (qSin(R) / R + 0.24f) * 1.61f;
            (*newRow)[index++].setPosition(QVector3D(x, y, z));
        }
        qDebug() << "New row: " << newRow->size();
        *dataArray << newRow;
    }
    sqrtSinProxy_->resetArray(dataArray);
}

void Custom3dSurface::enableSqrtSinModel(bool enable)
{
    if (enable) {
        sqrtSinSeries_->setDrawMode(QtDataVisualization::QSurface3DSeries::DrawSurfaceAndWireframe);
        sqrtSinSeries_->setFlatShadingEnabled(true);

        graph_->axisX()->setLabelFormat("%.2f");
        graph_->axisZ()->setLabelFormat("%.2f");
        graph_->axisX()->setRange(lon[0],lon[lonc-1]);
        graph_->axisY()->setRange(0,50);
        graph_->axisZ()->setRange(lat[0],lat[8910-1]);

        graph_->axisX()->setLabelAutoRotation(30);
        graph_->axisY()->setLabelAutoRotation(90);
        graph_->axisZ()->setLabelAutoRotation(30);

        graph_->addSeries(sqrtSinSeries_);

        // Reset range sliders for Sqrt&Sin
/*
        rangeMinX_ = lon[0];
        rangeMinZ_ = 50;
        stepX_ = (lon[8910-1] - X[0]) / float(8910 - 1);
        stepZ_ = (50 - 0) / float(8910 - 1);
*/
    }
}

void Custom3dSurface::fillFromFile()
{
    float stepX = (lon[lonc-1] - lon[0]) / float(sampleCountX - 1);
    float stepZ = (lat[8910-1] - lat[0]) / float(sampleCountZ - 1);

    QtDataVisualization::QSurfaceDataArray *dataArray = new QtDataVisualization::QSurfaceDataArray;
    dataArray->reserve(sampleCountZ);

    for (int i = 0; i < sampleCountZ; i++) {
        QtDataVisualization::QSurfaceDataRow *newRow = new QtDataVisualization::QSurfaceDataRow(sampleCountX);
        float z = qMin(float(lat[8910-1]), (i * stepZ + float(lat[0])));
        int index = 0;
        for (int j = 0; j < sampleCountX; j++) {
            float x = qMin(float(lon[lonc-1]), (j * stepX + float(lon[0])));
            float y = storeys[i*sampleCountX+j];
            (*newRow)[index++].setPosition(QVector3D(x, y, z));
        }
        qDebug() << "New row: " << newRow->size();
        *dataArray << newRow;
    }
    sqrtSinProxy_->resetArray(dataArray);

}

