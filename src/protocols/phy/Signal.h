#pragma once


#include <QVector>
#include <QString>
#include <QtCore/QObject>
#include <QtCharts/QXYSeries>
#include <QtWidgets/QLabel>
#include <QtCore/QElapsedTimer>
#include <QtCore/QTimer>


class Signal : public QObject
{
    Q_OBJECT
private:
    int sampleRate_;
    int FFTSize_;

    QVector<QVector<double>> powerValues_; //transmitted power for each MIMO path and sub-carrier
    QVector<QVector<double>> IOvalues_; //phase shift of received signal for each MIMO path and sub-carrier
    QVector<double> signalInTime_;

// Visualization
    QVector<QVector<QVector<QPointF> > > data_;
    int index_;
    QList<QtCharts::QXYSeries *> seriesList_;
    QLabel *fpsLabel_;
    QElapsedTimer fpsTimer_;
    QTimer dataUpdater_;

public slots:
    void generateData(int seriesCount, int rowCount, int colCount);
    void update(QtCharts::QAbstractSeries *series, int seriesIndex);
    void handleSceneChanged();
    void updateAllSeries();

public:
// ----- [ CONSTRUCTORS\DESTRUCTORS ] ----------------------------------------------------------------------------------
    Signal(bool backend);
    Signal(QObject *parent = 0);
    virtual ~Signal() = default;


// ----- [ SETTERS\GETTERS ] -------------------------------------------------------------------------------------------
    void setPowerValues(const QVector< QVector<double> > powerValues);
    void setIOValues(const QVector< QVector<double> >  IOvalues);


    QVector<QVector<double>> getPowerValues(void);
    QVector<QVector<double>> getIOValues(void);

    Signal *copy(void);

    void printIOValues() const;
    void generateRandomIOValues(int MIMOSize, int dataSize);

    void getDataFromFile(QString filePath);

// ----- [ PLOT FUNCTIONS ] --------------------------------------------------------------------------------------------
    void startUpdates(const QList<QtCharts::QXYSeries *> &seriesList); // , QLabel *fpsLabel);
};
