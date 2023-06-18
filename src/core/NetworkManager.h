#pragma once

#include <QVector>
#include <QGeoCoordinate>

class Equipment;
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
        SIGNAL_DOPPLER,
        WO_BUILDINGS,
    };
private:
    int cellIdLocal_;
    int gNbIdLocal_;
    int ueIdLocal_ = 10000;

    QVector<Cell*>         *cellContainer_;
    QVector<gNodeB*>        *gNodeBContainer_;
    QVector<UserEquipment*> *userEquipmentContainer_;

    RadioChannel *_radioChannel;

    SINRCalcMethod methodSINR_;

    // Each time value (granularity) is equal to 1 slot for 120 [kHz] SCS.
    int workit120TimeSlot_;
    int current120TimeSlot_;

public:
    // левый нижний = 54.930053 82.74078
    // верхний правый = 55.140901 83.102854
   QGeoCoordinate _leftBottom = {54.930053, 82.74078};
   QGeoCoordinate _rightUp = {55.140901, 83.102854};
   double _meterSize = 0.00001;

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

    void createRadioChannel();
    RadioChannel *getRadioChannel();
    void addDeviceToRadioChannel(Equipment *equip);
    void setSINRCalcMethod(NetworkManager::SINRCalcMethod method);
    NetworkManager::SINRCalcMethod getSINRCalcMethod();

// ----- [ EQUIPMENT GENERATORS ] --------------------------------------------------------------------------------------
    Cell* createCell (int idCell);
    Cell* createCell (int idCell, CartesianCoordinates *position, double alt, double dist, double angle, double azimuth);
    Cell* createCell (int idCell, gNodeB *targetGNb, int alt, int azimuth);

    gNodeB* createGNodeB (int id, Cell *cell, double posX, double posY, double posZ);
    gNodeB* createGNodeB (int id, double posX, double posY, double posZ);
    gNodeB* createGNodeB (int id, QGeoCoordinate &coordinates);

    UserEquipment* createUserEquipment (int id, 
                                        double posX, double posY, double posZ, 
                                        Cell *cell, gNodeB *targetGNodeB);

    void createMultipleUserEquipments(int number, int lowX, int highX, int lowY, int highY, int borderZ, 
                                   Cell *cell, gNodeB *targetGNodeB);

    void attachUEtoCell(Cell *cell, UserEquipment *ue);
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
    double calculate_sinr_per_user(UserEquipment *user1);
    void calculateSINRPerEquipment(NetworkManager::SINRCalcMethod method);
    void calculateSINRPerEquipment_wo_buildings();
    void calculateSINRPerEquipment_stupid();
    void calculateSINRPerEquipment_signals();
    void calculateSINRPerEquipment_signal_doppler();

    // ----- [ SIMULATION ] ------------------------------------------------------------------------------------------------

    void runNetwork();

    void initialCellSelection(int slot);

    void scheduleGNodeB();

    void scheduleCells(QVector<Cell*> *cellContainer);

    void transmitThroughChannel();
    void fillResourceGridCells(QVector<Cell*> *cellContainer);
    void receiveFromChannel();

    void generateTrafficPerUE(QVector<UserEquipment*> *ueContainer, int slot);

// ----- [ DEBUG INFORMATION ] -----------------------------------------------------------------------------------------

    void print();
};

