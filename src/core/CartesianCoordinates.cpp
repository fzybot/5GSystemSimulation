#include "CartesianCoordinates.h"
#include <QtMath>
#include <QDebug>

// ----- [ CONSTRUCTORS ] ----------------------------------------------------------------------------------------------
CartesianCoordinates::CartesianCoordinates()
{
    angleX_ = 0;
    angleY_ = 0;
    angleZ_ = 0;

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

// ----- [ SETTERS\GETTERS ] -------------------------------------------------------------------------------------------

void CartesianCoordinates::setCoordintes(double x, double y, double z)
{
    setCoordinateX(x);
    setCoordinateY(y);
    setCoordinateZ(z);
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
