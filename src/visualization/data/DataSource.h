#pragma once


#include <QtCore/QObject>
#include <QtCharts/QXYSeries>
#include <QtWidgets/QLabel>
#include <QtCore/QElapsedTimer>
#include <QtCore/QTimer>
#include <QtWidgets/QWidget>
#include <QtCharts/QChartGlobal>
#include <QtCharts>

QT_CHARTS_USE_NAMESPACE
using namespace QtCharts;

class DataSource : public QObject
{
    Q_OBJECT
public:
    explicit DataSource(QObject *parent = 0);

    void startUpdates(const QList<QXYSeries *> &seriesList,  QLabel *fpsLabel);

public slots:
    void generateData(int seriesCount, int rowCount, int colCount);
    void update(QAbstractSeries *series, int seriesIndex);
    void handleSceneChanged();
    void updateAllSeries();

private:
    QVector<QVector<QVector<QPointF> > > data_;
    int index_;
    QList<QXYSeries *> seriesList_;
    QLabel *fpsLabel_;
    QElapsedTimer fpsTimer_;
    QTimer dataUpdater_;
};

