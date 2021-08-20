#pragma once

#include <QVector>
#include <memory>

class CartesianCoordinates;
class PropagationLossModel;
class PacketBurst;
class Signal;
class Equipment;

class RadioChannel
{
private:
    int channelId_;

    QVector<Equipment *> *connectedDevices_;

    PropagationLossModel *propagationLossModel_;

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

    void startTx(Signal *txSignal, Equipment* src);
    void startRx(Signal *rxSignal, Equipment* src);

    void addDevice(Equipment *e);
    QVector<Equipment*>* getConnectedDevices();
    void delDevice(Equipment *e);
    bool isConnected(Equipment* e);
};
