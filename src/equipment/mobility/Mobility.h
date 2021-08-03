#pragma once

#include <QVector>
#include "src/core/CartesianCoordinates.h"

class Equipment;

class Mobility
{
public:
    enum MobilityModel
    {
      CONSTANT_POSITION,
      RANDOM_DIRECTION,
      RANDOM_WALK,
      RANDOM_WAYPOINT,
      MANHATTAN,
      LINEAR_MOVEMENT
    };

private:
    Equipment* equipment_;
    MobilityModel mobilityModel_;

    CartesianCoordinates *startPosition_;
    CartesianCoordinates *currentPosition_;
    QVector<CartesianCoordinates> passedPath_;

    int speed_; // Km/h
    double angle_; // in radian

public:
// ----- [ CONSTRUCTORS ] ----------------------------------------------------------------------------------------------
    Mobility();

// ----- [ SETTERS\GETTERS ] -------------------------------------------------------------------------------------------
    void setEquipment(Equipment *equipment);
    Equipment* getEquipment(void) const;

    void setMobilityModel(MobilityModel model);
    Mobility::MobilityModel getMobilityModel(void) const;

    void setPosition(CartesianCoordinates *position);
    CartesianCoordinates* getPosition(void) const;

    void setSpeed(int speed);
    int getSpeed();

    void setAngle(double angle);
    double getAngle();

    void deletePosition();

// ----- [ CALCULATIONS ] ----------------------------------------------------------------------------------------------
    void updatePosition(double time);

// ----- [ DEBUG INFORMATION ] -----------------------------------------------------------------------------------------
    void print();

};

