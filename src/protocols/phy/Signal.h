#pragma once


#include <QVector>
#include <QString>
#include <QtCore/QObject>
#include <QtCharts/QXYSeries>
#include <QtWidgets/QLabel>
#include <QtCore/QElapsedTimer>
#include <QtCore/QTimer>

#include <armadillo>

#include "src/visualization/Chartable.h"

class TransportBlock;

class Signal : public QObject, public Chartable
{
    Q_OBJECT
private:

    int startFrequency_ = 0;
    int bandwidth_ = 0;
    int scs_ = 0;
    int sampleRate_ = 0;
    int FFTSize_ = 0;
    double samplingTime_; // [nanoSec]

    QVector<QVector<double>>                powerValues_; //transmitted power for each MIMO path and sub-carrier
    QVector<QVector<QPair<float, float>>>   IOvalues_; //phase shift of received signal for each MIMO path and sub-carrier
    QVector<QPair<float, float>>            signalInTime_;

public:
// ----- [ CONSTRUCTORS\DESTRUCTORS ] ----------------------------------------------------------------------------------
    Signal();
    virtual ~Signal() = default;


// ----- [ SETTERS\GETTERS ] -------------------------------------------------------------------------------------------
    void configSignalSettings(int bandLow, int SCS, int bandwidth);

    int getFFTSize();
    double getSamplingTime();

    void setPowerValues(const QVector< QVector<double> > powerValues);
    void setIOValues(const QVector< QVector<QPair<float, float>> >  IOvalues);


    QVector<QVector<double>> &getPowerValues();
    QVector<QVector<QPair<float, float>>> &getIOValues();

    Signal *copy(void);

    void printIOValues() const;
    void generateRandomIOValues(int MIMOSize, int dataSize);

    void fromTbToSignal(QVector<TransportBlock> tbContainer);

    void getDataFromFile(QString filePath);

// ----- [ Calculations ] ----------------------------------------------------------------------------------------------

    void calculateFFTSize();
    void calculateSamplingTime();
};
