//#pragma once

#include "src/visualization/data/plotData/interpolationNskStoreysHeights.cpp"
#include "src/core/CartesianCoordinates.h"
#include "src/visualization/Heatmap.h"
#include "src/protocols/phy/propagationModels.h"
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

    CartesianCoordinates* BaseStation = new CartesianCoordinates(860, 230, 15); //851, 209, 15 - SibSUTIS //860, 230, 15 - near SibSUTIS

    int centerFrequency = 24;
    double h = getAvgBuildingHeight(); //[m]
    qDebug()<<"avgH = " << h;
    double W = 46;  //[m]
    double shadowFading = 4; //std 4 or 6 for RMa_LOS
    double heightBS = BaseStation->getCoordinateZ();
    double heightUT = 2; //[m]//point->getCoordinateZ();

    clock_t start, end;
    start = clock();
    //---Rays---
    calculateHeatmap3Dfast(&data, BaseStation->getCoordinateX(), BaseStation->getCoordinateY(), centerFrequency, h, W, BaseStation,
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
        }
        else{
            SumStepsY += oneStepY;
            Y++;
        }

        if(storeysHeights[(int)(slice[X].getCoordinateY()) * lonc + (int)(slice[X].getCoordinateX())][2]*storeysToHeight >= slice.front().getCoordinateZ()-Y){
            kIn++;
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
