#pragma once


#include <QVector>


class Signal
{
private:
    int sampleRate;

    QVector<QVector<double>> powerValues;
    QVector<QVector<double>> IOvalues;

public:
    Signal();

    void setPowerValues(const QVector<QVector<double>>& powerValues);
    void setIOValues(const QVector<QVector<double>>& IOvalues);

    QVector<QVector<double>> getPowerValues() const;
    QVector<QVector<double>> getIOValues() const;

    void prindIOValues() const;
    void generateRandomIOValues(int MIMOSize, int dataSize);

    virtual ~Signal() = default;
};
