#pragma once

#include <QWidget>
#include <QtWidgets/QWidget>
#include <QtCharts/QChartGlobal>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>

#include "src/visualization/data/DataSource.h"

class QComboBox;
class QCheckBox;
//class QChartView;
//class QChart;


typedef QPair<QPointF, QString> Data;
typedef QList<Data> DataList;
typedef QList<DataList> DataTable;

QT_CHARTS_USE_NAMESPACE


class ChartGroupWidget : public QWidget
{
    Q_OBJECT

private:
    int listCount_;
    int valueMax_;
    int valueCount_;
    QList<QChartView *> charts_;
    DataTable dataTable_;
    DataSource dataSource_;
    

// private Q_SLOTS:
//     void updateUI();

public:
// ----- [ CONSTRUCTORS ] ----------------------------------------------------------------------------------------------
    explicit ChartGroupWidget(QWidget *parent = nullptr);

private:
// ----- [ CALCULATIONS ] ----------------------------------------------------------------------------------------------
    DataTable generateRandomData(int listCount, int valueMax, int valueCount) const;
    DataTable generateRandomData(int listCount) const;

// ----- [ VISUAL SETTINGS ] -------------------------------------------------------------------------------------------
    void populateThemeBox();
    void populateAnimationBox();
    void populateLegendBox();
    void connectSignals();

// ----- [ CREATE CHARTS ] ----------------------------------------------------------------------------------------------
    // production charts
    QChart *createSignalChart();

    // Tutorial Charts
    QChart *createAreaChart() const;
    QChart *createBarChart(int valueCount) const;
    QChart *createPieChart() const;
    QChart *createLineChart() const;
    QChart *createSplineChart() const;
    QChart *createScatterChart() const;
};
