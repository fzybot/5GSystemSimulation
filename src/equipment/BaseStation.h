#ifndef BASESTATION_H
#define BASESTATION_H

#include <src/equipment/Equipment.h>


class BaseStation : public Equipment{
public:

    // Logistic information
    int PCI;
    int cellIdentity;

};


#endif // BASESTATION_H
