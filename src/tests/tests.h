#pragma once

#include "src/equipment/UserEquipment.h"
#include "src/equipment/gNodeB.h"
#include "src/equipment/Cell.h"
#include "src/core/NetworkManager.h"

#include "calculus_test.h"
#include "packet_test.h"
//#include <fftw3.h>>

//#include "blas.h"
//#include "MatlabDataArray.hpp"


void test_passing(){
    test_sum_dbm();
    vectorTest();

//    matlab::data::ArrayFactory factory;
//    matlab::data::Array A = factory.createArray<double>({ 2,2 },
//        { 1.0, 3.0, 2.0, 4.0 });

//    // Inspect array
//    matlab::data::ArrayType c = A.getType();
//    matlab::data::ArrayDimensions d = A.getDimensions();
//    size_t n = A.getNumberOfElements();
//    qDebug() << "matlab test" << n;
}
