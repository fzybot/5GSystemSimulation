#pragma once


#include <QVector>
#include <QString>
#include <QtCore/QObject>
#include <QtCharts/QXYSeries>
#include <QtWidgets/QLabel>
#include <QtCore/QElapsedTimer>
#include <QtCore/QTimer>
#include <QtMath>

#include <armadillo>

#include "src/visualization/Chartable.h"

class TransportBlock;

class Symbol : public QObject, public Chartable
{
    Q_OBJECT
private:

    int startFrequency_ = 0; // [MHz]
    int startFrequencyHz_ = 0; // [Hz]
    int bandwidth_ = 0;
    int scs_ = 0;
    int sampleRate_ = 0;
    int FFTSize_ = 0;
    int numberOfFreq_ = 0;
    double samplingTime_; // [nanoSec]
    double dopplerFreq_ = 0;
    const int c_ = 3 * qPow(10, 8);

    // For each MIMO layer
    QVector<QVector<bool>>              dataArray_;
    QVector<QVector<bool>>              dataArrayDemodulated_;
    
    QVector<QVector<arma::cx_double>>   modulatedIQ_;
    QVector<QVector<arma::cx_double>>   signalInTime_; // modulatedIQ after IFFT
    QVector<QVector<arma::cx_double>>   signalInFreq_; // timeSignal after FFT
    
    QVector<QVector<arma::cx_double>>   IQvalues_; // phase shift of received signal for each MIMO path and sub-carrier
    
    QVector<QVector<double>>            powerValues_; //transmitted power for each MIMO path and sub-carrier
    QVector<double>                     distance_;

    double averageEVM_ = 0;
    QVector<double> BER_ = {0,0,0,0};

public:
// ----- [ CONSTRUCTORS\DESTRUCTORS ] ----------------------------------------------------------------------------------
    
    Symbol();
    Symbol(int carrierFreq, int SCS, int bandwidth);
    virtual ~Symbol() = default;
    Symbol *copy(void);

// ----- [ SETTERS\GETTERS ] -------------------------------------------------------------------------------------------
    void configSignalSettings(int bandLow, int SCS, int bandwidth);
    void configDopplerSettings(int dSpeed, int angle);

    int     getStartFreqMhz();
    int     getStartFreqHz();
    int     getFFTSize();
    double  getSamplingTime();
    double  getAverageEvm();
    double  getDopplerFreq();

    QVector<QVector<bool>>              &getDataArray();
    QVector<QVector<bool>>              &getDataArrayDemodulated();
    QVector<QVector<arma::cx_double>>   &getModulatedIQ();
    QVector<double>                     &getBER();





    void setPowerValues(const QVector< QVector<double> > powerValues);
    void setIQValues(const QVector<QVector<arma::cx_double>>  IQvalues);

    QVector<QVector<double>>            &getPowerValues();
    QVector<QVector<arma::cx_double>>   &getIQValues();
    QVector<QVector<arma::cx_double>>   &getSignalInTime();
    QVector<QVector<arma::cx_double>>   &getSignalInFreq();

    void generateRandomIQValues(int MIMOSize, int dataSize);
    void fromTbToSignal(QVector<TransportBlock> tbContainer);
    void getDataFromFile(QString filePath);
    void fillRandomData(int mimoSize, int length);

    // ----- [ Calculations ] ----------------------------------------------------------------------------------------------

    void calculateFFTSize();
    void calculateSamplingTime();

    void calculateDoppler(int carrierFreq, double angle, double speed);


    void layersIFFT(QVector<QVector<arma::cx_double>> &modulatedIQ);
    void layersFFT(QVector<QVector<arma::cx_double>> &timeIO);
    QVector<arma::cx_double> IFFT(QVector<arma::cx_double> vector);
    QVector<arma::cx_double> FFT(QVector<arma::cx_double> vector);

    void layersArmaIFFT(QVector<QVector<arma::cx_double>> &modulatedIQ, int size_fft);
    void layersArmaFFT(QVector<QVector<arma::cx_double>> &timeIO, int size_fft);
    QVector<arma::cx_double> armaIFFT(QVector<arma::cx_double> vector, int size_fft);
    QVector<arma::cx_double> armaFFT(QVector<arma::cx_double> vector, int size_fft);
    
    void layersIFFTCarrier( QVector<QVector<arma::cx_double>> &modulatedIQ, int numerology, double speed);
    void layersFFTCarrier(QVector<QVector<arma::cx_double>> &timeIO, int numerology);
    QVector<arma::cx_double> IFFTCarrier(   QVector<arma::cx_double> vector, int numerology, double speed);
    QVector<arma::cx_double> FFTCarrier(QVector<arma::cx_double> vector, int numerology);

    // void IFFT(QVector<arma::cx_double> vector, int size, int freq, int numerology);
    // void dopplerIFFT(QVector<arma::cx_double> vector, int size, int freq, int numerology);

    void normalize(QVector<QVector<arma::cx_double>> &IQ, int byValue);
    void modulateData(int modulationOrder, QVector<QVector<bool>> &dataArray);
    //void modulateDataLayer(int modulationOrder, QVector<QVector<bool>> &dataArray);
    QVector<arma::cx_double> QPSK(QVector<bool> &dataArray);
    QVector<arma::cx_double> QAM16(QVector<bool> &dataArray);
    QVector<arma::cx_double> QAM64(QVector<bool> &dataArray);
    QVector<arma::cx_double> QAM256(QVector<bool> &dataArray);

    void demodulateIQ(int modulationOrder, QVector<QVector<arma::cx_double>> &IQvalues);
    //void demodulateIQLayer(int modulationOrder, QVector<QVector<arma::cx_double>> &IQvalues);
    QVector<bool> demQPSK(QVector<arma::cx_double> &IQvalues);
    QVector<bool> demQAM16(QVector<arma::cx_double> &IQvalues);
    QVector<bool> demQAM64(QVector<arma::cx_double> &IQvalues);
    QVector<bool> demQAM256(QVector<arma::cx_double> &IQvalues);

    double transmitAndReceive(int MO, int speed);
    void compareData();

    // ----- [ Debug ] -----------------------------------------------------------------------------------------------------
    void printIQValues(QVector<QVector<arma::cx_double>> &IQ, QString str = "printIQValues -->");
    void printData(QVector<QVector<bool>> &data);
    void printSignalInfo();
};
