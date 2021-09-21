#pragma once

class QoSProfile;

class Bearer
{
public:

    void setId(int id) {}
    int getId() {}

    void setQoSProfile(QoSProfile *QoS) {}
    QoSProfile *getQoSProfile() {}
};
