#include "Mobility.h"

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
    if (position == nullptr) {
        currentPosition_ = nullptr;
        return;
    }
    if (currentPosition_ == nullptr) {
        currentPosition_ = new CartesianCoordinates();
    }

    currentPosition_->setCoordinateX(position->getCoordinateX());
    currentPosition_->setCoordinateY(position->getCoordinateY());
    currentPosition_->setCoordinateZ(position->getCoordinateZ());
}

CartesianCoordinates* Mobility::getPosition(void) const
{
    return currentPosition_;
}

// ----- [ CALCULATIONS ] ----------------------------------------------------------------------------------------------
