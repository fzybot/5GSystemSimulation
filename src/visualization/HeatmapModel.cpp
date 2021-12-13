#include "HeatmapModel.h"

HeatmapModel::HeatmapModel()
{
    //default
    setCenterFrequency(2.4);
    setAvgBuildingHeight(getAvgBuildingHeight());
    setAvgStreetWidth(46);
    setShadowFading(4);
    setUEHeight(2);
    setBSPower(43);
    setAntennaGain(12);
    setPixelToMeter(1.25);
    setHeightOfStorey(2.7);
    setHeightUsage(true);
    setBuildingsUsage(true);
    setSavePicName("pixelMap.bmp");
}

void HeatmapModel::setBaseStation(CartesianCoordinates BS)
{
    BaseStation.setCoordinateX(BS.getCoordinateX());
    BaseStation.setCoordinateY(BS.getCoordinateY());
    BaseStation.setCoordinateZ(BS.getCoordinateZ());
}

void HeatmapModel::setCenterFrequency(double frequency)
{
    centerFrequency = frequency;
}

void HeatmapModel::setBand(int band)
{
    switch (band){
        case 0:
        setCenterFrequency(0);
        break;
        case 1:
        setCenterFrequency(1.92);
        break;
        case 3:
        setCenterFrequency(1.71);
        break;
        case 7:
        setCenterFrequency(2.5);
        break;
        case 8:
        setCenterFrequency(0.88);
        break;
        case 20:
        setCenterFrequency(0.832);
        break;
        case 25:
        setCenterFrequency(1.85);
        break;
        case 30:
        setCenterFrequency(2.305);
        break;
        case 41:
        setCenterFrequency(2.496);
        break;
        case 79:
        setCenterFrequency(4.4);
        break;
        case 257:
        setCenterFrequency(29.5);
        break;
    }
}

void HeatmapModel::setAvgBuildingHeight(double height)
{
    h = height;
}

void HeatmapModel::setAvgStreetWidth(double width)
{
    W = width;
}

void HeatmapModel::setShadowFading(double fading)
{
    shadowFading = fading;
}

void HeatmapModel::setUEHeight(double height)
{
    heightUT = height;
}

void HeatmapModel::setBSPower(double power)
{
    BSPower = power;
}

void HeatmapModel::setAntennaGain(double gain)
{
    AntennaGain = gain;
}

void HeatmapModel::setPixelToMeter(double ptm)
{
    pixelToMeter = ptm;
}

void HeatmapModel::setHeightOfStorey(double height)
{
    storeysToHeight = height;
}

void HeatmapModel::setHeightUsage(int usage)
{
    heightUsage = usage;
}

void HeatmapModel::setBuildingsUsage(int usage)
{
    buildingsUsage = usage;
}

void HeatmapModel::setSavePicName(QString name)
{
    picName = name;
}

void HeatmapModel::createData()
{
     data = vector <vector <double>>(lonc, vector <double> (latc));

    for (int i = 0; i < lonc; i++)
        for (int j = 0; j < latc; j++)
        {
            data[i][j] = 0;
        }
}

double HeatmapModel::getAvgBuildingHeight()
{
    double sum = 0;
    int count = 0;

    for(int i=0;i<length;++i){
        if(storeysHeights[i][3] > count){
            count = storeysHeights[i][3];
        }
    }
    qDebug()<<"buildings count =" << count;


    int i = 0;
    int num = 0;
    for(num=2; num<count; ++num){
        for(i=0; i<length; ++i){
            if(storeysHeights[i][3]==num){
                sum += storeysHeights[i][2] * storeysToHeight;
                i=length+1;
            }
        }
    }
    qDebug()<<"SUM = " << sum;
    return (sum/count);
}

bool HeatmapModel::createImage()
{
    QImage image(lonc, latc, QImage::Format_RGB32);
    image.fill(Qt::black);

    for(int i=0; i<lonc;++i){
        for(int j=0;j<latc;++j){
            double signalStrength = data[i][j];
            if(signalStrength!=20000){
                image.setPixel(i, latc - j - 1, signalStrengthToColor(signalStrength));
            }
            else{
                image.setPixel(i, latc - j - 1, qRgba(0,0,0,255));
            }
        }
    }

    QString path = QCoreApplication::applicationDirPath();
    QString texturePath = QString("/" + picName);
    path.append(texturePath);

    return image.save(path, "BMP", 100);
}

int HeatmapModel::isLOSDDA(vector<CartesianCoordinates> slice)
{
    int length = slice.size();

    double groundBS = 0;
    double groundUT = 0;

    if(heightUsage){
        groundUT = storeysHeights[(int)(slice.back().getCoordinateY()) * lonc
                + (int)(slice.back().getCoordinateX())][4];
        groundBS = storeysHeights[(int)(slice.front().getCoordinateY()) * lonc
                + (int)(slice.front().getCoordinateX())][4];
    }

    int L = qMax(fabs(slice.size()), fabs(slice.back().getCoordinateZ() + groundUT -
                                          (slice.front().getCoordinateZ() + groundBS)));
    L++;
    double stepX = ((double)(slice.size()))/L;
    double stepY = ((double)((slice.back().getCoordinateZ() + groundUT) -
                             (slice.front().getCoordinateZ() + groundBS)))/L;

    double startX = 0;
    double startY = slice.front().getCoordinateZ() + groundBS;

    int kIn = 0;

    int prevI = 0;

    double buildingHeight = 0;
    double buildingGround = 0;

    for(int k=0; k<L; ++k){
        int i = qRound(startX + (k*stepX));
        double j = (startY + (k*stepY));

        if(prevI < i){
            prevI = i;
            if(i >= length) break;

            if(buildingsUsage){
                buildingHeight = storeysHeights[(int)(slice[i].getCoordinateY()) * lonc
                        + (int)(slice[i].getCoordinateX())][2] * storeysToHeight;
            }
            if(heightUsage){
                buildingGround = storeysHeights[(int)(slice[i].getCoordinateY()) * lonc
                        + (int)(slice[i].getCoordinateX())][4];
            }

            if(buildingHeight + buildingGround >= j){
                kIn++;
            }
        }
    }

    return kIn;
}

QRgb HeatmapModel::signalStrengthToColor(double signalStrength)
{
    static int redChannel, greenChannel, blueChannel;

    int transparency = 100;

    if (signalStrength <= -120.0) { // Blue
        return qRgba(0, 0, 255, transparency);
    }
    else if (signalStrength <= -105.0) { // Blue to cyan
        greenChannel = static_cast<int>(255.0 * ((120.0 + signalStrength) / 15.0));
        return qRgba(0, greenChannel, 255, transparency);
    }
    else if (signalStrength <= -90.0) { // Cyan to green
        blueChannel = static_cast<int>(255.0 * (1.0 - (105.0 + signalStrength) / 15.0));
        return qRgba(0, 255, blueChannel, transparency);
    }
    else if (signalStrength <= -75.0) { // Green to yellow
        redChannel = static_cast<int>(255.0 * ((90.0 + signalStrength) / 15.0));
        return qRgba(redChannel, 255, 0, transparency);
    }
    else if (signalStrength <= -60.0) { // Yellow to red
        greenChannel = static_cast<int>(255.0 * (1.0 - (75.0 + signalStrength) / 15.0));
        return qRgba(255, greenChannel, 0, transparency);
    }
    else { // Red
        return qRgba(255, 0, 0, transparency);
    }
}

void HeatmapModel::calculateHeatmap3DDDA()
{
    int x=BaseStation.getCoordinateX(),
            y=BaseStation.getCoordinateY();

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
            vector <CartesianCoordinates> slice;
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

                if(kIn == 0)
                {
                        pathloss = UMa_LOS(startPoint->calculateDistance2D(point), 0,
                                           BaseStation.getCoordinateZ() + groundDelta,
                                           heightUT, centerFrequency, h,  W, shadowFading);
                        if(pathloss == -1){
                            (data)[i][j] = 20000;
                        }
                        else{
                        double rsrp = BSPower + AntennaGain - pathloss - 10*log10(50*1000/15);
                        (data)[i][j]= rsrp;
                        }
                }
                else
                {
                    pathloss = UMa_NLOS(startPoint->calculateDistance2D(point) - kIn*pixelToMeter, kIn*pixelToMeter,
                                        BaseStation.getCoordinateZ() + groundDelta,
                                        heightUT, centerFrequency, h,  W, shadowFading);
                    if(pathloss == -1){
                        (data)[i][j] = 20000;
                    }
                    else{
                    double rsrp = BSPower + AntennaGain - pathloss - 10*log10(50*1000/15);
                    (data)[i][j]= rsrp;
                    }

                }

            }
            }
        }
    }

}

void HeatmapModel::calculateHeatmap()
{
    clock_t start, end;
    createData();

    start = clock();
    calculateHeatmap3DDDA();
    end = clock();

    qDebug()<<"heatmap calculation TIME = "<<(end - start)/CLOCKS_PER_SEC;

    qDebug()<<"QImage was saved - " << createImage();
}

void HeatmapModel::changeSettings(void* stngs)
{
    SettingsTemplate* settings = (SettingsTemplate*)stngs;
    setBSPower(settings->cellTxPower);
    setAntennaGain(settings->cellAntennaGain);
    setHeightUsage(settings->heightUsage);
    setBuildingsUsage(settings->buildingsUsage);
    setBand(settings->band);
}

