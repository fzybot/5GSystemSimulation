#include "Signal.h"

#include <QDebug>
#include <QRandomGenerator>
#include <QtMath>

// ----- [ CONSTRUCTORS\DESTRUCTORS ] ----------------------------------------------------------------------------------

Signal::Signal(QObject *parent):
    QObject(parent),
    index_(-1)
{
    generateData(0, 0, 0);
}

// ----- [ PLOT FUNCTIONS ] --------------------------------------------------------------------------------------------

void Signal::update(QtCharts::QAbstractSeries *series, int seriesIndex)
{
    if (series) {
        QtCharts::QXYSeries *xySeries = static_cast<QtCharts::QXYSeries *>(series);
        const QVector<QVector<QPointF>> &seriesData = data_.at(seriesIndex);
        if (seriesIndex == 0) {
            index_++;
        }
        if (index_ > seriesData.count() - 1) {
            index_ = 0;
        }

        QVector<QPointF> points = seriesData.at(index_);
        xySeries->replace(points);
    }
}

void Signal::handleSceneChanged()
{
    dataUpdater_.start();
}

void Signal::updateAllSeries()
{
    static int frameCount = 0;
    static QString labelText = QStringLiteral("FPS: %1");

    for (int i = 0; i < seriesList_.size(); i++)
        update(seriesList_[i], i);

    frameCount++;
    int elapsed = fpsTimer_.elapsed();
    if (elapsed >= 1000) {
        elapsed = fpsTimer_.restart();
        qreal fps = qreal(0.1 * int(10000.0 * (qreal(frameCount) / qreal(elapsed))));
        // fpsLabel_->setText(labelText.arg(QString::number(fps, 'f', 1)));
        // fpsLabel_->adjustSize();
        frameCount = 0;
    }
}

void Signal::startUpdates(const QList<QtCharts::QXYSeries *> &seriesList) //, QLabel *fpsLabel)
{
    seriesList_ = seriesList;
    //fpsLabel_ = fpsLabel;

    dataUpdater_.setInterval(0);
    dataUpdater_.setSingleShot(true);
    QObject::connect(&dataUpdater_, &QTimer::timeout,
                     this, &Signal::updateAllSeries);

    fpsTimer_.start();
    updateAllSeries();
}

void Signal::generateData(int seriesCount, int rowCount, int colCount)
{
    data_.clear();

    qreal xAdjustment = 20.0 / (colCount * rowCount);
    qreal yMultiplier = 3.0 / qreal(seriesCount);

    // Append the new data depending on the type
    for (int k(0); k < seriesCount; k++) {
        QVector<QVector<QPointF> > seriesData;
        qreal height = qreal(k) * (10.0 / qreal(seriesCount)) + 0.3;
        for (int i(0); i < rowCount; i++) {
            QVector<QPointF> points;
            points.reserve(colCount);
            for (int j(0); j < colCount; j++) {
                qreal x(0);
                qreal y(0);
                // data with sin + random component
                y = height + (yMultiplier * qSin(M_PI / 50 * j)
                              + (yMultiplier * QRandomGenerator::global()->generateDouble()));
                // 0.000001 added to make values logaxis compatible
                x = 0.000001 + 20.0 * (qreal(j) / qreal(colCount)) + (xAdjustment * qreal(i));
                points.append(QPointF(x, y));
            }
            seriesData.append(points);
        }
        data_.append(seriesData);
    }
}
