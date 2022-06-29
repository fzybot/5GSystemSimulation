#include "Chartable.h"

#include <QDebug>
#include <QtMath>
#include <QtDataVisualization/Q3DSurface>
#include <QtWidgets>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLineSeries>

#include "src/visualization/Custom3dSurface.h"

Chartable::Chartable()
{

}

void Chartable::visualize3D()
{
    QtDataVisualization::Q3DSurface *graph = new QtDataVisualization::Q3DSurface();
    QWidget *container = QWidget::createWindowContainer(graph);
    container->setMinimumSize(800, 600);
    container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    container->setFocusPolicy(Qt::StrongFocus);
    surface_ = new Custom3dSurface(graph, dataArray3d_);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(container);

    container->show();
}

void Chartable::visualize2D(QVector<QVector<QPair<double, double>>> data, QString plotName, QVector<QString> seriesName, int minY, int maxY)
{
    QtCharts::QChartView *chartView;
    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->setTitle(plotName);
    chartView->setRubberBand(QtCharts::QChartView::HorizontalRubberBand);
    int nameIndex = 0;
    for (auto list : data) {
        QtCharts::QLineSeries *series = new QtCharts::QLineSeries(chart);
        for (auto element : list)
            series->append(element.first, element.second);
        series->setName(seriesName[nameIndex]);
        nameIndex++;
        chart->addSeries(series);
    }

    chart->createDefaultAxes();
    // chart->axes(Qt::Horizontal).first()->setRange(0, 20);
    //chart->axes(Qt::Vertical).first()->setRange(minY, maxY);

    // Add space to label to add space between labels and axis
    QtCharts::QValueAxis *axisY = qobject_cast<QtCharts::QValueAxis*>(chart->axes(Qt::Vertical).first());
    Q_ASSERT(axisY);
    axisY->setLabelFormat("%d  ");
    axisY->setRange(minY, maxY);

    chartView = new QtCharts::QChartView(chart);

    QWidget *container = new QWidget();
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(chartView);
    container->setMinimumSize(800, 600);
    container->setLayout(mainLayout);
    container->show();
}
