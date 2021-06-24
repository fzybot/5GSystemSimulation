#include "Heatmap.h"

#include <QVector>
#include <QtMath>


// ----- [ CONSTRUCTORS ] ----------------------------------------------------------------------------------------------

Heatmap::Heatmap(int width, int height, int analysisRadius, int smoothingDegree, int transparency) :
    QPixmap(width, height),
    analysisRadius_(analysisRadius),
    smoothingDegree_(smoothingDegree),
    transparency_(transparency),
    map_(width, height, QImage::Format_ARGB32)
{
#pragma region TemporaryCode // No real data yet
    analysisRadius_ *= 100.0;
#pragma endregion TemporaryCode
}



// ----- [ PRIVATE METHODS ] -------------------------------------------------------------------------------------------

QRgb Heatmap::signalStrengthToColor(double signalStrength) const
{
    static int redChannel, greenChannel, blueChannel;

    if (signalStrength <= -120.0) { // Blue
        return qRgba(0, 0, 255, transparency_);
    }
    else if (signalStrength <= -105.0) { // Blue to cyan
        greenChannel = static_cast<int>(255.0 * ((120.0 + signalStrength) / 15.0));
        return qRgba(0, greenChannel, 255, transparency_);
    }
    else if (signalStrength <= -90.0) { // Cyan to green
        blueChannel = static_cast<int>(255.0 * (1.0 - (105.0 + signalStrength) / 15.0));
        return qRgba(0, 255, blueChannel, transparency_);
    }
    else if (signalStrength <= -75.0) { // Green to yellow
        redChannel = static_cast<int>(255.0 * ((90.0 + signalStrength) / 15.0));
        return qRgba(redChannel, 255, 0, transparency_);
    }
    else if (signalStrength <= -60.0) { // Yellow to red
        greenChannel = static_cast<int>(255.0 * (1.0 - (75.0 + signalStrength) / 15.0));
        return qRgba(255, greenChannel, 0, transparency_);
    }
    else { // Red
        return qRgba(255, 0, 0, transparency_);
    }
}



// ----- [ PUBLIC METHODS ] --------------------------------------------------------------------------------------------

void Heatmap::setTransparency(int transparency)
{
    transparency_ = transparency;
}
void Heatmap::generate()
{
#pragma region TemporaryCode // To test the rendering of the heatmap
    QVector<QVector<double>> data = {
        // x, y, signal strength
        {10.0,  40.0,  -60.0},
        {60.0,  400.0, -90.0},
        {100.0, 80.0,  -120.0},
        {105.0, 90.0,  -95.0},
        {110.0, 105.0, -90.0},
        {120.0, 135.0, -100.0},
        {500.0, 300.0, -65.0},
        {10.0,  100.0, -85.0},
        {90.0,  30.0,  -80.0},
        {15.0,  150.0, -90.0},
        {30.0,  300.0, -80.0},
        {200.0, 200.0, -125.0},
        {220.0, 240.0, -110.0},
        {500.0, 20.0,  -70.0},
        {780.0, 40.0,  -90.0},
        {50.0,  590.0, -80.0},
        {150.0, 550.0, -80.0},
        {580.0, 40.0,  -90.0},
        {580.0, 200.0, -88.0},
        {750.0, 200.0, -70.0},
        {300.0, 200.0, -90.0},
        {150.0, 70.0,  -105.0},
        {560.0, 530.0, -80.0},
        {500.0, 510.0, -70.0},
        {500.0, 590.0, -80.0},
        {480.0, 560.0, -90.0},
        {10.0,  560.0, -70.0},
        {50.0,  550.0, -75.0},
    };
#pragma endregion TemporaryCode

    double distance, signalStrength, sumWeights, weight;
    for (int x = map_.size().width() - 1; x >= 0 ; --x) {
        for (int y = map_.size().height() - 1; y >= 0; --y) {
            signalStrength = 0.0;
            sumWeights = 0.0;

            for (auto& signalInformation : data) {
                distance = sqrt(pow(static_cast<double>(x) - signalInformation[0], 2) + pow(static_cast<double>(y) - signalInformation[1], 2));
                if (distance <= analysisRadius_) {
                    if (distance == 0.0) {
                        weight = 1.0;
                    } else {
                        weight = pow((analysisRadius_ - distance) / (analysisRadius_ * distance), smoothingDegree_);
                    }
                    signalStrength += signalInformation[2] * weight;
                    sumWeights += weight;
                }
            }

            if (sumWeights != 0.0) {
                map_.setPixel(x, y, signalStrengthToColor(signalStrength / sumWeights));
            }
            else {
                map_.setPixel(x, y, qRgba(255, 255, 255, 0));
            }
        }
    }
    QPixmap::operator=(QPixmap::fromImage(map_));
}
