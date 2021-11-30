#pragma once


#include <QVector>
#include <QString>
#include <QtCore/QObject>
#include <QtCharts/QXYSeries>
#include <QtWidgets/QLabel>
#include <QtCore/QElapsedTimer>
#include <QtCore/QTimer>

class TransportBlock;

class Signal : public QObject
{
    Q_OBJECT
private:
    int sampleRate_;
    int FFTSize_;

    QVector<QVector<double>> powerValues_; //transmitted power for each MIMO path and sub-carrier
    QVector<QVector<double>> IOvalues_; //phase shift of received signal for each MIMO path and sub-carrier
    QVector<double> signalInTime_;

public:
// ----- [ CONSTRUCTORS\DESTRUCTORS ] ----------------------------------------------------------------------------------
    Signal();
    virtual ~Signal() = default;


// ----- [ SETTERS\GETTERS ] -------------------------------------------------------------------------------------------
    void setPowerValues(const QVector< QVector<double> > powerValues);
    void setIOValues(const QVector< QVector<double> >  IOvalues);


    QVector<QVector<double>> getPowerValues(void);
    QVector<QVector<double>> getIOValues(void);

    Signal *copy(void);

    void printIOValues() const;
    void generateRandomIOValues(int MIMOSize, int dataSize);

    void fromTbToSignal(QVector<TransportBlock> tbContainer);

    void getDataFromFile(QString filePath);

// ----- [ PLOT FUNCTIONS ] --------------------------------------------------------------------------------------------
};
