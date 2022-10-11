#pragma once

#include <QVector>
#include <memory>
#include <complex>

class CartesianCoordinates;
class PropagationLossModel;
class PacketBurst;
class Equipment;

class RadioChannel
{

public:
    enum class ChannelModel
    {
      AWGN_CHANNEL,
      RAYLEIGH_CHANNEL,
      RICE_CHANNEL,
      EPA_5HZ,
      EVA_70HZ,
      ETU_300HZ,
      AWGN_DOPPLER_CHANNEL,
      RAYLEIGH_DOPPLER_CHANNEL,
      RICE_DOPPLER_CHANNEL,
      DOPPLER_CHANNEL
      // CHANNEL_MODEL_MACROCELL_URBAN,
      // CHANNEL_MODEL_MACROCELL_SUB_URBAN,
      // CHANNEL_MODEL_MACROCELL_RURAL,
      // CHANNEL_MODEL_MICROCELL,
      // CHANNEL_MODEL_FEMTOCELL_URBAN,
      // CHANNEL_MODEL_3GPP_DOWNLINK,
      // CHANNEL_MODEL_WINNER_DOWNLINK,
      // CHANNEL_MODEL_MACROCELL_URBAN_IMT,
      // CHANNEL_MODEL_MACROCELL_URBAN_IMT_3D,
      // CHANNEL_MODEL_MACROCELL_RURAL_IMT,
      // CHANNEL_MODEL_3GPP_CASE1,
    };
public:
    int _nPath;
    int _noiseValue;
    QVector<Equipment *> *connectedDevices_;
    PropagationLossModel *propagationLossModel_;

    QVector<std::complex<double>> _channelIQ;
    
private:
    QVector<QVector<float>> _pathCharacteristics;
public:
    RadioChannel();
    RadioChannel(RadioChannel::ChannelModel channel_model, int noiseValue, PropagationLossModel *model);
    virtual ~RadioChannel();

    QVector<std::complex<double>> transmitThroughChannel(QVector<std::complex<double>>);

    void setPropagationModel(PropagationLossModel *model);
    void setNoiseVal(int noise);
    void setPathNumber(int nPath);
    int getNumberOfPaths();

    void addDevice(Equipment *e);
    QVector<Equipment*>* getConnectedDevices();
    void delDevice(Equipment *e);
    bool isConnected(Equipment* e);
    void printConnectedDevices();

private:
    void addPath(int pathIndex, float delay, float pathLoss);
    void generateRandomPaths(int number, int maxDistance);
};
