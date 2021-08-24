//#pragma once

#include "src/visualization/data/plotData/interpolationNskStoreysHeights.cpp"
#include "src/core/CartesianCoordinates.h"
#include "src/visualization/Heatmap.h"
#include "src/protocols/phy/propagationModels.h"
#include <QtMath>

#include <QDebug>

QRgb signalStrengthToColor(double signalStrength);
void calculateHeatmap(double ***data, int ***data2, int X, int Y, int centerFrequency, double h, double W, double heightBS, double heightUT, double shadowFading);

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

    QImage image(lonc, latc, QImage::Format_RGB32);
    image.fill(Qt::black);

    int centerFrequency = 24;
    double h = 10;
    double W = 10;
    double shadowFading = 4; //std 4 or 6 for RMa_LOS
    double heightBS = BaseStation->getCoordinateZ();
    double heightUT = 15; //[m]//point->getCoordinateZ();

    //---Rays---
    calculateHeatmap(&data, &data2, BaseStation->getCoordinateX(), BaseStation->getCoordinateY(), centerFrequency, h, W, heightBS, heightUT, shadowFading);

    for(int i=0; i<lonc;++i){
        for(int j=0;j<latc;++j){
            double signalStrength = data[i][j];
            image.setPixel(i, latc - j - 1, signalStrengthToColor(signalStrength));
        }
    }
    delete[] data;
    delete[] data2;

    /* ---V1---
    for(int i=0; i<lonc;++i){
        for(int j=0;j<latc;++j){
            CartesianCoordinates* point = new CartesianCoordinates(i, j, 2);
            //note: one pixel on map = 1.25 [m] (cause of scaling)
            double distance2Dout = sqrt ( qPow ( (BaseStation->getCoordinateX()*1.25 - point->getCoordinateX()*1.25), 2) +
                              qPow ( (BaseStation->getCoordinateY()*1.25 - point->getCoordinateY()*1.25), 2));
            if(distance2Dout<2){
                image.setPixel(i, latc - j - 1, qRgb(255,255,255));
                continue;
            }
            //i =  844 j =  206(?)
            int centerFrequency = 24;
            double h = 10;
            double W = 10;
            double shadowFading = 4; //std 4 or 6 for RMa_LOS
            double heightBS = BaseStation->getCoordinateZ();
            double heightUT = point->getCoordinateZ();
            double pathloss = UMa_LOS(distance2Dout, 0, heightBS, heightUT,centerFrequency, h, W,shadowFading);
            if(pathloss<0){
                continue;
            }
            double signalStrength = 43 - pathloss;
            if(qIsNaN(signalStrength)) signalStrength=0;
            image.setPixel(i, latc - j - 1, signalStrengthToColor(signalStrength));

            delete point;
        } 
    }
     */
    qDebug()<<"QImage was saved - " << image.save("/home/timofey/Qt/projects/5GSystemSimulation/src/visualization/data/pixelMap.bmp", "BMP", 100);

}

void calculateHeatmap(double ***data, int ***data2, int X, int Y, int centerFrequency, double h, double W, double heightBS, double heightUT, double shadowFading)
{
    int x=X, y=Y;

    //(*data)[x][y]=-10;

    double BSPower = 43; //[dB]

    //---[SETTINGS]---//
    double fi_start = 0;
    double fi_end = 360;
    double fi_step = 0.01;
    double pixelToMeter = 1.25;
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

                   if(storeysHeights[rdy * lonc + rdx][2]<heightBS && storeysHeights[rdy * lonc + rdx][2]<heightUT)//storeysHeights[rdy * lonc + rdx][2]==0)//if((*data)[rdx][rdy]!=WALL)
                   {
                       if(wall==0)
                       {
                           (*data)[rdx][rdy]+= BSPower - InF_LOS(k*pixelToMeter, 0, heightBS, heightUT, centerFrequency, h,  W, shadowFading); //(26 * log(centerFrequency) + 22.7 + 36 * log(k*pixelToMeter));
                           (*data2)[rdx][rdy]+=1;
                           k++;
                       }
                       else
                       {
                           (*data)[rdx][rdy]+= BSPower - InF_NLOS_DH(k*pixelToMeter, 0, heightBS, heightUT, centerFrequency, h,  W, shadowFading); //((26 * log(centerFrequency) + 22.7 + 36 * log((k-wall)*pixelToMeter))+(wall*wallkoaf));
                           (*data2)[rdx][rdy]+=1;
                            k++;
                       }
                   }
                   else
                   {
                       (*data)[rdx][rdy]+= BSPower - InF_NLOS_DH(k*pixelToMeter, 0, heightBS, heightUT, centerFrequency, h,  W, shadowFading);//((26 * log(centerFrequency) + 22.7 + 36 * log((k-wall)*pixelToMeter))+(wall*wallkoaf));
                       (*data2)[rdx][rdy]+=1;
                       k++;
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

                   if(storeysHeights[rdy * lonc + rdx][2]<heightBS && storeysHeights[rdy * lonc + rdx][2]<heightUT)//storeysHeights[rdy * lonc + rdx][2]==0)//if((*data)[rdx][rdy]!=WALL)
                   {
                       if(wall==0)
                       {
                           (*data)[rdx][rdy]+= BSPower - InF_LOS(k*pixelToMeter, 0, heightBS, heightUT, centerFrequency, h,  W, shadowFading);//(26 * log(centerFrequency) + 22.7 + 36 * log(k*pixelToMeter));
                           (*data2)[rdx][rdy]+=1;
                           k++;
                       }
                       else
                       {
                           (*data)[rdx][rdy]+= BSPower - InF_NLOS_DH(k*pixelToMeter, 0, heightBS, heightUT, centerFrequency, h,  W, shadowFading);//((26 * log(centerFrequency) + 22.7 + 36 * log((k-wall)*pixelToMeter))+(wall*wallkoaf));
                           (*data2)[rdx][rdy]+=1;
                           k++;
                       }
                   }
                   else
                   {
                       (*data)[rdx][rdy]+= BSPower - InF_NLOS_DH(k*pixelToMeter, 0, heightBS, heightUT, centerFrequency, h,  W, shadowFading);//((26 * log(centerFrequency) + 22.7 + 36 * log((k-wall)*pixelToMeter))+(wall*wallkoaf));
                       (*data2)[rdx][rdy]+=1;
                       k++;
                       wall++;
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
