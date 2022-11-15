#include "src/tests/HeatmapModelTest.h"

void HeatmapModelTest::setCell(Cell* cell)
{
    cell_ = cell;
}

float HeatmapModelTest::calculateAngle(int x, int y)
{
    float dy = (y - cell_->mobility_->getPosition()->getCoordinateY());
    float dx = (x - cell_->mobility_->getPosition()->getCoordinateX());
    float angle = 0;

    angle = atan2(dy, dx);

    return angle;
}
float HeatmapModelTest::convertRadToDeg(float rad)
{
    float deg = rad * 180 / M_PI;
    return deg;
}

// -->> поправить gains
float HeatmapModelTest::calculateGain(float azimuth, float elevation)
{
    float gain = 0, resultGain = 0;
    for(int i = 0; i < cell_->getPhyEntity()->getAntennaArray()->getBeamContainer().size(); i++){
        for(int j = 0; j < cell_->getPhyEntity()->getAntennaArray()->getBeamContainer()[0].size(); j++){
            gain = cell_->getPhyEntity()->getAntennaArray()->gainPerBeamIndex(i, j, elevation, azimuth);
            resultGain += gain;
         }
    }

    return resultGain;
}

void HeatmapModelTest::calculateHeatmap3DDDA()
{
//	int x= cell_.getPhyEntity()->getAntennaArray()->getBeamContainer()[0][0];
    int x = cell_->getMobilityModel()->getPosition()->getCoordinateX(),
        y = cell_->getMobilityModel()->getPosition()->getCoordinateY();

    for(int dirX=0; dirX<lonc; ++dirX){
        for(int dirY=0; dirY<latc; ++dirY){
            if((dirX!=0 && (dirY==0 || dirY==latc-1)) ||
                    (dirY!=0 && (dirX==0 || dirX==lonc-1))){
            int L = qMax(fabs(dirX - x), fabs(dirY - y));
            L++;
            double stepX = ((double)(dirX - x))/L;
            double stepY = ((double)(dirY - y))/L;

            double startX = x;
            double startY = y;
            int kIn=0;
            CartesianCoordinates *point = new CartesianCoordinates(0, 0, heightUT);
            CartesianCoordinates *startPoint = new CartesianCoordinates(x,y, BaseStation.getCoordinateZ());
            QVector<CartesianCoordinates> slice;
            slice.push_back(BaseStation);

            for(int k=1; k<=L; ++k){
                int i = qRound(startX + (k*stepX));
                int j = qRound(startY + (k*stepY));
                if(i<0 || i>=lonc || j<0 || j>=latc) break;
                double pathloss=0;
                point->setCoordinateX(i);
                point->setCoordinateY(j);
                slice.push_back(*point);

                if((data)[i][j]!=0) continue;
                float elevation = 0;
                kIn = isLOSDDA(slice);
                double groundBS = 0;
                double groundUT = 0;
                double groundDelta = 0;
                if(heightUsage){
                    groundBS = storeysHeights[(int)(BaseStation.getCoordinateY()) * lonc
                                            + (int)(BaseStation.getCoordinateX())][4];
                    groundUT = storeysHeights[(int)(slice.back().getCoordinateY()) * lonc
                                            + (int)(slice.back().getCoordinateX())][4];
                    groundDelta = groundBS - groundUT;
                }

                CartesianCoordinates base = CartesianCoordinates(x, y, 0);
                CartesianCoordinates distination = CartesianCoordinates(i, j, 0);
                float azimuth  = base.calculateAngleToRemote(&base, &distination);
                //float gain = cell_->getPhyEntity()->getAntennaArray()->getBeamContainer()[0][0]->calculateAntGain(0, azimuth);
                float gain = calculateGain(azimuth, elevation);
                if(kIn == 0)
                {
                        pathloss = UMa_LOS(startPoint->calculateDistance2D(point), 0,
                                           BaseStation.getCoordinateZ() + groundDelta,
                                           heightUT, centerFrequency, h,  W, shadowFading);
                }
                else
                {
                    pathloss = UMa_NLOS(startPoint->calculateDistance2D(point) - kIn*pixelToMeter, kIn*pixelToMeter,
                                        BaseStation.getCoordinateZ() + groundDelta,
                                        heightUT, centerFrequency, h,  W, shadowFading);
                }

                if(pathloss == -1){
                    (data)[i][j] = 20000;
                }
                else{
                    double rsrp = BSPower + gain - pathloss - 10*log10(50*1000/15);
                    (data)[i][j]= rsrp;
                }

            }
            }
        }
    }

}

void HeatmapModelTest::calculateHeatmap()
{
    clock_t start, end;
    createData();

    start = clock();
    calculateHeatmap3DDDA();
    end = clock();

    qDebug()<<"heatmap calculation TIME = "<<(end - start)/CLOCKS_PER_SEC;

    qDebug()<<"QImage was saved - " << createImage();
}

void HeatmapModelTest::changeSettings(void* stngs)
{
    SettingsTemplate* settings = (SettingsTemplate*)stngs;
    setBSPower(settings->cellTxPower);
    setAntennaGain(settings->cellAntennaGain);
    setHeightUsage(settings->heightUsage);
    setBuildingsUsage(settings->buildingsUsage);
}
