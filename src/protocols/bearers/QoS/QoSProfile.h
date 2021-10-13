#pragma once
#include <QPair>

class QoSProfile
{
protected:
    int             id_;
    bool            gbrNgbr_;
    int             priority_;
    int             delayBudget_;
    float           packetErrorRate_;
    int             dataBurstVolume_;
    int             defaultAveragingWindow_;
    int             periodicity_;
    QPair<int, int> dataBurstVolumeRangeSize_;

    // Schedyuling weights

public:
    QoSProfile();

    void set5QIValue(int value);

    void config(
                int id,
                bool gbrNgbr,
                int priority,
                double delayBudget,
                float packetErrorRate,
                int dataBurstVolume,
                int defaultAveragingWindow
                );

    int getId();
    bool getGbrNbr();
    int getPriority();
    int getDelayBudget();
    float getPacketErrorRate();
    int getDataBurstVolume();
    int getDefaultAveragingWindow();

    void setDataBurstVolumeRange(int low, int high);
    QPair<int , int> &getDataBurstVolumeRange();

    void showProfile();
};
