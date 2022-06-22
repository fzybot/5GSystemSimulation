#pragma once

#include <QVector>
#include <complex>

class ResourceGrid
{

public:
    // _resourceGrid[i][j] - 'i' representing OFDM-symbol number, 'j' representing subcarrier number
    QVector<QVector<std::complex<double>>> _resourceGrid;
    QVector<QVector<std::complex<double>>> _resourceGridChannel;
    QVector<QVector<std::complex<double>>> _resourceGridReceived;

public:
    ResourceGrid(int nPrb, int nOfdmSymbols, QVector<QVector<int>> &dmrsPattern, QVector<QVector<int>> &coresetPattern);

    void createResourceGrid(int nPrb, int nOfdmSymbols);
    void mapDmrs(QVector<QVector<int>> &dmrsPattern);
    void mapCoreset(QVector<QVector<int>> &coresetPattern);
    void mapData(QVector<QVector<std::complex<double>>>);

    void transmit(QVector<QVector<std::complex<double>>> channelIQ);
    void receive();
    QVector<QVector<int>> &getResourceGrid();
};

