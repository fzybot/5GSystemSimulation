#ifndef TEST_ANTENNA_ARRAY_H
#define TEST_ANTENNA_ARRAY_H

#include "src/protocols/phy/AntennAarrayNR.h"

void antennaArray(){
    AntennaArrayNR ant;
    ant.config(10, 10, AntennaArrayNR::AntennaType::ANTENNA_TYPE_3GPP_3D, 1, 4, 120);
}
#endif // TEST_ANTENNA_ARRAY_H
