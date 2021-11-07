#include <QDebug>
#include "Mobility.h"
#include "src/debug.h"

// ----- [ CONSTRUCTORS ] ----------------------------------------------------------------------------------------------

Mobility::Mobility()
{
    setSpeed(0);
    interval_ = 0.;
    lastTimeDirectionChange_ = 0.;
    positionLastUpdate_ = 0;
}

// ----- [ SETTERS\GETTERS ] -------------------------------------------------------------------------------------------

void Mobility::setEquipment(Equipment *equipment)
{
    equipment_ = equipment;
}

Equipment* Mobility::getEquipment(void) const
{
    return equipment_;
}

void Mobility::setModel(Model model)
{
    model_ = model;
}

Mobility::Model Mobility::getModel(void) const
{
    return model_;
}
void Mobility::setPosition(CartesianCoordinates *position)
{
    debug("Mobility: setting position");

    // if (position == nullptr) {
    //     currentPosition_ = nullptr;
    // }
    // if (currentPosition_ == nullptr) {
    //     currentPosition_ = new CartesianCoordinates();
    // }

    currentPosition_ = new CartesianCoordinates();
    currentPosition_->setCoordintes(position->getCoordinateX(), position->getCoordinateY(), position->getCoordinateZ());
    debug("Mobility: currentPosition_:", currentPosition_);
}

CartesianCoordinates* Mobility::getPosition(void) const
{
    return currentPosition_;
}

void Mobility::setSpeed(int speed)
{
    speed_ = speed;
}

int Mobility::getSpeed()
{
    return speed_;
}

void Mobility::setAngle(double angle)
{
    angle_ = angle;
}

double Mobility::getAngle()
{
    return angle_;
}

void Mobility::setPositionLastUpdate(double time)
{
    positionLastUpdate_ = time;
}

double Mobility::getPositionLastUpdate() const
{
    return positionLastUpdate_;
}

void Mobility::deletePosition()
{
    delete currentPosition_;
    delete startPosition_;
}

// ----- [ CALCULATIONS ] ----------------------------------------------------------------------------------------------
void Mobility::updatePosition(double time)
{
    // Created by Ramazan 05.09.2021 ramazanaktaev7@gmail.com

    switch (model_) {
    case Model::CONSTANT_POSITION: break;
    case Model::RANDOM_DIRECTION:
        modelRandomDirection(time);
        break;
    case Model::RANDOM_WALK:
        modelRandomWalk(time);
        break;
    case Model::RANDOM_WAYPOINT:
        modelRandomWaypoint(time);
        break;
    case Model::MANHATTAN:
        modelManhattan(time);
        break;
    case Model::LINEAR_MOVEMENT:
        modelLinearMovement(time);
        break;
    }
}

void Mobility::modelRandomDirection(double time)
{
    // Created by Ramazan 05.09.2021 ramazanaktaev7@gmail.com
}
void Mobility::modelRandomWalk(double time)
{
    // Created by Ramazan 05.09.2021 ramazanaktaev7@gmail.com
    if(getSpeed()==0){
        qDebug() << "speed =0 --> position has not been updated!" << endl;
        return;
    }
    double timeInterval = time - getPositionLastUpdate();

    double shift = timeInterval * (getSpeed()*(1000.0/3600.0));

    double shift_y = shift * sin(getAngle());
    double shift_x = shift * cos(getAngle());

    ///
    CartesianCoordinates *newPosition = new CartesianCoordinates(getPosition()->getCoordinateX() + shift_x,
                                                                 getPosition()->getCoordinateY() + shift_y,
                                                                 getPosition()->getCoordinateZ());
    setPosition(newPosition);
    setPositionLastUpdate(time);
}
void Mobility::modelRandomWaypoint(double time)
{
    // Created by Ramazan 05.09.2021 ramazanaktaev7@gmail.com
}
void Mobility::modelManhattan(double time)
{
    // Created by Ramazan 05.09.2021 ramazanaktaev7@gmail.com
}
void Mobility::modelLinearMovement(double time)
{
    // Created by Ramazan 05.09.2021 ramazanaktaev7@gmail.com
}

// ----- [ DEBUG INFORMATION ] -----------------------------------------------------------------------------------------
// void Mobility::print()
// {
//     qDebug() << "Mobility model: " << mobilityModel_;
//     //getPosition()->print();
// }
