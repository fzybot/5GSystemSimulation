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

    QVector<bool> dataArray_;

    int startFrequency_ = 0;
    int bandwidth_ = 0;
    int scs_ = 0;
    int sampleRate_ = 0;
    int FFTSize_ = 0;
    double samplingTime_; // [nanoSec]

    // For each MIMO layer
    QVector<QVector<double>>            powerValues_; //transmitted power for each MIMO path and sub-carrier
    QVector<arma::Col<arma::cx_double>> IOvalues_; //phase shift of received signal for each MIMO path and sub-carrier
    QVector<arma::Col<arma::cx_double>> signalInTime_;

public:
// ----- [ CONSTRUCTORS\DESTRUCTORS ] ----------------------------------------------------------------------------------
    Signal();
    virtual ~Signal() = default;

    Signal *copy(void);


// ----- [ SETTERS\GETTERS ] -------------------------------------------------------------------------------------------
    void configSignalSettings(int bandLow, int SCS, int bandwidth);

    int getFFTSize();
    double getSamplingTime();

    void setPowerValues(const QVector< QVector<double> > powerValues);
    void setIOValues(const QVector<arma::Col<arma::cx_double>>  IOvalues);


    QVector<QVector<double>> &getPowerValues();
    QVector<arma::Col<arma::cx_double>> &getIOValues();


    void generateRandomIOValues(int MIMOSize, int dataSize);
    void fromTbToSignal(QVector<TransportBlock> tbContainer);
    void getDataFromFile(QString filePath);
    void fillRandomData(int mimoSize, int length);

// ----- [ Calculations ] ----------------------------------------------------------------------------------------------

    void calculateFFTSize();
    void calculateSamplingTime();


// ----- [ Debug ] -----------------------------------------------------------------------------------------------------
     void printIOValues();
};
