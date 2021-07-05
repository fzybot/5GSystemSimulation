#pragma once


#include <QWidget>
#include <QImage>
#include <QPaintEvent>
#include <QResizeEvent>


class Heatmap : public QWidget
{
    Q_OBJECT

private:
    int analysisRadius_; // In meters
    int smoothingDegree_;
    int transparency_; // 0 - 100

    QImage heatmap_;


    QRgb signalStrengthToColor(double signalStrength) const;

protected:
    void paintEvent(QPaintEvent*) override;

public:
    Heatmap(QWidget* parent = Q_NULLPTR, int analysisRadius = 3, int smoothingDegree = 2, int transparency = 90);

    void setTransparency(int transparency);
    void generate();
};
