#pragma once

#include <QVector>
#include <memory>

#include "src/equipment/Equipment.h"

class CartesianCoordinates;
class PropagationLossModel;
class PacketBurst;

class RadioChannel
{
public:
    enum ChannelModel
    {
      CHANNEL_MODEL_MACROCELL_URBAN,
      CHANNEL_MODEL_MACROCELL_SUB_URBAN,
      CHANNEL_MODEL_MACROCELL_RURAL,
      CHANNEL_MODEL_MICROCELL,
      CHANNEL_MODEL_FEMTOCELL_URBAN,
      CHANNEL_MODEL_3GPP_DOWNLINK,
      CHANNEL_MODEL_WINNER_DOWNLINK,
      CHANNEL_MODEL_MACROCELL_URBAN_IMT,
      CHANNEL_MODEL_MACROCELL_URBAN_IMT_3D,
      CHANNEL_MODEL_MACROCELL_RURAL_IMT,
      CHANNEL_MODEL_3GPP_CASE1,
    };

    RadioChannel();
    //virtual ~RadioChannel();

    void StartTransmission();
    void StartReception();

    void addDevice(Equipment *e);
    void delDevice(Equipment* e);
    bool isConnected(Equipment* e);

private:
    QVector<Equipment*> connectedDevices_;

    PropagationLossModel* propagationLossModel_;
};
