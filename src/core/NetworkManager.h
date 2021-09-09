#pragma once

#include <QVector>

class Cell;
class gNodeB;
class UserEquipment;
class RadioChannel;
class BandwidthManager;
class CartesianCoordinates;
class Mobility;

class NetworkManager
{
private:
    QVector<Cell*> *cellContainer_;
    QVector<gNodeB*> *gNodeBContainer_;
    QVector<UserEquipment*> *userEquipmentContainer_;

    int startTime_;
    int currentTime_;

public:
// ----- [ CONSTRUCTORS\DESTRUCTORS ] ----------------------------------------------------------------------------------
    NetworkManager();
    virtual ~NetworkManager();

// ----- [ SETTERS\GETTERS ] -------------------------------------------------------------------------------------------
    // Get containers
    QVector<Cell*> *getCellContainer (void);
    QVector<gNodeB*> *getGNodeBContainer (void);
    QVector<UserEquipment*> *getUserEquipmentContainer (void);

    // Get by ID
    Cell* getCellByID (int idCell);
    gNodeB* getGNodeBByID (int idGNodeB);
    gNodeB* getGNodeBByCellID (int idCell);
    UserEquipment* getUserEquipmentByID (int idUE);

    // Interworking
    void setWorkingTime(int time); // minimum time unit, 1 slot
    int getWorkingTime();
    void decreaseTime();

    // ----- [ EQUIPMENT GENERATORS ] --------------------------------------------------------------------------------------
    Cell* createCell (int idCell);
    Cell* createCell (int idCell, gNodeB *targetGNb);

    gNodeB* createGNodeB (int id, Cell *cell, double posX, double posY, double posZ);
    gNodeB* createGNodeB (int id, double posX, double posY, double posZ);

    UserEquipment* createUserEquipment (int id, 
                                        double posX, double posY, double posZ, 
                                        Cell *cell, gNodeB *targetGNodeB);

    void createMultipleUserEquipments(int number, int borderID, int lowX, int highX, int lowY, int highY, int borderZ, 
                                   Cell *cell, gNodeB *targetGNodeB);

    void attachUEtoCell(Cell *cell, UserEquipment *ue);
    void attachGNodeBtoCell(Cell *cell, gNodeB *gNb);

    // TODO: all other methods:
    // here should be a list of methods needed for simulation
    void CreateStreet (int idStreet, CartesianCoordinates* center, double theta,
                        int buildingtype, int nbBuildings, double street_width, double building_distance,
                        int nbFemtoInBuilding, double apartment_side, int firstFemtoIDInStreet);

    double* CheckBuildingPosition (int buildingType, double pos_X, double pos_Y, double side_X, double side_Y);

// ----- [ CALCULATIONS ] ----------------------------------------------------------------------------------------------

    double calcOnePointSINR();


// ----- [ DEBUG INFORMATION ] -----------------------------------------------------------------------------------------

    //void print();
};

