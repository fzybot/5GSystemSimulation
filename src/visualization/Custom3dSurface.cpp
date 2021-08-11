#include "Custom3dSurface.h"

#include <QtDataVisualization/QValue3DAxis>
#include <QtDataVisualization/Q3DTheme>
#include <QtGui/QImage>
#include <QtCore/qmath.h>
//#include "src/visualization/data/plotData/nskStoreysHeights.cpp"
//#include "src/visualization/data/plotData/scaleTest.cpp"
#include "src/visualization/data/plotData/interpolationNskStoreysHeights.cpp"
#include <algorithm>
#include <stdlib.h>
//#include <QWidgets>

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

    proxy_ = new QtDataVisualization::QSurfaceDataProxy();
    series_ = new QtDataVisualization::QSurface3DSeries(proxy_);

    setsCount_=2;
    sets_=new int[setsCount_];
    sets_[0]=2;
    sets_[1]=4;

    fillFromFile();
    enableModel();

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
    proxy_->resetArray(dataArray);
}

void Custom3dSurface::enableModel()
{
        series_->setDrawMode(QtDataVisualization::QSurface3DSeries::DrawSurface);
        series_->setFlatShadingEnabled(true);

        graph_->axisX()->setLabelFormat("%.10f");
        graph_->axisZ()->setLabelFormat("%.10f");
        graph_->axisX()->setRange(storeysHeights[0][1],storeysHeights[lonc-1][1]);
        graph_->axisY()->setRange(zMin_,zMax_);
        graph_->axisZ()->setRange(storeysHeights[0][0],storeysHeights[length-1][0]);

        graph_->axisX()->setLabelAutoRotation(30);
        graph_->axisY()->setLabelAutoRotation(90);
        graph_->axisZ()->setLabelAutoRotation(30);

        graph_->addSeries(series_);
        graph_->setShadowQuality(QtDataVisualization::QAbstract3DGraph::ShadowQualityNone);
        setBlueToRedGradient();

        // Reset range sliders for Sqrt&Sin
/*
        rangeMinX_ = lon[0];
        rangeMinZ_ = 50;
        stepX_ = (lon[length-1] - X[0]) / float(length - 1);
        stepZ_ = (50 - 0) / float(length - 1);
*/
}

void Custom3dSurface::fillFromFileCustom(int num)
{
    float stepX = (storeysHeights[lonc-1][1] - storeysHeights[0][1]) / float(sampleCountX - 1);
    float stepZ = (storeysHeights[length-1][0] - storeysHeights[0][0]) / float(sampleCountZ - 1);

    QtDataVisualization::QSurfaceDataArray *dataArray = new QtDataVisualization::QSurfaceDataArray;
    dataArray->reserve(sampleCountZ);

    for (int i = 0; i < sampleCountZ; i++) {
        QtDataVisualization::QSurfaceDataRow *newRow = new QtDataVisualization::QSurfaceDataRow(sampleCountX);
        float z = qMin(float(storeysHeights[length-1][0]), (i * stepZ + float(storeysHeights[0][0])));
        int index = 0;
        for (int j = 0; j < sampleCountX; j++) {
            float x = qMin(float(storeysHeights[lonc-1][1]), (j * stepX + float(storeysHeights[0][1])));
            float y=0;
            for (int c=0;c<setsCount_; ++c){
            if (storeysHeights[i*sampleCountX+j][3]==num){
                y +=storeysHeights[i*sampleCountX+j][sets_[c]];       //storeys + heights
            }
            else{
                if(setsCount_!=1){y = storeysHeights[i*sampleCountX+j][sets_[setsCount_-1]];}
            }
            }
            (*newRow)[index++].setPosition(QVector3D(x, y, z));
        }
        //qDebug() << "New row: " << newRow->size();
        *dataArray << newRow;
    }
    proxy_->resetArray(dataArray);
}

void Custom3dSurface::fillFromFile()
{
    float stepX = (storeysHeights[lonc-1][1] - storeysHeights[0][1]) / float(sampleCountX - 1);
    float stepZ = (storeysHeights[length-1][0] - storeysHeights[0][0]) / float(sampleCountZ - 1);

    QtDataVisualization::QSurfaceDataArray *dataArray = new QtDataVisualization::QSurfaceDataArray;
    dataArray->reserve(sampleCountZ);

    for (int i = 0; i < sampleCountZ; i++) {
        QtDataVisualization::QSurfaceDataRow *newRow = new QtDataVisualization::QSurfaceDataRow(sampleCountX);
        float z = qMin(float(storeysHeights[length-1][0]), (i * stepZ + float(storeysHeights[0][0])));
        int index = 0;
        for (int j = 0; j < sampleCountX; j++) {
            float x = qMin(float(storeysHeights[lonc-1][1]), (j * stepX + float(storeysHeights[0][1])));
            float y=0;
            for (int c=0;c<setsCount_; ++c){
                y+=storeysHeights[i*sampleCountX+j][sets_[c]];
            }
            (*newRow)[index++].setPosition(QVector3D(x, y, z));
        }
        *dataArray << newRow;
    }
    proxy_->resetArray(dataArray);
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
            qDebug()<<ID;
            graph_->removeSeries(series_);
            proxy_ = new QtDataVisualization::QSurfaceDataProxy();
            series_ = new QtDataVisualization::QSurface3DSeries(proxy_);
            fillFromFileCustom(ID);
            enableModel();
        }
    }
    else
    {
        graph_->removeSeries(series_);
        proxy_ = new QtDataVisualization::QSurfaceDataProxy();
        series_ = new QtDataVisualization::QSurface3DSeries(proxy_);
        fillFromFile();
        enableModel();
    }
}

int Custom3dSurface::checkBuildingID(QPoint point)
{
    return storeysHeights[point.x() * lonc + point.y()][3];
}

void Custom3dSurface::toggleItem()
{
    QObject* obj = QObject::sender();
    QCheckBox *checkBox=qobject_cast<QCheckBox *>(obj);
    if(checkBox->text()=="Height"){
        if(checkBox->checkState())
        {
            if(sets_!=NULL){
                delete[] sets_;
            }
            setsCount_=2;
            sets_= new int[setsCount_];
            sets_[0]=2;
            sets_[1]=4;

            zMin_ = 100;
            zMax_ = 200;
        }
        else
        {
            if(sets_!=NULL){
                delete[] sets_;
            }
            setsCount_=1;
            sets_= new int[setsCount_];
            sets_[0]=2;

            zMin_ = -50;
            zMax_ = 50;
        }
    }
}


