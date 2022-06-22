    //#pragma once

#include "src/visualization/data/plotData/interpolationNskStoreysHeights.cpp"
#include "src/core/CartesianCoordinates.h"
#include "src/visualization/Heatmap.h"
#include "src/protocols/phy/Channel/propagationModels.h"
#include <QtMath>
#include <QHash>
#include <QDebug>
#include <stdlib.h>
#include <vector>
#include <time.h>

using namespace std;

QRgb signalStrengthToColor(double signalStrength);
void calculateHeatmap(double ***data, int ***data2, int X, int Y, int centerFrequency, double h, double W, double heightBS, double heightUT, double shadowFading);

void calculateHeatmap3D(double ***data, int ***data2, int X, int Y, int centerFrequency, double h, double W, CartesianCoordinates* BS,
                        double heightUT, double shadowFading);

void calculateHeatmap3Dfast(double ***data, int X, int Y, int centerFrequency, double h, double W, CartesianCoordinates* BS,
                        double heightUT, double shadowFading);

void calculateHeatmap3DTest(double ***data, int ***data2, int X, int Y, int centerFrequency, double h, double W, CartesianCoordinates* BS,
                            double heightUT, double shadowFading);

void calculateHeatmap3Dalt(double ***data, int X, int Y, int centerFrequency, double h, double W, CartesianCoordinates* BS,
                        double heightUT, double shadowFading);

void calculateHeatmap3Drotate(double ***data, int X, int Y, int centerFrequency, double h, double W, CartesianCoordinates* BS,
                        double heightUT, double shadowFading);

void calculateHeatmap3DDDA(double ***data, int X, int Y, double centerFrequency, double h, double W, CartesianCoordinates* BS,
                        double heightUT, double shadowFading);

void calculateHeatmap3DBresenham(double ***data, int X, int Y, int centerFrequency, double h, double W, CartesianCoordinates* BS,
                                 double heightUT, double shadowFading);

int isLOS(vector <CartesianCoordinates> slice);
int isLOS_Hash(QHash <int, CartesianCoordinates> slice);
int isLOS_Hash2(vector <CartesianCoordinates> slice, QHash<int, vector<float>> Hash);

double getAvgBuildingHeight();
QHash<int, vector<float>> createHash();

bool createImage(double**);

void testModel()
{

    double **data = new double*[lonc];
    int **data2 = new int*[lonc];
    for(int i = 0; i < lonc; ++i) {
        data[i] = new double[latc];
        data2[i] = new int[latc];
        for(int j = 0; j < latc; ++j){
            data[i][j] = 0;
            data2[i][j] = 0;
        }
    }

    CartesianCoordinates* BaseStation = new CartesianCoordinates(851, 230, 60); //851, 209, 15 - SibSUTIS //860, 230, 15 - near SibSUTIS
    //test - 600, 347, 15
    //test2 - 284, 85

    double centerFrequency = 2.6;
    double h = getAvgBuildingHeight(); //[m]
    qDebug()<<"avgH = " << h;
    double W = 46;  //[m]
    double shadowFading = 4; //std 4 or 6 for RMa_LOS
    double heightBS = BaseStation->getCoordinateZ();
    double heightUT = 2; //[m]//point->getCoordinateZ();

    clock_t start, end;
    start = clock();
    //---Rays---
    calculateHeatmap3DDDA(&data, BaseStation->getCoordinateX(), BaseStation->getCoordinateY(), centerFrequency, h, W, BaseStation,
                       heightUT, shadowFading);
    end = clock();

    qDebug()<<"TIME = "<<(end - start)/CLOCKS_PER_SEC;

    qDebug()<<"QImage was saved - " << createImage(data);

    delete[] data;
    delete[] data2;


}

bool createImage(double** data){
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
    QString texturePath = QString("/pixelMap.bmp");
    path.append(texturePath);

    return image.save(path, "BMP", 100);
}

double getAvgBuildingHeight()
{
    double sum = 0;
    int count = 0;
    double storeysToHeight = 2.7;


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
int isLOSDDA(vector <CartesianCoordinates> slice)
{

    //clock_t start, end;
    //start = clock();
    double storeysToHeight = 2.7;
    int length = slice.size();

    int L = qMax(fabs(slice.size()), fabs(slice.back().getCoordinateZ() +
                                          storeysHeights[(int)(slice.back().getCoordinateY()) * lonc + (int)(slice.back().getCoordinateX())][4]
            - (slice.front().getCoordinateZ() +
               storeysHeights[(int)(slice.front().getCoordinateY()) * lonc + (int)(slice.front().getCoordinateX())][4])));
    L++;
    double stepX = ((double)(slice.size()))/L;
    double stepY = ((double)((slice.back().getCoordinateZ() +
                              storeysHeights[(int)(slice.back().getCoordinateY()) * lonc + (int)(slice.back().getCoordinateX())][4])
            - (slice.front().getCoordinateZ() +
               storeysHeights[(int)(slice.front().getCoordinateY()) * lonc + (int)(slice.front().getCoordinateX())][4])))/L;

    double startX = 0;
    double startY = slice.front().getCoordinateZ() + storeysHeights[(int)(slice.front().getCoordinateY()) * lonc
            + (int)(slice.front().getCoordinateX())][4];

    int kIn = 0;

    int prevI = 0;
    for(int k=0; k<L; ++k){
        int i = qRound(startX + (k*stepX));
        double j = (startY + (k*stepY));

        if(prevI < i){
            prevI = i;
            if(i >= length) break;
            if(storeysHeights[(int)(slice[i].getCoordinateY()) * lonc + (int)(slice[i].getCoordinateX())][2] * storeysToHeight +
                    storeysHeights[(int)(slice[i].getCoordinateY()) * lonc + (int)(slice[i].getCoordinateX())][4]
                    >= j){
                kIn++;
            }
        }
    }

    return kIn;

}
int isLOS(vector <CartesianCoordinates> slice)
{
    //clock_t start, end;
    //start = clock();
    double storeysToHeight = 2.7;
    int length = slice.size();

    double distance = slice.front().calculateDistance3D(&(slice.back()));

    CartesianCoordinates* groundUnderBS = new CartesianCoordinates(slice.front().getCoordinateX(), slice.front().getCoordinateY(), slice.back().getCoordinateZ());

    double oneStepX = distance/(groundUnderBS->calculateDistance3D(&(slice.back())));
    double oneStepY = distance/(slice.front().calculateDistance3D(groundUnderBS));

    double SumStepsX = 0;
    double SumStepsY = 0;

    int X = 0;
    double Y = 0;


    int kIn=0;
    while(SumStepsX < distance || SumStepsY < distance){
        if(SumStepsX<=SumStepsY){
            SumStepsX += oneStepX;
            X++;
            if(X >= length) break;

            if(storeysHeights[(int)(slice[X].getCoordinateY()) * lonc + (int)(slice[X].getCoordinateX())][2]*storeysToHeight >= slice.front().getCoordinateZ()-Y){
                kIn++;
            }
        }
        else{
            SumStepsY += oneStepY;
            Y++;
        }


    }
    delete groundUnderBS;
    //end = clock();
    //qDebug() << "array time " << (end - start);
    return kIn;
}

int isLOS_Hash2(vector <CartesianCoordinates> slice, QHash<int, vector<float>> Hash)
{
      //clock_t start, end;
      //start = clock();
    double storeysToHeight = 2.7;
    int length = slice.size();

    double distance = slice.front().calculateDistance3D(&(slice.back()));

    CartesianCoordinates* groundUnderBS = new CartesianCoordinates(slice.front().getCoordinateX(), slice.front().getCoordinateY(), slice.back().getCoordinateZ());

    double oneStepX = distance/(groundUnderBS->calculateDistance3D(&(slice.back())));
    double oneStepY = distance/(slice.front().calculateDistance3D(groundUnderBS));

    double SumStepsX = 0;
    double SumStepsY = 0;

    int X = 0;
    double Y = 0;


    int kIn=0;
    while(SumStepsX < distance || SumStepsY < distance){
        if(SumStepsX<=SumStepsY){
            SumStepsX += oneStepX;
            X++;
            if(X >= length) break;
        }
        else{
            SumStepsY += oneStepY;
            Y++;
        }

        if(Hash.value((int)(slice[X].getCoordinateY()) * lonc + (int)(slice[X].getCoordinateX()))[2]*storeysToHeight >= slice.front().getCoordinateZ()-Y){
            kIn++;
        }
    }

    delete groundUnderBS;
    //end = clock();
    //qDebug() << "hash time " << (end - start);
    return kIn;
}

QHash<int, vector<float>> createHash(){
    QHash<int, vector<float>> HashStoreysHeights;

    for(int i=0; i<lonc; ++i){
        for(int j=0; j<latc; ++j){
            vector<float> point;
            point.push_back(storeysHeights[i*latc + j][0]);
            point.push_back(storeysHeights[i*latc + j][1]);
            point.push_back(storeysHeights[i*latc + j][2]);
            point.push_back(storeysHeights[i*latc + j][3]);
            point.push_back(storeysHeights[i*latc + j][4]);

            HashStoreysHeights.insert(i*latc + j, point);
        }
    }
    return HashStoreysHeights;
}

int isLOS_Hash(QHash <int, CartesianCoordinates> slice)
{
    double storeysToHeight = 2.7;
    int length = slice.size();

    CartesianCoordinates source = slice.value(0);
    CartesianCoordinates destination = slice.value(length - 1);

    double distance = source.calculateDistance3D(&(destination));

    CartesianCoordinates* groundUnderBS = new CartesianCoordinates(source.getCoordinateX(),
            source.getCoordinateY(), destination.getCoordinateZ());

    double oneStepX = distance/(groundUnderBS->calculateDistance3D(&(destination)));
    double oneStepY = distance/(source.calculateDistance3D(groundUnderBS));

    double SumStepsX = 0;
    double SumStepsY = 0;

    int X = 0;
    double Y = 0;

    CartesianCoordinates point;
    int kIn=0;
    while(SumStepsX < distance || SumStepsY < distance){
        if(SumStepsX<=SumStepsY){
            SumStepsX += oneStepX;
            X++;
            if(X >= length) break;
        }
        else{
            SumStepsY += oneStepY;
            Y++;
        }

        point = slice.value(X);
        if(storeysHeights[(int)(point.getCoordinateY()) * lonc + (int)(point.getCoordinateX())][2]
                *storeysToHeight >= source.getCoordinateZ()-Y){
            kIn++;
        }
    }
    delete groundUnderBS;
    return kIn;
}

void calculateHeatmap3DTest(double ***data, int ***data2, int X, int Y, int centerFrequency, double h, double W, CartesianCoordinates* BS,
                            double heightUT, double shadowFading)
{
    //int x=X, y=Y;

    double BSPower = 43; //[dBm]
    double AGain = 18;   //[dBm]

    //---[SETTINGS]---//
    double fi_start = 0;
    double fi_end = 360;
    double fi_step = 0.01;
    double pixelToMeter = 1.25;
    double storeysToHeight = 2.7;
    //----------------//

    double fi=fi_start;

    //int i2=0;
    //int j2=0;

    double y = 0;
    double x = 0;
    double step = 1;
    double k = 0;
    double value = 20000;
    int path = 0;
    int indoorPath = 0;

    for(int I = 0; I < lonc; ++I){
        for(int J = 0; J < latc; ++J){
            CartesianCoordinates* point = new CartesianCoordinates(0, 0, heightUT);
            vector <CartesianCoordinates> slice;
            slice.push_back(*BS);
            //calculate k
            path = 0;
            x = 0;
            y = 0;
            if(I == BS->getCoordinateX()){
                k = qPow(latc,latc);
            }
            else{
                k = (J - BS->getCoordinateY())/(I - BS->getCoordinateX());
            }

            if (I - BS->getCoordinateX() > 0){  //is right?
                //right
                if(J - BS->getCoordinateY() > 0){   //is top?
                    //top
                    if(qAtan(k) <= M_PI/4){ //is less then pi/4 ?
                        //yes
                        x = BS->getCoordinateX();
                        while(x < lonc){
                            if(y < latc && y >= 0 && (*data)[(int)x][int(y)]==0)
                            {
                                indoorPath = isLOS(slice);
                                if(indoorPath == 0){
                                    (*data)[(int)x][int(y)] = BSPower + AGain - UMa_LOS(point->calculateDistance2D(BS),
                                                                                indoorPath * pixelToMeter, BS->getCoordinateZ(), heightUT, centerFrequency, h,  W, shadowFading);
                                }
                                else{
                                    (*data)[(int)x][int(y)] = BSPower + AGain - UMa_NLOS(point->calculateDistance2D(BS) - indoorPath * pixelToMeter,
                                                                                indoorPath * pixelToMeter, BS->getCoordinateZ(), heightUT, centerFrequency, h,  W, shadowFading);
                                }
                            }
                            x += step;
                            y = k * (x - BS->getCoordinateX()) +
                                    BS->getCoordinateY();
                            point->setCoordinateX(x);
                            point->setCoordinateY(y);

                            slice.push_back(*point);
                        }
                    }
                    else{
                        //no
                        y = BS->getCoordinateY();
                        while(y < latc){
                            if(x < lonc && x >= 0 && (*data)[(int)x][int(y)]==0)
                            {
                                indoorPath = isLOS(slice);
                                if(indoorPath == 0){
                                    (*data)[(int)x][int(y)] = BSPower + AGain - UMa_LOS(point->calculateDistance2D(BS),
                                                                                indoorPath * pixelToMeter, BS->getCoordinateZ(), heightUT, centerFrequency, h,  W, shadowFading);
                                }
                                else{
                                    (*data)[(int)x][int(y)] = BSPower + AGain - UMa_NLOS(point->calculateDistance2D(BS) - indoorPath * pixelToMeter,
                                                                                indoorPath * pixelToMeter, BS->getCoordinateZ(), heightUT, centerFrequency, h,  W, shadowFading);
                                }
                            }
                            y += step;
                            x = 1/k * (y - BS->getCoordinateY()) +
                                    BS->getCoordinateX();
                            point->setCoordinateX(x);
                            point->setCoordinateY(y);
                            slice.push_back(*point);
                        }

                    }
                }
                else{
                    //bottom
                    //qDebug()<<"right - bottom";
                    if(qAtan(k) <= M_PI/4){ //is less then pi/4
                        //yes
                        x = BS->getCoordinateX();
                        while(x < lonc){
                            if(y < latc && y >= 0 && (*data)[(int)x][int(y)]==0)
                            {
                                indoorPath = isLOS(slice);
                                if(indoorPath == 0){
                                    (*data)[(int)x][int(y)] = BSPower + AGain - UMa_LOS(point->calculateDistance2D(BS),
                                                                                indoorPath * pixelToMeter, BS->getCoordinateZ(), heightUT, centerFrequency, h,  W, shadowFading);
                                }
                                else{
                                    (*data)[(int)x][int(y)] = BSPower + AGain - UMa_NLOS(point->calculateDistance2D(BS) - indoorPath * pixelToMeter,
                                                                                indoorPath * pixelToMeter, BS->getCoordinateZ(), heightUT, centerFrequency, h,  W, shadowFading);
                                }
                            }
                            x += step;
                            y = k * (x - BS->getCoordinateX()) +
                                    BS->getCoordinateY();
                            point->setCoordinateX(x);
                            point->setCoordinateY(y);
                            slice.push_back(*point);
                        }
                    }
                    else{
                        //no
                        y = BS->getCoordinateY();
                        while(y >= 0){
                            if(x < lonc && x >= 0 && (*data)[(int)x][int(y)]==0)
                            {
                                indoorPath = isLOS(slice);
                                if(indoorPath == 0){
                                    (*data)[(int)x][int(y)] = BSPower + AGain - UMa_LOS(point->calculateDistance2D(BS),
                                                                                indoorPath * pixelToMeter, BS->getCoordinateZ(), heightUT, centerFrequency, h,  W, shadowFading);
                                }
                                else{
                                    (*data)[(int)x][int(y)] = BSPower + AGain - UMa_NLOS(point->calculateDistance2D(BS) - indoorPath * pixelToMeter,
                                                                                indoorPath * pixelToMeter, BS->getCoordinateZ(), heightUT, centerFrequency, h,  W, shadowFading);
                                }
                            }
                            y -= step;
                            x = -1/k * (y - BS->getCoordinateY()) +
                                    BS->getCoordinateX();
                            point->setCoordinateX(x);
                            point->setCoordinateY(y);
                            slice.push_back(*point);
                        }
                    }
                }

            }
            else{
                //left
                if(J - BS->getCoordinateY() > 0){   //is top?
                    //top
                    //qDebug()<<"left- top";
                    if(qAtan(k) <= M_PI/4){ //is less then pi/4
                        //yes
                        x = BS->getCoordinateX();
                        while(x >= 0){
                            if(y < latc && y >=0 && (*data)[(int)x][int(y)]==0)
                            {
                                indoorPath = isLOS(slice);
                                if(indoorPath == 0){
                                    (*data)[(int)x][int(y)] = BSPower + AGain - UMa_LOS(point->calculateDistance2D(BS),
                                                                                indoorPath * pixelToMeter, BS->getCoordinateZ(), heightUT, centerFrequency, h,  W, shadowFading);
                                }
                                else{
                                    (*data)[(int)x][int(y)] = BSPower + AGain - UMa_NLOS(point->calculateDistance2D(BS) - indoorPath * pixelToMeter,
                                                                                indoorPath * pixelToMeter, BS->getCoordinateZ(), heightUT, centerFrequency, h,  W, shadowFading);
                                }
                            }
                            x -= step;
                            y = k * (x - BS->getCoordinateX()) +
                                    BS->getCoordinateY();
                            point->setCoordinateX(x);
                            point->setCoordinateY(y);
                            slice.push_back(*point);
                        }
                    }
                    else{
                        //no
                        y = BS->getCoordinateY();
                        while(y < latc){
                            if(x < lonc && x>=0 && (*data)[(int)x][int(y)]==0)
                            {
                                indoorPath = isLOS(slice);
                                if(indoorPath == 0){
                                    (*data)[(int)x][int(y)] = BSPower + AGain - UMa_LOS(point->calculateDistance2D(BS),
                                                                                indoorPath * pixelToMeter, BS->getCoordinateZ(), heightUT, centerFrequency, h,  W, shadowFading);
                                }
                                else{
                                    (*data)[(int)x][int(y)] = BSPower + AGain - UMa_NLOS(point->calculateDistance2D(BS) - indoorPath * pixelToMeter,
                                                                                indoorPath * pixelToMeter, BS->getCoordinateZ(), heightUT, centerFrequency, h,  W, shadowFading);
                                }
                            }
                            y += step;
                            x = -1/k * (y - BS->getCoordinateY()) +
                                    BS->getCoordinateX();
                            point->setCoordinateX(x);
                            point->setCoordinateY(y);
                            slice.push_back(*point);
                        }
                    }
                }
                else{
                    //bottom
                    if(qAtan(k) <= M_PI/4){ //is less then pi/4
                        //yes
                        x = BS->getCoordinateX();
                        while(x >= 0){
                            if(y < latc && y >= 0 && (*data)[(int)x][int(y)]==0)
                            {
                                indoorPath = isLOS(slice);
                                if(indoorPath == 0){
                                    (*data)[(int)x][int(y)] = BSPower + AGain - UMa_LOS(point->calculateDistance2D(BS),
                                                                                indoorPath * pixelToMeter, BS->getCoordinateZ(), heightUT, centerFrequency, h,  W, shadowFading);
                                }
                                else{
                                    (*data)[(int)x][int(y)] = BSPower + AGain - UMa_NLOS(point->calculateDistance2D(BS) - indoorPath * pixelToMeter,
                                                                                indoorPath * pixelToMeter, BS->getCoordinateZ(), heightUT, centerFrequency, h,  W, shadowFading);
                                }
                            }
                            x -= step;
                            y = k * (x - BS->getCoordinateX()) +
                                    BS->getCoordinateY();
                            point->setCoordinateX(x);
                            point->setCoordinateY(y);
                            slice.push_back(*point);
                        }
                    }
                    else{
                        //no
                        y = BS->getCoordinateY();
                        while(y >= 0){
                            if(x < lonc && x >= 0 && (*data)[(int)x][int(y)]==0)
                            {
                                indoorPath = isLOS(slice);
                                if(indoorPath == 0){
                                    (*data)[(int)x][int(y)] = BSPower + AGain - UMa_LOS(point->calculateDistance2D(BS),
                                                                                indoorPath * pixelToMeter, BS->getCoordinateZ(), heightUT, centerFrequency, h,  W, shadowFading);
                                }
                                else{
                                    (*data)[(int)x][int(y)] = BSPower + AGain - UMa_NLOS(point->calculateDistance2D(BS) - indoorPath * pixelToMeter,
                                                                                indoorPath * pixelToMeter, BS->getCoordinateZ(), heightUT, centerFrequency, h,  W, shadowFading);
                                }
                            }
                            y -= step;
                            x = 1/k * (y - BS->getCoordinateY()) +
                                    BS->getCoordinateX();
                            point->setCoordinateX(x);
                            point->setCoordinateY(y);
                            slice.push_back(*point);
                        }
                    }
                }

            }
            delete point;
        }
    }
}

void calculateHeatmap3DDDA(double ***data, int X, int Y, double centerFrequency, double h, double W, CartesianCoordinates* BS,
                        double heightUT, double shadowFading)
{
    int x=X, y=Y;

    double BSPower = 43; //[dBm]
    double AGain = 10;   //[dBm]

    //---[SETTINGS]---//
    double fi_start = 0;
    double fi_end = 360;
    double fi_step = 0.01;
    double pixelToMeter = 1.25;
    double storeysToHeight = 2.7;
    //----------------//

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
            CartesianCoordinates *startPoint = new CartesianCoordinates(x,y, BS->getCoordinateZ());
            vector <CartesianCoordinates> slice;
            slice.push_back(*BS);

            for(int k=1; k<=L; ++k){
                int i = qRound(startX + (k*stepX));
                int j = qRound(startY + (k*stepY));
                if(i<0 || i>=lonc || j<0 || j>=latc) break;
                double pathloss=0;
                point->setCoordinateX(i);
                point->setCoordinateY(j);
                slice.push_back(*point);

                if((*data)[i][j]!=0) continue;
                kIn = isLOSDDA(slice);
                double groundBS = storeysHeights[(int)(BS->getCoordinateY()) * lonc
                        + (int)(BS->getCoordinateX())][4];
                double groundUT = storeysHeights[(int)(slice.back().getCoordinateY()) * lonc
                        + (int)(slice.back().getCoordinateX())][4];
                double groundDelta = groundBS - groundUT;

                if(kIn == 0)
                {
                        pathloss = UMi_LOS(startPoint->calculateDistance2D(point), 0, BS->getCoordinateZ() + groundDelta, heightUT, centerFrequency, h,  W, shadowFading);
                        if(pathloss == -1){
                            (*data)[i][j] = 20000;
                        }
                        else{
                        double rsrp = BSPower + AGain - pathloss - 10*log10(50*1000/15);
                        (*data)[i][j]= rsrp;
                        }
                }
                else
                {
                    pathloss = UMi_NLOS(startPoint->calculateDistance2D(point) - kIn*pixelToMeter, kIn*pixelToMeter, BS->getCoordinateZ() + groundDelta, heightUT, centerFrequency, h,  W, shadowFading);
                    if(pathloss == -1){
                        (*data)[i][j] = 20000;
                    }
                    else{
                    double rsrp = BSPower + AGain - pathloss - 10*log10(50*1000/15);
                    (*data)[i][j]= rsrp;
                    }

                }

            }
            }
        }
    }

}

void calculateHeatmap3Dalt(double ***data, int X, int Y, int centerFrequency, double h, double W, CartesianCoordinates* BS,
                        double heightUT, double shadowFading)
{
    int x=X, y=Y;

    double BSPower = 43; //[dBm]
    double AGain = 18;   //[dBm]

    //---[SETTINGS]---//
    double fi_start = 0;
    double fi_end = 360;
    double fi_step = 0.01;
    double pixelToMeter = 1.25;
    double storeysToHeight = 2.7;
    //----------------//

    double fi=fi_start;

    int startI=0;
    int startJ=0;

       while(fi<=fi_end)
       {
           startI=1;
           startJ=latc;

           double C=0,Sx=0,Sy=0;
           double Cx=0,Cy=0;
           int dx=0,dy=0;

           C=sqrt(pow(startI,2) + pow(startJ,2));

           Sx=sqrt(1 + pow(startJ/startI,2));
           Sy=sqrt(1 + pow(startI/startJ,2));

           dx=0;
           dy=0;
           Cx=0;
           Cy=0;

           int k=0;
           int kIn = 0;
           double pathloss = 0;

           if(Sx>=Sy)
           {
               Cx+=Sx;
               dx++;
           }
           else
           {
               Cy+=Sy;
               dy++;
           }

           int rdx=0,rdy=0;
           vector <CartesianCoordinates> slice;
           slice.push_back(*BS);
           do
           {
               if(Cx<=Cy)
               {
                   Cx+=Sx;
                   dx++;
               }
               else
               {
                   Cy+=Sy;
                   dy++;
               }

                       rdx=round(dx*cos(fi*M_PI/180)+dy*sin(fi*M_PI/180));
                       rdy=round(dx*(-1)*sin(fi*M_PI/180)+dy*cos(fi*M_PI/180));

                       rdx=rdx+x;
                       rdy=rdy+y;

                       if(rdx<0 || rdx>=lonc || rdy<0 || rdy>=latc) break;
                    slice.push_back(CartesianCoordinates(rdx, rdy, heightUT));
                    if((*data)[rdx][rdy]!=0){
                        k++;
                        continue;
                    }
                    kIn = isLOS(slice);
                   if(kIn == 0)
                   {
                           pathloss = UMa_LOS(k*pixelToMeter, 0, BS->getCoordinateZ(), heightUT, centerFrequency, h,  W, shadowFading);
                           if(pathloss == -1){
                               (*data)[rdx][rdy] = 20000;
                           }
                           else{
                           (*data)[rdx][rdy]= BSPower + AGain - pathloss;
                           }
                           k++;
                   }
                   else
                   {
                       pathloss = UMa_NLOS((k-kIn)*pixelToMeter, kIn*pixelToMeter, BS->getCoordinateZ(), heightUT, centerFrequency, h,  W, shadowFading);
                       if(pathloss == -1){
                           (*data)[rdx][rdy] = 20000;
                       }
                       else{
                       (*data)[rdx][rdy]= BSPower + AGain - pathloss;
                       }
                       k++;
                       kIn++;
                   }

           }while(rdy>=0 && rdy<latc && rdx>=0 && rdx<lonc);

       fi=fi+fi_step;
   }
}



void calculateHeatmap3Drotate(double ***data, int X, int Y, int centerFrequency, double h, double W, CartesianCoordinates* BS,
                        double heightUT, double shadowFading)
{
    int x=X, y=Y;

    double BSPower = 43; //[dBm]
    double AGain = 18;   //[dBm]

    //---[SETTINGS]---//
    double fi_start = 0;
    double fi_end = 360;
    double fi_step = 0.01;
    double pixelToMeter = 1.25;
    double storeysToHeight = 2.7;
    //----------------//
    //TODO: feature to calculate max necessary fi_step
    double fi=fi_start;

       while(fi<=fi_end)
       {
           int dx=0,dy=0;

           int k=0;
           int kIn = 0;
           double pathloss = 0;

           int rdx=0,rdy=0;
           vector <CartesianCoordinates> slice;
           slice.push_back(*BS);
           do
           {
               dy++;

                       rdx=round(dx*cos(fi*M_PI/180)+dy*sin(fi*M_PI/180));
                       rdy=round(dx*(-1)*sin(fi*M_PI/180)+dy*cos(fi*M_PI/180));

                       rdx=rdx+x;
                       rdy=rdy+y;

                       if(rdx<0 || rdx>=lonc || rdy<0 || rdy>=latc) break;
                    slice.push_back(CartesianCoordinates(rdx, rdy, heightUT));
                    if((*data)[rdx][rdy]!=0){
                        k++;
                        continue;
                    }
                    kIn = isLOSDDA(slice);
                   if(kIn == 0)
                   {
                           pathloss = UMa_LOS(k*pixelToMeter, 0, BS->getCoordinateZ(), heightUT, centerFrequency, h,  W, shadowFading);
                           if(pathloss == -1){
                               (*data)[rdx][rdy] = 20000;
                           }
                           else{
                           (*data)[rdx][rdy]= BSPower + AGain - pathloss;
                           }
                           k++;
                   }
                   else
                   {
                       pathloss = UMa_NLOS((k-kIn)*pixelToMeter, kIn*pixelToMeter, BS->getCoordinateZ(), heightUT, centerFrequency, h,  W, shadowFading);
                       if(pathloss == -1){
                           (*data)[rdx][rdy] = 20000;
                       }
                       else{
                       (*data)[rdx][rdy]= BSPower + AGain - pathloss;
                       }
                       k++;
                       kIn++;
                   }

           }while(rdy>=0 && rdy<latc && rdx>=0 && rdx<lonc);

       fi=fi+fi_step;
   }
}


void calculateHeatmap3Dfast(double ***data, int X, int Y, int centerFrequency, double h, double W, CartesianCoordinates* BS,
                        double heightUT, double shadowFading)
{
    int x=X, y=Y;

    double BSPower = 43; //[dBm]
    double AGain = 18;   //[dBm]

    //---[SETTINGS]---//
    double fi_start = 0;
    double fi_end = 360;
    double fi_step = 0.01;
    double pixelToMeter = 1.25;
    double storeysToHeight = 2.7;
    //----------------//

    double fi=fi_start;

    int i2=0;
    int j2=0;

       while(fi<=fi_end)
       {

           i2=1;
           j2=latc*2;

           double C=0,Sx=0,Sy=0;
           double Cx=0,Cy=0;
           int dx=0,dy=0;

           C=sqrt(pow(i2,2) + pow(j2,2));

           Sx=sqrt(1 + pow(j2/i2,2));
           Sy=sqrt(1 + pow(i2/j2,2));

           dx=0;
           dy=0;
           Cx=0;
           Cy=0;

           int k=0;
           int kIn = 0;
           double pathloss = 0;

           if(Sx>=Sy)
           {
               Cx+=Sx;
           }
           else
           {
               Cy+=Sy;
           }

           int rdx=0,rdy=0;
           vector <CartesianCoordinates> slice;
           //slice.insert(slice.size(),*BS);
           slice.push_back(*BS);
           while(1)                     //(Cx<C || Cy<C)(?)
           {
               if(Cx<=Cy)
               {
                   Cx+=Sx;
                   if((i2)<0)dx--;
                   else
                       dx++;

                   if(rdx>=0 && rdx<lonc)
                   {

                       rdx=round(dx*cos(fi*M_PI/180)+dy*sin(fi*M_PI/180));
                       rdy=round(dx*(-1)*sin(fi*M_PI/180)+dy*cos(fi*M_PI/180));

                       rdx=rdx+x;
                       rdy=rdy+y;

                       if(rdx<0 || rdx>=lonc || rdy<0 || rdy>=latc) break;
                    //slice.insert(slice.size(),CartesianCoordinates(rdx, rdy, heightUT));
                    slice.push_back(CartesianCoordinates(rdx, rdy, heightUT));
                    if((*data)[rdx][rdy]!=0){
                        k++;
                        continue;
                    }
                    kIn = isLOS(slice);
                   if(kIn == 0)//storeysHeights[rdy * lonc + rdx][2]==0)//if((*data)[rdx][rdy]!=WALL)
                   {
                           pathloss = UMa_LOS(k*pixelToMeter, 0, BS->getCoordinateZ(), heightUT, centerFrequency, h,  W, shadowFading);
                           if(pathloss == -1){
                               (*data)[rdx][rdy] = 20000;
                               //(*data2)[rdx][rdy] = 1;
                           }
                           else{
                           (*data)[rdx][rdy]= BSPower + AGain - pathloss; //(26 * log(centerFrequency) + 22.7 + 36 * log(k*pixelToMeter));
                           //(*data2)[rdx][rdy]+=1;
                           }
                           k++;
                   }
                   else
                   {
                       pathloss = UMa_NLOS((k-kIn)*pixelToMeter, kIn*pixelToMeter, BS->getCoordinateZ(), heightUT, centerFrequency, h,  W, shadowFading);
                       if(pathloss == -1){
                           (*data)[rdx][rdy] = 20000;
                           //(*data2)[rdx][rdy] = 1;
                       }
                       else{
                       (*data)[rdx][rdy]= BSPower + AGain - pathloss;//((26 * log(centerFrequency) + 22.7 + 36 * log((k-wall)*pixelToMeter))+(wall*wallkoaf));
                       //(*data2)[rdx][rdy]+=1;
                       }
                       k++;
                   }
                   }
                   else
                       break;
               }
               else
               {
                   Cy+=Sy;
                   if((j2)<0)dy--;
                   else
                       dy++;

                   if(rdy>=0 && rdy<latc)
                   {

                       rdx=round(dx*cos(fi*M_PI/180)+dy*sin(fi*M_PI/180));
                       rdy=round(dx*(-1)*sin(fi*M_PI/180)+dy*cos(fi*M_PI/180));

                       rdx=rdx+x;
                       rdy=rdy+y;

                       if(rdx<0 || rdx>=lonc || rdy<0 || rdy>=latc) break;
                    //slice.insert(slice.size(),CartesianCoordinates(rdx, rdy, heightUT));
                    slice.push_back(CartesianCoordinates(rdx, rdy, heightUT));
                    if((*data)[rdx][rdy]!=0){
                        k++;
                        continue;
                    }
                    kIn = isLOS(slice);
                   if(kIn == 0)//storeysHeights[rdy * lonc + rdx][2]==0)//if((*data)[rdx][rdy]!=WALL)
                   {
                           pathloss = UMa_LOS(k*pixelToMeter, 0, BS->getCoordinateZ(), heightUT, centerFrequency, h,  W, shadowFading);
                           if(pathloss == -1){
                               (*data)[rdx][rdy] = 20000;
                               //(*data2)[rdx][rdy] = 1;
                           }
                           else{
                           (*data)[rdx][rdy]= BSPower + AGain - pathloss;//(26 * log(centerFrequency) + 22.7 + 36 * log(k*pixelToMeter));
                           //(*data2)[rdx][rdy]+=1;
                           }
                           k++;
                   }
                   else
                   {
                       pathloss = UMa_NLOS((k-kIn)*pixelToMeter, kIn*pixelToMeter, BS->getCoordinateZ(), heightUT, centerFrequency, h,  W, shadowFading);
                       if(pathloss == -1){
                           (*data)[rdx][rdy] = 20000;
                           //(*data2)[rdx][rdy] = 1;
                       }
                       else{
                       (*data)[rdx][rdy]= BSPower + AGain - pathloss;//((26 * log(centerFrequency) + 22.7 + 36 * log((k-wall)*pixelToMeter))+(wall*wallkoaf));
                       //(*data2)[rdx][rdy]+=1;
                       }
                       k++;
                       kIn++;
                   }
                   }
                   else
                       break;
               }

           }



       fi=fi+fi_step;;
   }
/*
for(int i=0;i<lonc;++i)
{
    for(int j=0;j<latc;++j)
    {
        //if((*data)[i][j]!=WALL && (*data)[i][j]!=TX)
        (*data)[i][j]=double((*data)[i][j])/int((*data2)[i][j]);
    }
}
*/
}


void calculateHeatmap3D(double ***data, int ***data2, int X, int Y, int centerFrequency, double h, double W, CartesianCoordinates* BS,
                        double heightUT, double shadowFading)
{
    int x=X, y=Y;

    double BSPower = 43; //[dBm]
    double AGain = 18;   //[dBm]

    //---[SETTINGS]---//
    double fi_start = 0;
    double fi_end = 360;
    double fi_step = 0.01;
    double pixelToMeter = 1.25;
    double storeysToHeight = 2.7;
    //----------------//

    double fi=fi_start;

    int i2=0;
    int j2=0;

       while(fi<=fi_end)
       {

           i2=1;
           j2=latc*2;

           double C=0,Sx=0,Sy=0;
           double Cx=0,Cy=0;
           int dx=0,dy=0;

           C=sqrt(pow(i2,2) + pow(j2,2));

           Sx=sqrt(1 + pow(j2/i2,2));
           Sy=sqrt(1 + pow(i2/j2,2));

           dx=0;
           dy=0;
           Cx=0;
           Cy=0;

           int k=0;
           int kIn = 0;
           double pathloss = 0;

           if(Sx>=Sy)
           {
               Cx+=Sx;
           }
           else
           {
               Cy+=Sy;
           }

           int rdx=0,rdy=0;
           vector <CartesianCoordinates> slice;
           //slice.insert(slice.size(),*BS);
           slice.push_back(*BS);
           while(1)                     //(Cx<C || Cy<C)(?)
           {
               if(Cx<=Cy)
               {
                   Cx+=Sx;
                   if((i2)<0)dx--;
                   else
                       dx++;

                   if(rdx>=0 && rdx<lonc)
                   {

                       rdx=round(dx*cos(fi*M_PI/180)+dy*sin(fi*M_PI/180));
                       rdy=round(dx*(-1)*sin(fi*M_PI/180)+dy*cos(fi*M_PI/180));

                       rdx=rdx+x;
                       rdy=rdy+y;

                       if(rdx<0 || rdx>=lonc || rdy<0 || rdy>=latc) break;
                    //slice.insert(slice.size(),CartesianCoordinates(rdx, rdy, heightUT));
                    slice.push_back(CartesianCoordinates(rdx, rdy, heightUT));
                    kIn = isLOS(slice);
                   if(kIn == 0)//storeysHeights[rdy * lonc + rdx][2]==0)//if((*data)[rdx][rdy]!=WALL)
                   {
                           pathloss = UMa_LOS(k*pixelToMeter, 0, BS->getCoordinateZ(), heightUT, centerFrequency, h,  W, shadowFading);
                           if(pathloss == -1){
                               (*data)[rdx][rdy] = 20000;
                               (*data2)[rdx][rdy] = 1;
                           }
                           else{
                           (*data)[rdx][rdy]+= BSPower + AGain - pathloss; //(26 * log(centerFrequency) + 22.7 + 36 * log(k*pixelToMeter));
                           (*data2)[rdx][rdy]+=1;
                           }
                           k++;
                   }
                   else
                   {
                       pathloss = UMa_NLOS((k-kIn)*pixelToMeter, kIn*pixelToMeter, BS->getCoordinateZ(), heightUT, centerFrequency, h,  W, shadowFading);
                       if(pathloss == -1){
                           (*data)[rdx][rdy] = 20000;
                           (*data2)[rdx][rdy] = 1;
                       }
                       else{
                       (*data)[rdx][rdy]+= BSPower + AGain - pathloss;//((26 * log(centerFrequency) + 22.7 + 36 * log((k-wall)*pixelToMeter))+(wall*wallkoaf));
                       (*data2)[rdx][rdy]+=1;
                       }
                       k++;
                   }
                   }
                   else
                       break;
               }
               else
               {
                   Cy+=Sy;
                   if((j2)<0)dy--;
                   else
                       dy++;

                   if(rdy>=0 && rdy<latc)
                   {

                       rdx=round(dx*cos(fi*M_PI/180)+dy*sin(fi*M_PI/180));
                       rdy=round(dx*(-1)*sin(fi*M_PI/180)+dy*cos(fi*M_PI/180));

                       rdx=rdx+x;
                       rdy=rdy+y;

                       if(rdx<0 || rdx>=lonc || rdy<0 || rdy>=latc) break;
                    //slice.insert(slice.size(),CartesianCoordinates(rdx, rdy, heightUT));
                    slice.push_back(CartesianCoordinates(rdx, rdy, heightUT));
                    kIn = isLOS(slice);
                   if(kIn == 0)//storeysHeights[rdy * lonc + rdx][2]==0)//if((*data)[rdx][rdy]!=WALL)
                   {
                           pathloss = UMa_LOS(k*pixelToMeter, 0, BS->getCoordinateZ(), heightUT, centerFrequency, h,  W, shadowFading);
                           if(pathloss == -1){
                               (*data)[rdx][rdy] = 20000;
                               (*data2)[rdx][rdy] = 1;
                           }
                           else{
                           (*data)[rdx][rdy]+= BSPower + AGain - pathloss;//(26 * log(centerFrequency) + 22.7 + 36 * log(k*pixelToMeter));
                           (*data2)[rdx][rdy]+=1;
                           }
                           k++;
                   }
                   else
                   {
                       pathloss = UMa_NLOS((k-kIn)*pixelToMeter, kIn*pixelToMeter, BS->getCoordinateZ(), heightUT, centerFrequency, h,  W, shadowFading);
                       if(pathloss == -1){
                           (*data)[rdx][rdy] = 20000;
                           (*data2)[rdx][rdy] = 1;
                       }
                       else{
                       (*data)[rdx][rdy]+= BSPower + AGain - pathloss;//((26 * log(centerFrequency) + 22.7 + 36 * log((k-wall)*pixelToMeter))+(wall*wallkoaf));
                       (*data2)[rdx][rdy]+=1;
                       }
                       k++;
                       kIn++;
                   }
                   }
                   else
                       break;
               }

           }



       fi=fi+fi_step;;
   }

for(int i=0;i<lonc;++i)
{
    for(int j=0;j<latc;++j)
    {
        //if((*data)[i][j]!=WALL && (*data)[i][j]!=TX)
        (*data)[i][j]=double((*data)[i][j])/int((*data2)[i][j]);
    }
}

}



void calculateHeatmap(double ***data, int ***data2, int X, int Y, int centerFrequency, double h, double W, double heightBS, double heightUT, double shadowFading)
{
    int x=X, y=Y;

    double BSPower = 43; //[dBm]
    double AGain = 18;   //[dBm]

    //---[SETTINGS]---//
    double fi_start = 0;
    double fi_end = 360;
    double fi_step = 0.01;
    double pixelToMeter = 1.25;
    double storeysToHeight = 2.7;
    //----------------//

    double fi=fi_start;

    int i2=0;
    int j2=0;

       while(fi<=fi_end)
       {

           i2=1;
           j2=latc*2;

           double C=0,Sx=0,Sy=0;
           double Cx=0,Cy=0;
           int dx=0,dy=0;

           C=sqrt(pow(i2,2) + pow(j2,2));

           Sx=sqrt(1 + pow(j2/i2,2));
           Sy=sqrt(1 + pow(i2/j2,2));

           dx=0;
           dy=0;
           Cx=0;
           Cy=0;


           int wall=0;
           int k=0;
           int kIn = 0;
           double pathloss = 0;

           if(Sx>=Sy)
           {
               Cx+=Sx;
           }
           else
           {
               Cy+=Sy;
           }

           int rdx=0,rdy=0;

           while(1)                     //(Cx<C || Cy<C)(?)
           {
               if(Cx<=Cy)
               {
                   Cx+=Sx;
                   if((i2)<0)dx--;
                   else
                       dx++;

                   if(rdx>=0 && rdx<lonc)
                   {

                       rdx=round(dx*cos(fi*M_PI/180)+dy*sin(fi*M_PI/180));
                       rdy=round(dx*(-1)*sin(fi*M_PI/180)+dy*cos(fi*M_PI/180));

                       rdx=rdx+x;
                       rdy=rdy+y;

                       if(rdx<0 || rdx>=lonc || rdy<0 || rdy>=latc) break;

                   if((storeysHeights[rdy * lonc + rdx][2]*storeysToHeight)<heightBS && (storeysHeights[rdy * lonc + rdx][2]*storeysToHeight)<heightUT)//storeysHeights[rdy * lonc + rdx][2]==0)//if((*data)[rdx][rdy]!=WALL)
                   {
                       if(wall==0)
                       {
                           pathloss = UMa_LOS(k*pixelToMeter, 0, heightBS, heightUT, centerFrequency, h,  W, shadowFading);
                           if(pathloss == -1){
                               (*data)[rdx][rdy] = 20000;
                               (*data2)[rdx][rdy] = 1;
                           }
                           else{
                           (*data)[rdx][rdy]+= BSPower + AGain - pathloss; //(26 * log(centerFrequency) + 22.7 + 36 * log(k*pixelToMeter));
                           (*data2)[rdx][rdy]+=1;
                           }
                           k++;

                       }
                       else
                       {
                           pathloss = UMa_NLOS(k*pixelToMeter, kIn*pixelToMeter, heightBS, heightUT, centerFrequency, h,  W, shadowFading);
                           if(pathloss == -1){
                               (*data)[rdx][rdy] = 20000;
                               (*data2)[rdx][rdy] = 1;
                           }
                           else{
                           (*data)[rdx][rdy]+= BSPower + AGain - pathloss; //((26 * log(centerFrequency) + 22.7 + 36 * log((k-wall)*pixelToMeter))+(wall*wallkoaf));
                           (*data2)[rdx][rdy]+=1;
                           }
                            k++;
                            //kIn = 0;
                       }
                   }
                   else
                   {
                       pathloss = UMa_NLOS(k*pixelToMeter, kIn*pixelToMeter, heightBS, heightUT, centerFrequency, h,  W, shadowFading);
                       if(pathloss == -1){
                           (*data)[rdx][rdy] = 20000;
                           (*data2)[rdx][rdy] = 1;
                       }
                       else{
                       (*data)[rdx][rdy]+= BSPower + AGain - pathloss;//((26 * log(centerFrequency) + 22.7 + 36 * log((k-wall)*pixelToMeter))+(wall*wallkoaf));
                       (*data2)[rdx][rdy]+=1;
                       }
                       k++;
                       kIn++;
                       wall++;
                   }
                   }
                   else
                       break;
               }
               else
               {
                   Cy+=Sy;
                   if((j2)<0)dy--;
                   else
                       dy++;

                   if(rdy>=0 && rdy<latc)
                   {

                       rdx=round(dx*cos(fi*M_PI/180)+dy*sin(fi*M_PI/180));
                       rdy=round(dx*(-1)*sin(fi*M_PI/180)+dy*cos(fi*M_PI/180));

                       rdx=rdx+x;
                       rdy=rdy+y;

                       if(rdx<0 || rdx>=lonc || rdy<0 || rdy>=latc) break;

                   if((storeysHeights[rdy * lonc + rdx][2]*storeysToHeight)<heightBS && (storeysHeights[rdy * lonc + rdx][2]*storeysToHeight)<heightUT)//storeysHeights[rdy * lonc + rdx][2]==0)//if((*data)[rdx][rdy]!=WALL)
                   {
                       if(wall==0)
                       {
                           pathloss = UMa_LOS(k*pixelToMeter, 0, heightBS, heightUT, centerFrequency, h,  W, shadowFading);
                           if(pathloss == -1){
                               (*data)[rdx][rdy] = 20000;
                               (*data2)[rdx][rdy] = 1;
                           }
                           else{
                           (*data)[rdx][rdy]+= BSPower + AGain - pathloss;//(26 * log(centerFrequency) + 22.7 + 36 * log(k*pixelToMeter));
                           (*data2)[rdx][rdy]+=1;
                           }
                           k++;
                       }
                       else
                       {
                           pathloss = UMa_NLOS(k*pixelToMeter, 0, heightBS, heightUT, centerFrequency, h,  W, shadowFading);
                           if(pathloss == -1){
                               (*data)[rdx][rdy] = 20000;
                               (*data2)[rdx][rdy] = 1;
                           }
                           else{
                           (*data)[rdx][rdy]+= BSPower + AGain - pathloss; //((26 * log(centerFrequency) + 22.7 + 36 * log((k-wall)*pixelToMeter))+(wall*wallkoaf));
                           (*data2)[rdx][rdy]+=1;
                           }
                           k++;
                           //kIn = 0;
                       }
                   }
                   else
                   {
                       pathloss = UMa_NLOS(k*pixelToMeter, 0, heightBS, heightUT, centerFrequency, h,  W, shadowFading);
                       if(pathloss == -1){
                           (*data)[rdx][rdy] = 20000;
                           (*data2)[rdx][rdy] = 1;
                       }
                       else{
                       (*data)[rdx][rdy]+= BSPower + AGain - pathloss;//((26 * log(centerFrequency) + 22.7 + 36 * log((k-wall)*pixelToMeter))+(wall*wallkoaf));
                       (*data2)[rdx][rdy]+=1;
                       }
                       k++;
                       wall++;
                       kIn++;
                   }
                   }
                   else
                       break;
               }

           }



       fi=fi+fi_step;;
   }

for(int i=0;i<lonc;++i)
{
    for(int j=0;j<latc;++j)
    {
        //if((*data)[i][j]!=WALL && (*data)[i][j]!=TX)
        (*data)[i][j]=double((*data)[i][j])/int((*data2)[i][j]);
    }
}

}



QRgb signalStrengthToColor(double signalStrength)
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
