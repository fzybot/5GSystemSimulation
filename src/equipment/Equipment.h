#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <src/commonParameters.h>

class Equipment {

public:

    /* Coordinates & Geometry for spherical basis
     * According to 3GPP TS38.901:
     *  latitude is 'y' axis
     *  lontitude is 'x' axis
     *  altitude is  'z' axis (height above the sea)
     *
     *  angles:
     *      lonAngle - 'fi'
     *      latAngle - '0'
     */

    double altitude = 0;
    double longtitude;
    double latitude;

    double lonAngle = 0;
    double latAngle = 0;

    double height;



    // Power parameters
    double maxPowerInDbm;

    // Frequency parameters
    int ARFCN = 0;
    int numerologyIndex = 0;
    int SCS = NUMEROLOGY[numerologyIndex];
    int bandwidth;
    int carrierFrequency; // in Mhz




public:
    Equipment(){
        this->bandwidth = 10;
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
