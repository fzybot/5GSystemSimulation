#ifndef ANTENNA_H
#define ANTENNA_H

/* Antenna modeling by TR 38.901 (page 22)
 *
 *
 */


class Antenna{

public:

    int gain;

public:
    Antenna(){

    }

    void setGain(int g){
        this->gain = g;
    }
};



#endif // ANTENNA_H
