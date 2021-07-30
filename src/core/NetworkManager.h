#pragma once

#include <QVector>

class Cell;
class gNodeB;
class UserEquipment;
class RadioChannel;
class BandwidthManager;
class CartesianCoordinates;

class NetworkManager
{
private:
    QVector<Cell*> *cellContainer_;
    QVector<gNodeB*> *gNodeBContainer_;
    QVector<UserEquipment*> *userEquipmentContainer_;

public:
// ----- [ CONSTRUCTORS\DESTRUCTORS ] ----------------------------------------------------------------------------------
    NetworkManager();
    virtual ~NetworkManager();

// ----- [ SETTERS\GETTERS ] -------------------------------------------------------------------------------------------
    // Get containers
    QVector<Cell*>* getCellContainer (void);
    QVector<gNodeB*>* getGNodeBContainer (void);
    QVector<UserEquipment*>* getUserEquipmentContainer (void);

    // Get by ID
    Cell* getCellByID (int idCell);
    gNodeB* getGNodeBByID (int idGNodeB);
    gNodeB* getGNodeBByCellID (int idCell);
    UserEquipment* getUserEquipmentByID (int idUE);

// ----- [ EQUIPMENT GENERATORS ] --------------------------------------------------------------------------------------
    Cell* createCell (int idCell, double radius, double minDistance, double X, double Y);

    gNodeB* createGnodeb (int id,
                        Cell* cell,
                        double pos_X, double pos_Y,
                        int numTxAntennas, int numRxAntennas,
                        RadioChannel *dlCh, RadioChannel *ulCh,
                        BandwidthManager *bm);

    UserEquipment* createUserEquipment (int id,
                                        double pos_X, double pos_Y, double speed, double speedDirection, 
                                        int numTxAntennas, int numRxAntennas, Cell* cell, gNodeB* gnb);

    void CreateStreet (int idStreet, CartesianCoordinates* center, double theta,
                        int buildingtype, int nbBuildings, double street_width, double building_distance,
                        int nbFemtoInBuilding, double apartment_side, int firstFemtoIDInStreet);

    double* CheckBuildingPosition (int buildingType, double pos_X, double pos_Y, double side_X, double side_Y);
};

