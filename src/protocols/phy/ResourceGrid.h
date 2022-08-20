#pragma once

#include <QVector>
#include <complex>

class Bandwidth;

class ResourceGrid
{

public:
    // _resourceGrid[i][j] - 'i' representing OFDM-symbol number, 'j' representing subcarrier number
    QVector< QVector<int> > _inputData;
    QVector< QVector<std::complex<double>> > _freqModulatedIQ;
    QVector< QVector<std::complex<double>> > _resourceGrid;
    QVector< QVector<std::complex<double>> > _resourceGridChannelIQ;
    QVector< QVector<std::complex<double>> > _resourceGridChannelDopplerIQ;
    QVector< QVector<std::complex<double>> > _resourceGridChannelOnlyDopplerIQ;
    QVector< QVector<std::complex<double>> > _freqDemodulatedIQ;

    Bandwidth *_bw;

public:
    ResourceGrid();

    void setBw(Bandwidth *bw);
    Bandwidth *getBw();

    void configResourceGrid(Bandwidth *bw);
    void mapDmrs(QVector<QVector<int>> &dmrsPattern);
    void mapCoreset(QVector<QVector<int>> &coresetPattern);
    void mapData(QVector<QVector<int>> &data);

    void transmit(QVector<QVector<std::complex<double>>> channelIQ);
    void receive();
    QVector<QVector<int>> &getResourceGrid();
};

