#include "ChartGroupWidget.h"
#include "src/visualization/data/DataSource.h"

#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QAbstractBarSeries>
#include <QtCharts/QPercentBarSeries>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QLegend>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QLabel>
#include <QtCore/QRandomGenerator>
#include <QtCharts/QBarCategoryAxis>
#include <QtWidgets/QApplication>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>

// ----- [ CONSTRUCTORS ] ----------------------------------------------------------------------------------------------

ChartGroupWidget::ChartGroupWidget(QWidget *parent) :
    QWidget(parent),
    listCount_(3),
    valueMax_(10),
    valueCount_(7),
    dataSource_(),
    dataTable_(generateRandomData(listCount_, valueMax_, valueCount_))
{
    QGridLayout *grid = new QGridLayout(this);
    grid->setSpacing(2);

    // populateThemeBox();
    // populateAnimationBox();
    // populateLegendBox();

    QChartView *chartView;

    chartView = new QChartView(createSignalChart());
    grid->addWidget(chartView, 0, 0);
    charts_ << chartView;

    chartView = new QChartView(createAreaChart());
    charts_ << chartView;
    grid->addWidget(chartView, 1, 1);

    chartView = new QChartView(createPieChart());
    // Funny things happen if the pie slice labels do not fit the screen, so we ignore size policy
    chartView->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    grid->addWidget(chartView, 1, 0);
    charts_ << chartView;

    chartView = new QChartView(createLineChart());
    grid->addWidget(chartView, 0, 1);
    charts_ << chartView;

    // chartView = new QChartView(createBarChart(valueCount_));
    // grid->addWidget(chartView, 2, 0);
    // charts_ << chartView;

    // chartView = new QChartView(createScatterChart());
    // grid->addWidget(chartView, 2, 2);
    // charts_ << chartView;

    //Set the colors from the light theme as default ones
    QPalette pal = qApp->palette();
    pal.setColor(QPalette::Window, QRgb(0xf0f0f0));
    pal.setColor(QPalette::WindowText, QRgb(0x404044));
    qApp->setPalette(pal);

    setLayout(grid);
}

// ----- [ CALCULATIONS ] ----------------------------------------------------------------------------------------------

DataTable ChartGroupWidget::generateRandomData(int listCount, int valueMax, int valueCount) const
{
    DataTable dataTable;

    // generate random data
    for (int i(0); i < listCount; i++) {
        DataList dataList;
        qreal yValue(0);
        for (int j(0); j < valueCount; j++) {
            yValue = yValue + QRandomGenerator::global()->bounded(valueMax / (qreal) valueCount);
            QPointF value((j + QRandomGenerator::global()->generateDouble()) * ((qreal) valueMax_ /
                                                                                (qreal) valueCount), yValue);
            QString label = "Slice " + QString::number(i) + ":" + QString::number(j);
            dataList << Data(value, label);
        }
        dataTable << dataList;
    }

    return dataTable;
}

// ----- [ VISUAL SETTINGS ] -------------------------------------------------------------------------------------------

// TODO: Finish the settings part

// void ChartsWidget::populateThemeBox()
// {
//     // add items to theme combobox
//     m_ui->themeComboBox->addItem("Light", QChart::ChartThemeLight);
//     m_ui->themeComboBox->addItem("Blue Cerulean", QChart::ChartThemeBlueCerulean);
//     m_ui->themeComboBox->addItem("Dark", QChart::ChartThemeDark);
//     m_ui->themeComboBox->addItem("Brown Sand", QChart::ChartThemeBrownSand);
//     m_ui->themeComboBox->addItem("Blue NCS", QChart::ChartThemeBlueNcs);
//     m_ui->themeComboBox->addItem("High Contrast", QChart::ChartThemeHighContrast);
//     m_ui->themeComboBox->addItem("Blue Icy", QChart::ChartThemeBlueIcy);
//     m_ui->themeComboBox->addItem("Qt", QChart::ChartThemeQt);
// }

// void ChartsWidget::populateAnimationBox()
// {
//     // add items to animation combobox
//     m_ui->animatedComboBox->addItem("No Animations", QChart::NoAnimation);
//     m_ui->animatedComboBox->addItem("GridAxis Animations", QChart::GridAxisAnimations);
//     m_ui->animatedComboBox->addItem("Series Animations", QChart::SeriesAnimations);
//     m_ui->animatedComboBox->addItem("All Animations", QChart::AllAnimations);
// }

// void ChartsWidget::populateLegendBox()
// {
//     // add items to legend combobox
//     m_ui->legendComboBox->addItem("No Legend ", 0);
//     m_ui->legendComboBox->addItem("Legend Top", Qt::AlignTop);
//     m_ui->legendComboBox->addItem("Legend Bottom", Qt::AlignBottom);
//     m_ui->legendComboBox->addItem("Legend Left", Qt::AlignLeft);
//     m_ui->legendComboBox->addItem("Legend Right", Qt::AlignRight);
// }

// ----- [ CREATE CHARTS ] ----------------------------------------------------------------------------------------------

// Production Charts
QChart *ChartGroupWidget::createSignalChart()
{
    QStringList colors;
    colors << "red" << "blue" << "green" << "black";

    QChart *chart = new QChart();
    chart->legend()->hide();

    QValueAxis *axisX = new QValueAxis;
    QValueAxis *axisY = new QValueAxis;
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    const int seriesCount = 10;
    const int pointCount = 1000;
    chart->setTitle("Signal in time");

    QList<QXYSeries *> seriesList;
    for (int i = 0; i < seriesCount; i++) {
        QXYSeries *series = 0;
        int colorIndex = i % colors.size();
        if (i % 2) {
            series = new QScatterSeries;
            QScatterSeries *scatter = static_cast<QScatterSeries *>(series);
            scatter->setColor(QColor(colors.at(colorIndex)));
            scatter->setMarkerSize(qreal(colorIndex + 2) / 2.0);
            // Scatter pen doesn't have affect in OpenGL drawing, but if you disable OpenGL drawing
            // this makes the marker border visible and gives comparable marker size to OpenGL
            // scatter points.
            scatter->setPen(QPen("black"));
        } else {
            series = new QLineSeries;
            series->setPen(QPen(QBrush(QColor(colors.at(colorIndex))),
                                qreal(colorIndex + 2) / 2.0));
        }
        seriesList.append(series);

        series->setUseOpenGL(true);
        
        chart->addSeries(series);
        series->attachAxis(axisX);
        series->attachAxis(axisY);
    }

    if (axisX->type() == QAbstractAxis::AxisTypeLogValue)
        axisX->setRange(0.1, 20.0);
    else
        axisX->setRange(0, 20.0);

    if (axisY->type() == QAbstractAxis::AxisTypeLogValue)
        axisY->setRange(0.1, 10.0);
    else
        axisY->setRange(0, 10.0);

    dataSource_.generateData(seriesCount, 10, pointCount);

    QLabel *fpsLabel = new QLabel(this);
    QLabel *countLabel = new QLabel(this);
    QString countText = QStringLiteral("Total point count: %1");
    countLabel->setText(countText.arg(pointCount * seriesCount));
    countLabel->adjustSize();
    fpsLabel->move(10, 2);
    fpsLabel->adjustSize();
    fpsLabel->raise();
    fpsLabel->show();
    countLabel->move(10, fpsLabel->height());
    fpsLabel->raise();
    countLabel->show();

    QObject::connect(chart->scene(), &QGraphicsScene::changed,
                      &dataSource_, &DataSource::handleSceneChanged);

    dataSource_.startUpdates(seriesList, fpsLabel);

    return chart;
}

// Tutorial Charts
QChart *ChartGroupWidget::createAreaChart() const
{
    QChart *chart = new QChart();
    chart->setTitle("Area chart");

    // The lower series initialized to zero values
    QLineSeries *lowerSeries = 0;
    QString name("Series ");
    int nameIndex = 0;
    for (int i(0); i < dataTable_.count(); i++) {
        QLineSeries *upperSeries = new QLineSeries(chart);
        for (int j(0); j < dataTable_[i].count(); j++) {
            Data data = dataTable_[i].at(j);
            if (lowerSeries) {
                const QVector<QPointF>& points = lowerSeries->pointsVector();
                upperSeries->append(QPointF(j, points[i].y() + data.first.y()));
            } else {
                upperSeries->append(QPointF(j, data.first.y()));
            }
        }
        QAreaSeries *area = new QAreaSeries(upperSeries, lowerSeries);
        area->setName(name + QString::number(nameIndex));
        nameIndex++;
        chart->addSeries(area);
        lowerSeries = upperSeries;
    }

    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).first()->setRange(0, valueCount_ - 1);
    chart->axes(Qt::Vertical).first()->setRange(0, valueMax_);
    // Add space to label to add space between labels and axis
    QValueAxis *axisY = qobject_cast<QValueAxis*>(chart->axes(Qt::Vertical).first());
    Q_ASSERT(axisY);
    axisY->setLabelFormat("%.1f  ");

    return chart;
}

QChart *ChartGroupWidget::createBarChart(int valueCount) const
{
    Q_UNUSED(valueCount);
    QChart *chart = new QChart();
    chart->setTitle("Bar chart");

    QStackedBarSeries *series = new QStackedBarSeries(chart);
    for (int i(0); i < dataTable_.count(); i++) {
        QBarSet *set = new QBarSet("Bar set " + QString::number(i));
        for (const Data &data : dataTable_[i])
            *set << data.first.y();
        series->append(set);
    }
    chart->addSeries(series);

    chart->createDefaultAxes();
    chart->axes(Qt::Vertical).first()->setRange(0, valueMax_ * 2);
    // Add space to label to add space between labels and axis
    QValueAxis *axisY = qobject_cast<QValueAxis*>(chart->axes(Qt::Vertical).first());
    Q_ASSERT(axisY);
    axisY->setLabelFormat("%.1f  ");

    return chart;
}

QChart *ChartGroupWidget::createLineChart() const
{
    //![1]
    QChart *chart = new QChart();
    chart->setTitle("Line chart");
    //![1]

    //![2]
    QString name("Series ");
    int nameIndex = 0;
    for (const DataList &list : dataTable_) {
        QLineSeries *series = new QLineSeries(chart);
        for (const Data &data : list)
            series->append(data.first);
        series->setName(name + QString::number(nameIndex));
        nameIndex++;
        chart->addSeries(series);
    }
    //![2]

    //![3]
    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).first()->setRange(0, valueMax_);
    chart->axes(Qt::Vertical).first()->setRange(0, valueCount_);
    //![3]
    //![4]
    // Add space to label to add space between labels and axis
    QValueAxis *axisY = qobject_cast<QValueAxis*>(chart->axes(Qt::Vertical).first());
    Q_ASSERT(axisY);
    axisY->setLabelFormat("%.1f  ");
    //![4]

    return chart;
}

QChart *ChartGroupWidget::createPieChart() const
{
    QChart *chart = new QChart();
    chart->setTitle("Pie chart");

    QPieSeries *series = new QPieSeries(chart);
    for (const Data &data : dataTable_[0]) {
        QPieSlice *slice = series->append(data.second, data.first.y());
        if (data == dataTable_[0].first()) {
            // Show the first slice exploded with label
            slice->setLabelVisible();
            slice->setExploded();
            slice->setExplodeDistanceFactor(0.5);
        }
    }
    series->setPieSize(0.4);
    chart->addSeries(series);

    return chart;
}

QChart *ChartGroupWidget::createSplineChart() const
{
    QChart *chart = new QChart();
    chart->setTitle("Spline chart");
    QString name("Series ");
    int nameIndex = 0;
    for (const DataList &list : dataTable_) {
        QSplineSeries *series = new QSplineSeries(chart);
        for (const Data &data : list)
            series->append(data.first);
        series->setName(name + QString::number(nameIndex));
        nameIndex++;
        chart->addSeries(series);
    }

    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).first()->setRange(0, valueMax_);
    chart->axes(Qt::Vertical).first()->setRange(0, valueCount_);

    // Add space to label to add space between labels and axis
    QValueAxis *axisY = qobject_cast<QValueAxis*>(chart->axes(Qt::Vertical).first());
    Q_ASSERT(axisY);
    axisY->setLabelFormat("%.1f  ");
    return chart;
}

QChart *ChartGroupWidget::createScatterChart() const
{
    // scatter chart
    QChart *chart = new QChart();
    chart->setTitle("Scatter chart");
    QString name("Series ");
    int nameIndex = 0;
    for (const DataList &list : dataTable_) {
        QScatterSeries *series = new QScatterSeries(chart);
        for (const Data &data : list)
            series->append(data.first);
        series->setName(name + QString::number(nameIndex));
        nameIndex++;
        chart->addSeries(series);
    }

    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).first()->setRange(0, valueMax_);
    chart->axes(Qt::Vertical).first()->setRange(0, valueCount_);
    // Add space to label to add space between labels and axis
    QValueAxis *axisY = qobject_cast<QValueAxis*>(chart->axes(Qt::Vertical).first());
    Q_ASSERT(axisY);
    axisY->setLabelFormat("%.1f  ");
    return chart;
}
