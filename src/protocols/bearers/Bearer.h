#pragma once

class QoSProfile;

class Bearer
{
protected:
    int id_;
    double ambr;

    QoSProfile *QoS_;

public:
    Bearer();
    Bearer(int id);

    void setId(int id);
    int getId();

    void setQoSProfile(QoSProfile *QoS);
    QoSProfile *getQoSProfile();
};
