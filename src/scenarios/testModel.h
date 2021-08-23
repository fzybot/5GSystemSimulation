//#pragma once

#include "src/visualization/data/plotData/interpolationNskStoreysHeights.cpp"
#include "src/core/CartesianCoordinates.h"
#include "src/visualization/Heatmap.h"
#include "src/protocols/phy/propagationModels.h"
#include <QtMath>

#include <QDebug>


QRgb signalStrengthToColor(double signalStrength);

void testModel()
{
    CartesianCoordinates* BaseStation = new CartesianCoordinates(851, 209, 15);

    QImage image(lonc, latc, QImage::Format_RGB32);
    image.fill(Qt::black);
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
    qDebug()<<"QImage was saved - " << image.save("/home/timofey/Qt/projects/5GSystemSimulation/src/visualization/data/pixelMap.bmp", "BMP", 100);

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
