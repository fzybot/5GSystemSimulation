#pragma once


/* Antenna modeling by TR 38.901 (page 22)
 *
 *
 */


class Antenna
{
public:
    int gain;
    int type;

public:
    Antenna();

    void setGain(int g);
};
