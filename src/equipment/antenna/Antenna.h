#pragma once

#include <QVector>

class Antenna
{  
public:


    // TODO: add antenna patterns
    enum class AntennaPattern
    {
        ONE,
        TWO
    };

private:
    AntennaType type_;
    int         ID_;
    float       antennaGain_; // with beamforming gain
    float       feederLoss_; // assuming with MHA\THA

    // The position inside Antenna Array matrix
    int     positionX_;
    int     positionY_;
    float   length; // in cm (lambda)


    double horizBeamwidth_;
    double vertBeamwidth_;
    double maxHorizAttenuation_;
    double maxVertAttenuation_;

    double bearing_;
    double tilt_;

public:
    Antenna();
    Antenna(int posX, int posY);
    Antenna(int posX, int posY, Antenna::AntennaType type);

    void setAntennaType(Antenna::AntennaType type);
    Antenna::AntennaType getAntennaType();

    void setPosition(int x, int y);

    float calcRadiationPattern(float angle, float absoluteAngle);
};

