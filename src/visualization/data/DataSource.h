#pragma once


#include <QtCore/QObject>
#include <QtCharts/QXYSeries>
#include <QtWidgets/QLabel>
#include <QtCore/QElapsedTimer>
#include <QtCore/QTimer>

QT_CHARTS_USE_NAMESPACE

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
    QVector<QVector<QVector<QPointF> > > m_data;
    int m_index;
    QList<QXYSeries *> m_seriesList;
    QLabel *m_fpsLabel;
    QElapsedTimer m_fpsTimer;
    QTimer m_dataUpdater;
};

