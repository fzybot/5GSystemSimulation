#pragma once

#include "src/equipment/UserEquipment.h"
#include "src/equipment/gNodeB.h"
#include "src/equipment/Cell.h"
#include "src/core/NetworkManager.h"

#include "calculus_test.h"
#include "packet_test.h"
//#include <fftw3.h>>


void test_passing(){
    test_sum_dbm();
    vectorTest();
}
