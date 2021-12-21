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

    // For each MIMO layer
    QVector<bool>                       dataArray_;
    QVector<QVector<bool>>              dataArrayDemodulated_;
    
    QVector<QVector<arma::cx_double>>   modulatedIQ_;

    
    QVector<QVector<arma::cx_double>>   IQvalues_; // phase shift of received signal for each MIMO path and sub-carrier
    QVector<QVector<arma::cx_double>>   signalInTime_;
    QVector<QVector<double>>            powerValues_; //transmitted power for each MIMO path and sub-carrier

    float averageEVM_ = 0;

public:
// ----- [ CONSTRUCTORS\DESTRUCTORS ] ----------------------------------------------------------------------------------
    
    Signal();
    virtual ~Signal() = default;
    Signal *copy(void);

// ----- [ SETTERS\GETTERS ] -------------------------------------------------------------------------------------------
    void configSignalSettings(int bandLow, int SCS, int bandwidth);

    int     getFFTSize();
    double  getSamplingTime();
    float   getAverageEvm();

    QVector<bool>                       &getDataArray();
    QVector<QVector<bool>>              &getDataArrayDemodulated();
    QVector<QVector<arma::cx_double>>   &getModulatedIQ();





    void setPowerValues(const QVector< QVector<double> > powerValues);
    void setIQValues(const QVector<QVector<arma::cx_double>>  IQvalues);

    QVector<QVector<double>>            &getPowerValues();
    QVector<QVector<arma::cx_double>>   &getIQValues();

    void generateRandomIQValues(int MIMOSize, int dataSize);
    void fromTbToSignal(QVector<TransportBlock> tbContainer);
    void getDataFromFile(QString filePath);
    void fillRandomData(int mimoSize, int length);

    // ----- [ Calculations ] ----------------------------------------------------------------------------------------------

    void calculateFFTSize();
    void calculateSamplingTime();

    void normalize(QVector<QVector<arma::cx_double>> &IQ, int byValue);

    void makeIFFT(QVector<arma::cx_double> vector, int size);

    void addDoppler(int carrierFreq, int speed);

    void modulateData(int modulationOrder, QVector<bool> &dataArray);
    QVector<arma::cx_double> QPSK(QVector<bool> &dataArray);
    QVector<arma::cx_double> QAM16(QVector<bool> &dataArray);
    QVector<arma::cx_double> QAM64(QVector<bool> &dataArray);
    QVector<arma::cx_double> QAM256(QVector<bool> &dataArray);

    void demodulate(int modulationOrder, QVector<arma::cx_double> &IQvalues);
    QVector<bool> demQPSK(QVector<arma::cx_double> &IQvalues);
    QVector<bool> demQAM16(QVector<arma::cx_double> &IQvalues);
    QVector<bool> demQAM64(QVector<arma::cx_double> &IQvalues);
    QVector<bool> demQAM256(QVector<arma::cx_double> &IQvalues);

    // ----- [ Debug ] -----------------------------------------------------------------------------------------------------
    void printIQValues(QVector<QVector<arma::cx_double>> &IQ);
};
