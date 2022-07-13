#pragma once
#include <QDebug>
#include "src/additionalCalculations.h"

void test_sum_dbm(){
    qDebug() << sum_dBm(23, 20);
    qDebug() << sum_dBm(20, 23);
    qDebug() << sum_dBm(-123, -110);
}
