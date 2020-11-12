#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <src/commonParameters.h>

class Equipment {
public:

    // Coordinates
    double altitude = 0;
    double longtitude;
    double latitude;

    double altAngle = 0;
    double lonAngle;
    double latAngle;


    // Power parameters
    double maxPowerInDbm = 43;

    // Frequency parameters
    int ARFCN = 0;
    int numerologyIndex = 0;
    int SCS = numerology[numerologyIndex];



public:
    Equipment(){

    }

    void setLatitude(double lat){
        this->latitude = lat;
    }

    void setLontitude(double lon){
        this->longtitude = lon;
    }

    void setAltitude(double alt){
        this->altitude = alt;
    }


};

#endif // EQUIPMENT_H
