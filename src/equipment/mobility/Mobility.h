#pragma once

#include <QVector>
#include "src/core/CartesianCoordinates.h"
#include <QtMath>
#include <time.h>
#include <random>

class Equipment;

class Mobility
{
public:
    enum class Model
    {
      CONSTANT_POSITION,
      RANDOM_DIRECTION,
      RANDOM_WALK,
      RANDOM_WAYPOINT,
      MANHATTAN,
      LINEAR_MOVEMENT,
      GAUSS_MARKOV
    };

protected:
    Equipment* equipment_;
    Model model_;

    CartesianCoordinates *startPosition_;
    CartesianCoordinates *currentPosition_;
    QVector<CartesianCoordinates> passedPath_;

    int speed_; // Km/h
    double angle_; // in radian
    double interval_;
    double lastTimeDirectionChange_;
    double positionLastUpdate_;
    int changeSpeedCount_;
    int changeAngleCount_;
    double averageSpeed_;
    double sumSpeed_;
    double averageAngle_;
    double sumAngle_;
    double alpha_;

    double topBorder_,bottomBorder_,leftBorder_,rightBorder_;
    double borderZone_;
    int speedMin_, speedMax_;
    CartesianCoordinates *moveToPosition_;
    double pauseTime_;
    double tempPauseTime_;

    std::mt19937 gen; //generator

public:
// ----- [ CONSTRUCTORS ] ----------------------------------------------------------------------------------------------
    Mobility();

// ----- [ SETTERS\GETTERS ] -------------------------------------------------------------------------------------------
    void setEquipment(Equipment *equipment);
    Equipment* getEquipment(void) const;

    void setModel(Model model);
    Mobility::Model getModel(void) const;

    void setPosition(CartesianCoordinates *position);
    CartesianCoordinates* getPosition(void) const;

    void setSpeed(int speed);
    int getSpeed();
    void setAngle(double angle);
    double getAngle();
    void setPositionLastUpdate(double time);
    double getPositionLastUpdate(void) const;
    void setAlpha(double alpha);
    double getAlpha();
    void setBorders(double top, double bottom, double left, double right);
    void setBorderZone(double zone);
    int isInZone(CartesianCoordinates *position);
    void setMaxSpeed(int);
    void setMinSpeed(int);
    void forceStayInArea(CartesianCoordinates *position);
    void setMovePosition(double lon, double lat);
    void setPauseTime(double pauseTime);

    void deletePosition();

// ----- [ CALCULATIONS ] ----------------------------------------------------------------------------------------------
    void updatePosition(double time);

    void modelRandomDirection(double time);
    void modelRandomWalk(double time);
    void modelRandomWaypoint(double time);
    void modelManhattan(double time);
    void modelLinearMovement(double time);
    void modelGaussMarkov(double time);

// ----- [ DEBUG INFORMATION ] -----------------------------------------------------------------------------------------
    // void print();
};

