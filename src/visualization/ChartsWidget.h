#pragma once

#include <QWidget>
#include <QtWidgets/QWidget>
#include <QtCharts/QChartGlobal>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>

QT_BEGIN_NAMESPACE
class QComboBox;
class QCheckBox;
class Ui_ThemeWidgetForm;
QT_END_NAMESPACE

QT_CHARTS_BEGIN_NAMESPACE
class QChartView;
class QChart;
QT_CHARTS_END_NAMESPACE

typedef QPair<QPointF, QString> Data;
typedef QList<Data> DataList;
typedef QList<DataList> DataTable;

QT_CHARTS_USE_NAMESPACE


class ChartsWidget : public QWidget
{
    Q_OBJECT
private:
    int m_listCount;
    int m_valueMax;
    int m_valueCount;
    QList<QChartView *> m_charts;
    DataTable m_dataTable;

// private Q_SLOTS:
//     void updateUI();

private:
// ----- [ CALCULATIONS ] ----------------------------------------------------------------------------------------------
    DataTable generateRandomData(int listCount, int valueMax, int valueCount) const;

// ----- [ VISUAL SETTINGS ] -------------------------------------------------------------------------------------------
    void populateThemeBox();
    void populateAnimationBox();
    void populateLegendBox();
    void connectSignals();

// ----- [ CREATE CHARTS ] ----------------------------------------------------------------------------------------------
    QChart *createAreaChart() const;
    QChart *createBarChart(int valueCount) const;
    QChart *createPieChart() const;
    QChart *createLineChart() const;
    QChart *createSplineChart() const;
    QChart *createScatterChart() const;

public:
// ----- [ CONSTRUCTORS ] ----------------------------------------------------------------------------------------------
    explicit ChartsWidget(QWidget *parent = nullptr);
};

