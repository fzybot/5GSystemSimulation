#pragma once

class Equipment;

class Mobility
{
public:
    Mobility();

    enum MobilityModel
    {
      CONSTANT_POSITION,
      RANDOM_DIRECTION,
      RANDOM_WALK,
      RANDOM_WAYPOINT,
      MANHATTAN,
      LINEAR_MOVEMENT
    };

    void setEquipment(Equipment *equip);
    Equipment getEquipment(void) const;

    void setMobilityModel(MobilityModel model);
    Mobility::MobilityModel getMobilityModel(void) const;

    //TODO: Add cartesian coordinates class
    //void setCartesianPosition(CartesianCoordinates *position);

    void setSpeed(int speed);
    int getSpeed();
    void setAngle(double angle);
    double getAngle();

    void updatePosition(double time);

private:
    Equipment* m_equipment;
    MobilityModel m_mobilityModel;

    int speed;
    double angle;

};

