#ifndef SETTINGSTEMPLATE_H
#define SETTINGSTEMPLATE_H

typedef struct settings{
    int numberOfCell;
    int band;
    int numerology;
    int bandwidth;
    int channelModel;
    int dopplerUsage;

    int numberOfUEs;
    int mobilityModel;
    int ueDistribution;

    double cellTxPower;
    double cellFeederLos;
    int antennaConfig;
    double cellAntennaGain;
    double cellNoiseFigure;
    int propagationModel;
    int heightUsage;
    int buildingsUsage;

    double ueTxPower;
    double ueFeederLos;
    double ueAntennaGain;
    double ueNoiseFigure;


}SettingsTemplate;

#endif // SETTINGSTEMPLATE_H
