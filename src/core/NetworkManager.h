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
public:
    enum class SINRCalcMethod
    {
        STUPID,
        SIGNAL,
        SIGNAL_DOPPLER
    };
private:
    int cellIdLocal_;
    int gNbIdLocal_;
    int ueIdLocal_ = 10000;

    QVector<Cell *>         *cellContainer_;
    QVector<gNodeB*>        *gNodeBContainer_;
    QVector<UserEquipment*> *userEquipmentContainer_;

    SINRCalcMethod methodSINR_;

    // Each time value (granularity) is equal to 1 slot for 120 [kHz] SCS.
    int workit120TimeSlot_;
    int current120TimeSlot_;

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
    int &getCurrentTime();
    int &getWorkingTime();
    void increaseCurrentTime();

    void setSINRCalcMethod(NetworkManager::SINRCalcMethod method);
    NetworkManager::SINRCalcMethod getSINRCalcMethod();

// ----- [ EQUIPMENT GENERATORS ] --------------------------------------------------------------------------------------
    Cell* createCell (int idCell);
    Cell* createCell (int idCell, double posX, double posY, double posZ);
    Cell* createCell (int idCell, gNodeB *targetGNb);

    gNodeB* createGNodeB (int id, Cell *cell, double posX, double posY, double posZ);
    gNodeB* createGNodeB (int id, double posX, double posY, double posZ);

    UserEquipment* createUserEquipment (int id, 
                                        double posX, double posY, double posZ, 
                                        Cell *cell, gNodeB *targetGNodeB);

    void createMultipleUserEquipments(int number, int lowX, int highX, int lowY, int highY, int borderZ, 
                                   Cell *cell, gNodeB *targetGNodeB);

    void attachUEtoCell(Cell *cell, UserEquipment *ue);
    void detachUeFromCell(Cell *cell, UserEquipment *ue, int reason);
    void deleteUeFromOtherCells(Cell *targetCell, UserEquipment *targetUe);
    void attachGNodeBtoCell(Cell *cell, gNodeB *gNb);

    // TODO: all other methods:
    // here should be a list of methods needed for simulation
    void CreateStreet (int idStreet, CartesianCoordinates* center, double theta,
                        int buildingtype, int nbBuildings, double street_width, double building_distance,
                        int nbFemtoInBuilding, double apartment_side, int firstFemtoIDInStreet);

    double* CheckBuildingPosition (int buildingType, double pos_X, double pos_Y, double side_X, double side_Y);

// ----- [ CALCULATIONS ] ----------------------------------------------------------------------------------------------

    bool checkHandOver();
    void makeHandOver();

    float calculatePathLosses(Cell *cell, UserEquipment *user);
    float calculatePathLosses(UserEquipment *user1, UserEquipment *user2);
    // 'Equipment' is equal to 'Cell' & 'UserEquipment'
    double calcOnePointSINR();
    void calculateSINRPerEquipment(NetworkManager::SINRCalcMethod method);
    void calculateSINRPerEquipment_stupid();
    void calculateSINRPerEquipment_signals();
    void calculateSINRPerEquipment_signal_doppler();

// ----- [ SIMULATION ] ------------------------------------------------------------------------------------------------

    void runNetwork();

    void initialCellSelection(int slot);
    void pathLosDetach();

    void scheduleGNodeB();

    void scheduleCells(QVector<Cell*> *cellContainer);

    void generateTrafficPerUE(QVector<UserEquipment*> *ueContainer);

// ----- [ DEBUG INFORMATION ] -----------------------------------------------------------------------------------------

    void print();
};

