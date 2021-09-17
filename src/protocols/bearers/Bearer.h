#pragma once

class QoSProfile;

class Bearer
{
public:
    virtual void setId(int id) {}
    virtual int getId() {}

    virtual void setQoSProfile(QoSProfile *QoS) {}
    virtual QoSProfile *getQoSProfile() {}
};
