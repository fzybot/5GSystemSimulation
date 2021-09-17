#pragma once
#include "src/protocols/bearers/Bearer.h"

class RadioBearer : public Bearer
{
public:
    enum class RadioBearerType
    {
      SRB0,
      SRB1,
      SRB2,
      DRB
    };

private:
    RadioBearer::RadioBearerType type_;

    int id_;
    double ambr;

    QoSProfile *QoS_;

public:
    RadioBearer();
    RadioBearer(int id);

    virtual void setId(int id) override;
    virtual int getId() override;

    virtual void setQoSProfile(QoSProfile *QoS) override;
    virtual QoSProfile *getQoSProfile() override;

    void createDefaultBearer(int id);
    void createRadioBearer(RadioBearerType type);
};
