#include "Custom3dSurface.h"

#include <QtDataVisualization/QValue3DAxis>
#include <QtDataVisualization/Q3DTheme>
#include <QtDataVisualization/QCustom3DItem>
#include <QtDataVisualization/QCustom3DLabel>
#include <QtGui/QImage>
#include <QtCore/qmath.h>
#include <algorithm>
#include <stdlib.h>

//#include "src/visualization/data/plotData/nskStoreysHeights.cpp"
//#include "src/visualization/data/plotData/scaleTest.cpp"
//#include "src/visualization/data/plotData/interpolationNskStoreysHeights.cpp"
//#include "src/visualization/data/plotData/interpolationTest.cpp"

//#include <QWidgets>

//#include "src/scenarios/testModel.h"

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

    initializeHeatmap();

    setsCount_=2;
    sets_=new int[setsCount_];
    sets_[0]=2;
    sets_[1]=4;

    fillFromFile();
    enableModel();

    connect(graph_, &QtDataVisualization::QAbstract3DGraph::selectedElementChanged,
            this, &Custom3dSurface::handleElementSelected);

    //connect(series_, &QtDataVisualization::QSurface3DSeries::selectedPointChanged,
    //                     this, &Custom3dSurface::handlePositionChange);
}

Custom3dSurface::Custom3dSurface(QtDataVisualization::Q3DSurface *surface, int test)
    :graph_(surface)
{
    graph_->setAxisX(new QtDataVisualization::QValue3DAxis);
    graph_->setAxisY(new QtDataVisualization::QValue3DAxis);
    graph_->setAxisZ(new QtDataVisualization::QValue3DAxis);

    proxy_ = new QtDataVisualization::QSurfaceDataProxy();
    series_ = new QtDataVisualization::QSurface3DSeries(proxy_);

    fillSqrtSinProxy();
    // QLinearGradient gr;
    // gr.setColorAt(0.0, Qt::blue);
    // gr.setColorAt(0.5, Qt::green);
    // gr.setColorAt(1.0, Qt::red);

    // series_->setBaseGradient(gr);
    // series_->setColorStyle(QtDataVisualization::Q3DTheme::ColorStyleRangeGradient);
    
}

Custom3dSurface::Custom3dSurface(QtDataVisualization::Q3DSurface *surface, QtDataVisualization::QSurfaceDataArray *dataArray)
    :graph_(surface)
{
    graph_->setAxisX(new QtDataVisualization::QValue3DAxis);
    graph_->setAxisY(new QtDataVisualization::QValue3DAxis);
    graph_->setAxisZ(new QtDataVisualization::QValue3DAxis);

    graph_->axisX()->setLabelFormat("%.10f");
    graph_->axisZ()->setLabelFormat("%.10f");
    graph_->axisX()->setRange(-180,180);
    graph_->axisY()->setRange(-90, 90);
    graph_->axisZ()->setRange(-100, 100);

    proxy_ = new QtDataVisualization::QSurfaceDataProxy();
    series_ = new QtDataVisualization::QSurface3DSeries(proxy_);

    proxy_->resetArray(dataArray);
    graph_->addSeries(series_);
}

Custom3dSurface::~Custom3dSurface()
{
    delete graph_;
}

void Custom3dSurface::fillSqrtSinProxy()
{
    int sampleCountXLocal = 100;
    int sampleCountZLocal = 100;
    float stepX = (sampleMax - sampleMin) / float(sampleCountXLocal - 1);
    float stepZ = (sampleMax - sampleMin) / float(sampleCountZLocal - 1);

    QtDataVisualization::QSurfaceDataArray *dataArray = new QtDataVisualization::QSurfaceDataArray;
    dataArray->reserve(sampleCountZLocal);
    for (int i = 0; i < sampleCountZLocal; i++) {
        QtDataVisualization::QSurfaceDataRow *newRow = new QtDataVisualization::QSurfaceDataRow(sampleCountXLocal);
        float z = qMin(sampleMax, (i * stepZ + sampleMin));
        int index = 0;
        for (int j = 0; j < sampleCountXLocal; j++) {
            float x = qMin(sampleMax, (j * stepX + sampleMin));
            float R = qSqrt(z * z + x * x) + 0.01f;
            float y = (qSin(R) / R + 0.24f) * 1.61f;
            (*newRow)[index++].setPosition(QVector3D(x, y, z));
        }
        //qDebug() << "New row: " << newRow->size();
        *dataArray << newRow;
    }
    proxy_->resetArray(dataArray);

    graph_->addSeries(series_);
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
        setBlueToRedGradient(series_);


        // Reset range sliders for Sqrt&Sin
/*
        rangeMinX_ = lon[0];
        rangeMinZ_ = 50;
        stepX_ = (lon[length-1] - X[0]) / float(length - 1);
        stepZ_ = (50 - 0) / float(length - 1);
*/
}

void Custom3dSurface::initializeHeatmap()
{
    heatmapModel_ = new HeatmapModelTest;
	cell_ = new Cell;

    Mobility* mob = new Mobility();
    mob->setModel(Mobility::Model::CONSTANT_POSITION);
    CartesianCoordinates* cor = new CartesianCoordinates(851, 230, 60);
    mob->setPosition(cor);
    cell_->setMobilityModel(mob);
    int sizeX = 1 , sizeY = 1;
    float azimuth = 0, elevation = 0;
    float beamWidth = 0;
    float sectorWidth = 0;
    cell_->getPhyEntity()->addAntennaArray(AntennaArray::AntennaType::ANTENNA_TYPE_3GPP_CUSTOM,
                                           sizeX, sizeY, azimuth,
                                          elevation, beamWidth,
                                          sectorWidth);
    cell_->getPhyEntity()->getAntennaArray()->configAntennaGrid(sizeX, sizeY);
    cell_->getPhyEntity()->getAntennaArray()->setBeams(0, 0, 10, 45);
    cell_->getPhyEntity()->getAntennaArray()->setDefaultGain(12);
    heatmapModel_->setCell(cell_);
    //heatmapModel_->setBaseStation(CartesianCoordinates(851, 230, 60));
	
    connect(this, &Custom3dSurface::settingsChanged, heatmapModel_, &HeatmapModelTest::changeSettings);
    connect(this, &Custom3dSurface::calculateModelSignal, heatmapModel_, &HeatmapModelTest::calculateHeatmap);
}

void Custom3dSurface::enableHeatmap(bool check)
{
    if(check){
        QString path = QCoreApplication::applicationDirPath();
        QString texturePath = QString("/pixelMap.bmp");
        path.append(texturePath);
        series_->setTextureFile(path);
    }
    else{
        QImage empty(0,0,QImage::Format_RGB32);
        series_->setTexture(empty);
    }
}

void Custom3dSurface::enableCityPic(bool check)
{
    if(check){
        series_->setTextureFile(":/images/cityPic.bmp");
    }
    else{
        QImage empty(0,0,QImage::Format_RGB32);
        series_->setTexture(empty);
    }
}

void Custom3dSurface::calculateModel()
{
    emit calculateModelSignal();
    QImage empty(0,0,QImage::Format_RGB32);
    series_->setTexture(empty);
    QString path = QCoreApplication::applicationDirPath();
    QString texturePath = QString("/pixelMap.bmp");
    path.append(texturePath);
    series_->setTextureFile(path);
}

void Custom3dSurface::changeSettings(void* settings)
{
    emit settingsChanged(settings);
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
                if(sets_[c]==2)y +=storeysHeights[i*sampleCountX+j][sets_[c]]*2.7;  //storeys + heights
                else{
                    y+=storeysHeights[i*sampleCountX+j][sets_[c]];
                }
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
                if(sets_[c]==2){
                    y+=storeysHeights[i*sampleCountX+j][sets_[c]]*2.7;
                }
                else{
                    y+=storeysHeights[i*sampleCountX+j][sets_[c]];
                }
            }
            (*newRow)[index++].setPosition(QVector3D(x, y, z));
        }
        *dataArray << newRow;
    }
    proxy_->resetArray(dataArray);
}

void Custom3dSurface::setBlueToRedGradient(QtDataVisualization::QSurface3DSeries* series)
{
    QLinearGradient gr;
    gr.setColorAt(0.0, Qt::blue);
    gr.setColorAt(0.5, Qt::green);
    gr.setColorAt(1.0, Qt::red);

    series->setBaseGradient(gr);
    series->setColorStyle(QtDataVisualization::Q3DTheme::ColorStyleRangeGradient);
}

void Custom3dSurface::setGrayGradient(QtDataVisualization::QSurface3DSeries* series)
{
    QLinearGradient gr;
    gr.setColorAt(0.0, Qt::gray);
    gr.setColorAt(1.0, Qt::gray);

    series->setBaseGradient(gr);
    series->setColorStyle(QtDataVisualization::Q3DTheme::ColorStyleRangeGradient);
}

void Custom3dSurface::handleElementSelected(QtDataVisualization::QAbstract3DGraph::ElementType type)
{
    if (type == QtDataVisualization::QAbstract3DGraph::ElementSeries){
        QtDataVisualization::QSurface3DSeries *series = graph_->selectedSeries();
        if(series){
            QPoint point = series->selectedPoint();
            int ID = this->checkBuildingID(point);
            qDebug()<<"ID = "<<ID<<"x = "<<point.x() << "y = "<<point.y();
            //graph_->removeSeries(series_);
            //proxy_ = new QtDataVisualization::QSurfaceDataProxy();
            //series_ = new QtDataVisualization::QSurface3DSeries(proxy_);
            fillFromFileCustom(ID);
            enableModel();
        }
    }
    else
    {
        //graph_->removeSeries(series_);
        //proxy_ = new QtDataVisualization::QSurfaceDataProxy();
        //series_ = new QtDataVisualization::QSurface3DSeries(proxy_);
        fillFromFile();
        enableModel();
    }
}

int Custom3dSurface::checkBuildingID(QPoint point)
{
    return storeysHeights[point.x() * lonc + point.y()][3];
}

void Custom3dSurface::toggleCheckBoxItem()
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

            zMin_ = 0;//100
            zMax_ = 300;//200
        }
        else
        {
            if(sets_!=NULL){
                delete[] sets_;
            }
            setsCount_=1;
            sets_= new int[setsCount_];
            sets_[0]=2;

            zMin_ = -150;//-50
            zMax_ = 150;//50
        }
    }
}

void Custom3dSurface::toggleRadioButtonItem()
{
    QObject* obj = QObject::sender();
    QRadioButton *radioButton=qobject_cast<QRadioButton *>(obj);

    if(radioButton->text()=="Heatmap"){
        if(radioButton->isChecked()){
            enableHeatmap(true);
        }
    }
    if(radioButton->text()=="City picture"){
        if(radioButton->isChecked()){
            enableCityPic(true);
        }
    }
    if(radioButton->text()=="Heightmap"){
        if(radioButton->isChecked()){
            enableCityPic(false);
        }
    }

}

void Custom3dSurface::handlePositionChange(const QPoint &position)
{
    //m_position = position;
    qDebug()<<graph_->seriesList().length();
    qDebug()<<position;
    qDebug()<<graph_->seriesList().length();

    if (position == QtDataVisualization::QSurface3DSeries::invalidSelectionPosition()) {
        highlightSeries_->setVisible(false);

        return;
    }

    int halfWidth = 100 / 2;
    int halfHeight = 100 / 2;

    int startX = position.y() - halfWidth;
    if (startX < 0 )
        startX = 0;
    int endX = position.y() + halfWidth;
    if (endX > ((graph_->seriesList().at(0)->dataProxy()->array()->at(0)->size())- 1))
        endX = (graph_->seriesList().at(0)->dataProxy()->array()->at(0)->size()) - 1;
    int startZ = position.x() - halfHeight;
    if (startZ < 0 )
        startZ = 0;
    int endZ = position.x() + halfHeight;
    if (endZ > (graph_->seriesList().at(0)->dataProxy()->array()->size() - 1))
        endZ = graph_->seriesList().at(0)->dataProxy()->array()->size() - 1;

    QtDataVisualization::QSurfaceDataProxy *srcProxy = proxy_;
    const QtDataVisualization::QSurfaceDataArray &srcArray = *srcProxy->array();

    QtDataVisualization::QSurfaceDataArray *dataArray = new QtDataVisualization::QSurfaceDataArray;
    dataArray->reserve(endZ - startZ);
    for (int i = startZ; i < endZ; i++) {
        QtDataVisualization::QSurfaceDataRow *newRow = new QtDataVisualization::QSurfaceDataRow(endX - startX);
        QtDataVisualization::QSurfaceDataRow *srcRow = srcArray.at(i);
        for (int j = startX, p = 0; j < endX; j++, p++) {
            QVector3D pos = srcRow->at(j).position();
            (*newRow)[p].setPosition(QVector3D(pos.x(), pos.y() + 0.1f, pos.z()));
        }
        *dataArray << newRow;
    }

    highlightSeries_->dataProxy()->resetArray(dataArray);
    highlightSeries_->setVisible(true);
}

