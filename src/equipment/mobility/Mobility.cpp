#include <QDebug>
#include "Mobility.h"
#include "src/debug.h"

// ----- [ CONSTRUCTORS ] ----------------------------------------------------------------------------------------------

Mobility::Mobility()
{

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
        modelManhattan(time);
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
