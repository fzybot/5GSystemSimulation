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

void Mobility::setMobilityModel(MobilityModel model)
{
    mobilityModel_ = model;
}

Mobility::MobilityModel Mobility::getMobilityModel(void) const
{
    return mobilityModel_;
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



// ----- [ DEBUG INFORMATION ] -----------------------------------------------------------------------------------------
// void Mobility::print()
// {
//     qDebug() << "Mobility model: " << mobilityModel_;
//     //getPosition()->print();
// }
