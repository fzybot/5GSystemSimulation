#pragma once


class QoSProfile
{
private:
    int qci_;
    double maxDelay_;
    int priority_;
    bool arpPreEmptionCapability_;
    bool arpPreEmptionVulnerability_;
    double gbr_;
    double mbr_;

public:
    QoSProfile();


};

