#include "Custom3dSurface.h"

#include <QtDataVisualization/QValue3DAxis>
#include <QtDataVisualization/Q3DTheme>
#include <QtGui/QImage>
#include <QtCore/qmath.h>
#include "src/visualization/data/plotData/nskStoreysHeights.cpp"
#include <algorithm>
#include <stdlib.h>

#include <QtDataVisualization/QCustom3DItem>
#include <QtDataVisualization/QCustom3DLabel>

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

    QtDataVisualization::QSurfaceDataProxy* Proxy = new QtDataVisualization::QSurfaceDataProxy();
    QtDataVisualization::QSurface3DSeries* Series = new QtDataVisualization::QSurface3DSeries(Proxy);

    fillFromFile(Proxy);
    enableSqrtSinModel(true,Series);

    setBlueToRedGradient();

    connect(graph_, &QtDataVisualization::QAbstract3DGraph::selectedElementChanged,
            this, &Custom3dSurface::handleElementSelected);

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

void Custom3dSurface::enableSqrtSinModel(bool enable,QtDataVisualization::QSurface3DSeries* Series)
{
    if (enable) {
        Series->setDrawMode(QtDataVisualization::QSurface3DSeries::DrawSurfaceAndWireframe);
        Series->setFlatShadingEnabled(true);

        graph_->axisX()->setLabelFormat("%.2f");
        graph_->axisZ()->setLabelFormat("%.2f");
        graph_->axisX()->setRange(storeysHeights[0][1],storeysHeights[lonc-1][1]);
        graph_->axisY()->setRange(100,180);
        graph_->axisZ()->setRange(storeysHeights[0][0],storeysHeights[8910-1][0]);

        graph_->axisX()->setLabelAutoRotation(30);
        graph_->axisY()->setLabelAutoRotation(90);
        graph_->axisZ()->setLabelAutoRotation(30);

        graph_->addSeries(Series);
        graph_->setShadowQuality(QtDataVisualization::QAbstract3DGraph::ShadowQualityNone);

        // Reset range sliders for Sqrt&Sin
/*
        rangeMinX_ = lon[0];
        rangeMinZ_ = 50;
        stepX_ = (lon[8910-1] - X[0]) / float(8910 - 1);
        stepZ_ = (50 - 0) / float(8910 - 1);
*/
    }
}

void Custom3dSurface::fillFromFileCustom(QtDataVisualization::QSurfaceDataProxy* Proxy, int num)
{
    float stepX = (storeysHeights[lonc-1][1] - storeysHeights[0][1]) / float(sampleCountX - 1);
    float stepZ = (storeysHeights[8910-1][0] - storeysHeights[0][0]) / float(sampleCountZ - 1);

    QtDataVisualization::QSurfaceDataArray *dataArray = new QtDataVisualization::QSurfaceDataArray;
    dataArray->reserve(sampleCountZ);

    for (int i = 0; i < sampleCountZ; i++) {
        QtDataVisualization::QSurfaceDataRow *newRow = new QtDataVisualization::QSurfaceDataRow(sampleCountX);
        float z = qMin(float(storeysHeights[8910-1][0]), (i * stepZ + float(storeysHeights[0][0])));
        int index = 0;
        for (int j = 0; j < sampleCountX; j++) {
            float x = qMin(float(storeysHeights[lonc-1][1]), (j * stepX + float(storeysHeights[0][1])));
            float y=0;
            if (storeysHeights[i*sampleCountX+j][3]==num){
                y = (storeysHeights[i*sampleCountX+j][2] + storeysHeights[i*sampleCountX+j][4]);        //storeys + heights
            }
            else{
                y = storeysHeights[i*sampleCountX+j][4];
            }
            (*newRow)[index++].setPosition(QVector3D(x, y, z));
        }
        //qDebug() << "New row: " << newRow->size();
        *dataArray << newRow;
    }
    Proxy->resetArray(dataArray);
}

void Custom3dSurface::fillFromFile(QtDataVisualization::QSurfaceDataProxy* Proxy)
{
    float stepX = (storeysHeights[lonc-1][1] - storeysHeights[0][1]) / float(sampleCountX - 1);
    float stepZ = (storeysHeights[8910-1][0] - storeysHeights[0][0]) / float(sampleCountZ - 1);

    QtDataVisualization::QSurfaceDataArray *dataArray = new QtDataVisualization::QSurfaceDataArray;
    dataArray->reserve(sampleCountZ);

    for (int i = 0; i < sampleCountZ; i++) {
        QtDataVisualization::QSurfaceDataRow *newRow = new QtDataVisualization::QSurfaceDataRow(sampleCountX);
        float z = qMin(float(storeysHeights[8910-1][0]), (i * stepZ + float(storeysHeights[0][0])));
        int index = 0;
        for (int j = 0; j < sampleCountX; j++) {
            float x = qMin(float(storeysHeights[lonc-1][1]), (j * stepX + float(storeysHeights[0][1])));
            float y=(storeysHeights[i*sampleCountX+j][2] + storeysHeights[i*sampleCountX+j][4]);
            (*newRow)[index++].setPosition(QVector3D(x, y, z));
        }
        //qDebug() << "New row: " << newRow->size();
        *dataArray << newRow;
    }
    Proxy->resetArray(dataArray);
}

void Custom3dSurface::setBlueToRedGradient()
{
    QLinearGradient gr;
    gr.setColorAt(0.0, Qt::blue);
    gr.setColorAt(0.5, Qt::green);
    gr.setColorAt(1.0, Qt::red);

    graph_->seriesList().at(0)->setBaseGradient(gr);
    graph_->seriesList().at(0)->setColorStyle(QtDataVisualization::Q3DTheme::ColorStyleRangeGradient);

}

void Custom3dSurface::handleElementSelected(QtDataVisualization::QAbstract3DGraph::ElementType type)
{
    if (type == QtDataVisualization::QAbstract3DGraph::ElementSeries){
        QtDataVisualization::QSurface3DSeries *series = graph_->selectedSeries();
        if(series){
            QPoint point = series->selectedPoint();
            int ID = this->checkBuildingID(point);
            QtDataVisualization::QSurfaceDataProxy* Proxy = new QtDataVisualization::QSurfaceDataProxy();
            graph_->seriesList().at(0)->setDataProxy(Proxy);
            fillFromFileCustom(Proxy,ID);
        }
    }
    else
    {
        QtDataVisualization::QSurfaceDataProxy* Proxy = new QtDataVisualization::QSurfaceDataProxy();
        graph_->seriesList().at(0)->setDataProxy(Proxy);
        fillFromFile(Proxy);
    }
}

int Custom3dSurface::checkBuildingID(QPoint point)
{
    return storeysHeights[point.x() * lonc + point.y()][3];
}
