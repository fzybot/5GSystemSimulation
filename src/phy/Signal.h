#pragma once


#include <QVector>


class Signal
{
public:
    Signal();
    Signal(int sampleRate, int durationTime);

    void setPowerValues(const QVector<QVector<double>>& powerValues);
    void setIOValues(const QVector<QVector<double>>& IOvalues);

    QVector<QVector<double>> getPowerValues() const;
    QVector<QVector<double>> getIOValues() const;

    void prindIOValues() const;
    void generateRandomIOValues(int MIMOSize, int dataSize);

    virtual ~Signal() = default;

private:
    int sampleRate_;

    QVector<QVector<double>> powerValues_;
    QVector<double> signalInTime_;
    QVector<QVector<double>> IOvalues_;
};
