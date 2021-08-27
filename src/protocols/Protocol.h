#pragma once

class Equipment;

class Protocol
{
public:
    Equipment *device_;
public:
    Protocol();

    void setDevice(Equipment *e);
    Equipment *getDevice();
};

