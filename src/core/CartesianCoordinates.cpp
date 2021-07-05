#include "CartesianCoordinates.h"
#include <QtMath>

CartesianCoordinates::CartesianCoordinates()
{

}

CartesianCoordinates::CartesianCoordinates(double x, double y, double z)
{
    setCoordintes(x, y, z);
}

CartesianCoordinates::CartesianCoordinates(double x, double y, double z, double angX, double angY, double angZ)
{
    setCoordintes(x, y, z);
    setAngles(angX, angY, angZ);
}

void CartesianCoordinates::setCoordintes(double x, double y, double z)
{
    posX_ = x;
    posY_ = y;
    posZ_ = z;
}

void CartesianCoordinates::setAngles(double angX, double angY, double angZ)
{
    angleX_ = angX;
    angleY_ = angY;
    angleZ_ = angZ;
}

double CartesianCoordinates::calculateDistance3D(CartesianCoordinates *remoteEquipment)
{
    return sqrt ( qPow ( (getCoordinateX() - remoteEquipment->getCoordinateX()), 2) +
                  qPow ( (getCoordinateY() - remoteEquipment->getCoordinateY()), 2) +
                  qPow ( (getCoordinateZ() - remoteEquipment->getCoordinateZ()), 2) );
}

double CartesianCoordinates::getCoordinateX()
{
    return posX_;
}

double CartesianCoordinates::getCoordinateY()
{
    return posY_;
}

double CartesianCoordinates::getCoordinateZ()
{
    return posZ_;
}

void CartesianCoordinates::setCoordinateAngleX(double angX)
{
    angleX_ = angX;
}

void CartesianCoordinates::setCoordinateAngleY(double angY)
{
    angleY_ = angY;
}

void CartesianCoordinates::setCoordinateAngleZ(double angZ)
{
    angleZ_ = angZ;
}
