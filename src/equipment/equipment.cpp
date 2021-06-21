#include "Equipment.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QRandomGenerator>
#include <QStyleOption>
#include <QtMath>


Equipment::Equipment()
{

}

void Equipment::printData() {
    qDebug() << this->data;
}

//**************************************************************
// Physical effects methods
//**************************************************************
void Equipment::calculateThermalNoise()
{
    this->thermalNoise = -174 + 10 * log10(this->bandwidth * 1000000);
}

void dopplerEffect(QVector<double> data, double speed, double angle)
{
    int dataLength = data.length();

    // Let's calculate the Doppler shift value per 1 RB (Resource Block = 12 subcarriers)
    for (int RB = 0; RB <= data.length() / 12; RB++) {
    }
}

void Equipment::calculateEIRP()
{
    this->EIRP = this->TxPower + this->antennaGain - this->feederLoss;
}
void Equipment::dopplerEffect(QVector<double> data, double speed, double angle)
{

}

//**************************************************************
// LOGISTIC METHODS
//**************************************************************

void Equipment::assignLonLat(double lon, double lat, double alt)
{
    this->latitude = lat;
    this->longtitude = lon;
    this->altitude = alt;
}

void Equipment::generateRandomCoordinates(double minLon, double minLat, double maxLon, double maxLat, double minAlt, double maxAlt)
{

}

void Equipment::assignPixelCoordinates(int x, int y, int z)
{
    this->pixelX = x;
    this->pixelY = y;
    this->pixelZ = z;
}

//**************************************************************
// GRAPHIC METHODS
//**************************************************************
