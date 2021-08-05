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

    QVector<QVector<double>> powerValues_;
    QVector<double> signalInTime_;
    QVector<QVector<double>> IOvalues_;

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
    Signal(QObject *parent = 0);
    virtual ~Signal() = default;


// ----- [ SETTERS\GETTERS ] -------------------------------------------------------------------------------------------
    void setPowerValues(const QVector<QVector<double>>& powerValues);
    void setIOValues(const QVector<QVector<double>>& IOvalues);
    void getDataFromFile(QString filePath);

    QVector<QVector<double>> getPowerValues() const;
    QVector<QVector<double>> getIOValues() const;

    void printIOValues() const;
    void generateRandomIOValues(int MIMOSize, int dataSize);

// ----- [ PLOT FUNCTIONS ] --------------------------------------------------------------------------------------------
    void startUpdates(const QList<QtCharts::QXYSeries *> &seriesList); // , QLabel *fpsLabel);
};
