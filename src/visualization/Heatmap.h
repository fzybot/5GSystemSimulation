#pragma once


#include <QQuickWidget>
#include <QImage>
#include <QPixmap>

class Heatmap : public QPixmap
{
private:
    int analysisRadius_; // In meters
    int smoothingDegree_;
    int transparency_; // 0 - 100
    QImage map_;

    QRgb signalStrengthToColor(double signalStrength) const;

public:
    Heatmap(int width, int height, int analysisRadius = 3, int smoothingDegree = 2, int transparency = 80);

    void setTransparency(int transparency);
    void generate();
};
