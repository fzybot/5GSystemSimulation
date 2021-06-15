#include "bandwidth.h"
#include <iostream>
#include <stdio.h>
#include <QMap>


// first element is the bandwidth in MHz, second one is the corresponding number of RBs
const static Qmap::map<double, int> RBs_for_BW =
  {
    { 1.4, 6 },
    { 3, 15 },
    { 5, 25 },
    { 10, 50 },
    { 15, 75 },
    { 20, 100 } };


Bandwidth::Bandwidth()
{

}
