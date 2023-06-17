#include "CartesianCoordinates.h"
#include <QtMath>
#include <QDebug>
#include <QGeoCoordinate>

#include "src/debug.h"

// ----- [ CONSTRUCTORS ] ----------------------------------------------------------------------------------------------
CartesianCoordinates::CartesianCoordinates()
{
    //debug("CartesianCoordinates: CartesianCoordinates()");
    angleX_ = 0;
    angleY_ = 0;
    angleZ_ = 0;
    posX_ = 0;
    posY_ = 0;
    posZ_ = 0;
    //debug("CartesianCoordinates: CartesianCoordinates() - done");
}

CartesianCoordinates::CartesianCoordinates(double x, double y, double z)
{
    //debug("CartesianCoordinates: CartesianCoordinates(double x, double y, double z)");
    setCoordintes(x, y, z);
}

CartesianCoordinates::CartesianCoordinates(double x, double y, double z, double angX, double angY, double angZ)
{
    setCoordintes(x, y, z);
    setAngles(angX, angY, angZ);
}

// ----- [ SETTERS\GETTERS ] -------------------------------------------------------------------------------------------

void CartesianCoordinates::setCoordintes(double x, double y, double z)
{
    //debug("CartesianCoordinates: setCoordintes(double x, double y, double z)");
    setCoordinateX(x);
    setCoordinateY(y);
    setCoordinateZ(z);
    //debug("CartesianCoordinates: Coordinates: ", posX_, posY_, posZ_);
}

void CartesianCoordinates::setAngles(double angX, double angY, double angZ)
{
    setAngleX(angX);
    setAngleY(angY);
    setAngleZ(angZ);
}

double CartesianCoordinates::calculateDistance3D(CartesianCoordinates *remoteEquipment)
{
    return sqrt ( qPow ( (getCoordinateX() - remoteEquipment->getCoordinateX()), 2) +
                  qPow ( (getCoordinateY() - remoteEquipment->getCoordinateY()), 2) +
                  qPow ( (getCoordinateZ() - remoteEquipment->getCoordinateZ()), 2) );
}

double CartesianCoordinates::calculateDistance2D(CartesianCoordinates *remoteEquipment)
{
    return sqrt ( qPow ( (getCoordinateX() - remoteEquipment->getCoordinateX()), 2) +
                  qPow ( (getCoordinateY() - remoteEquipment->getCoordinateY()), 2) );
}

double CartesianCoordinates::calculateAngleToRemote(CartesianCoordinates *sourceEquipment, CartesianCoordinates *remoteEquipment)
{
    int x1 = sourceEquipment->getCoordinateX();
    int y1 = sourceEquipment->getCoordinateY();
    int x2 = remoteEquipment->getCoordinateX();
    int y2 = remoteEquipment->getCoordinateY();

    double deltaX = qFabs(x1 - x2) + 0.00001;
    double deltaY = qFabs(y1 - y2) + 0.00001;
    double angle = 0;
    if ((x1 - x2) < 0 && (y1 - y2) < 0)
    {
        angle =  qRadiansToDegrees(qAtan(deltaY / deltaX));
    } else if ( (x1 - x2) > 0 && (y1 - y2) < 0 )
    {
        angle =  (90 - qRadiansToDegrees(qAtan(deltaY / deltaX))) + 90;
    } else if ((x1 - x2) > 0 && (y1 - y2) > 0)
    {
        angle =  qRadiansToDegrees(qAtan(deltaY / deltaX)) + 180;
    } else if ((x1 - x2) < 0 && (y1 - y2) > 0) {
        angle =  (90 - qRadiansToDegrees(qAtan(deltaY / deltaX))) + 270;
    } else if ((x1 - x2) < 0 && (y1 - y2) == 0)
    {
        angle =  0;
    } else if ((x1 - x2) == 0 && (y1 - y2) < 0)
    {
        angle =  90;
    } else if ((x1 - x2) > 0 && (y1 - y2) == 0)
    {
        angle =  180;
    } else if ((x1 - x2) == 0 && (y1 - y2) > 0)
    {
        angle =  270;
    }
    if (angle > 180)
        angle = angle - 360;
    return angle;
}

double CartesianCoordinates::calculateAngleToRemoteRad(CartesianCoordinates *sourceEquipment, CartesianCoordinates *remoteEquipment)
{
    int x1 = sourceEquipment->getCoordinateX();
    int y1 = sourceEquipment->getCoordinateY();
    int x2 = remoteEquipment->getCoordinateX();
    int y2 = remoteEquipment->getCoordinateY();

    double deltaX = qFabs(x1 - x2) + 0.00001;
    double deltaY = qFabs(y1 - y2) + 0.00001;
    double angle = 0;
    if ((x1 - x2) < 0 && (y1 - y2) < 0)
    {
        angle =  (qAtan(deltaY / deltaX));
    } else if ( (x1 - x2) > 0 && (y1 - y2) < 0 )
    {
        angle =  (M_PI/2 - (qAtan(deltaY / deltaX))) + M_PI/2;
    } else if ((x1 - x2) > 0 && (y1 - y2) > 0)
    {
        angle =  (qAtan(deltaY / deltaX)) + M_PI;
    } else if ((x1 - x2) < 0 && (y1 - y2) > 0) {
        angle =  (M_PI/2 - (qAtan(deltaY / deltaX))) + 3*M_PI/2;
    } else if ((x1 - x2) < 0 && (y1 - y2) == 0)
    {
        angle =  0;
    } else if ((x1 - x2) == 0 && (y1 - y2) < 0)
    {
        angle =  M_PI/2;
    } else if ((x1 - x2) > 0 && (y1 - y2) == 0)
    {
        angle =  M_PI;
    } else if ((x1 - x2) == 0 && (y1 - y2) > 0)
    {
        angle =  3*M_PI/2;
    }
    if(angle > M_PI)
        angle = angle - 2 * M_PI;
    return angle;
}

void CartesianCoordinates::setCoordinateX(double x)
{
    posX_ = x;
}

void CartesianCoordinates::setCoordinateY(double y)
{
    posY_ = y;
}

void CartesianCoordinates::setCoordinateZ(double z)
{
    posZ_ = z;
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

void CartesianCoordinates::setAngleX(double angX)
{
    angleX_ = angX;
}

void CartesianCoordinates::setAngleY(double angY)
{
    angleY_ = angY;
}

void CartesianCoordinates::setAngleZ(double angZ)
{
    angleZ_ = angZ;
}

double CartesianCoordinates::getAngleX()
{
    return angleX_;
}

double CartesianCoordinates::getAngleY()
{
    return angleY_;
}

double CartesianCoordinates::getAngleZ()
{
    return angleZ_;
}


// ----- [ CALCULATIONS ] ----------------------------------------------------------------------------------------------

CartesianCoordinates* CartesianCoordinates::operator+(CartesianCoordinates *A)
{
    CartesianCoordinates *Result = new CartesianCoordinates ((getCoordinateX() + A->getCoordinateX()),
                                                             (getCoordinateY() + A->getCoordinateY()),
                                                             (getCoordinateZ() + A->getCoordinateZ()));
    return Result;
}

CartesianCoordinates* CartesianCoordinates::operator-(CartesianCoordinates *B)
{
  CartesianCoordinates *Result =
    new CartesianCoordinates ((getCoordinateX() - B->getCoordinateX()),
                              (getCoordinateY() - B->getCoordinateY()), 
                              (getCoordinateZ() - B->getCoordinateZ()));
  return Result;
}

bool CartesianCoordinates::operator == (CartesianCoordinates C)
{
  if (getCoordinateX() == C.getCoordinateX() &&
      getCoordinateY() == C.getCoordinateY() &&
      getCoordinateZ() == C.getCoordinateZ() )
    {
      return true;
    }
  else
    {
      return false;
    }
}

// ----- [ DEBUG INFORMATION ] -----------------------------------------------------------------------------------------

void CartesianCoordinates::print()
{
    qDebug() << "Current Position: ";
    qDebug() << "Position X: " << posX_;
    qDebug() << "Position Y: " << posY_;
    qDebug() << "Position Z: " << posZ_;
    qDebug() << "Angle X: " << angleX_;
    qDebug() << "Angle Y: " << angleY_;
    qDebug() << "Angle Z: " << angleZ_;
}
