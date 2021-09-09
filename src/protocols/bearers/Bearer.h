#pragma once


class Bearer
{
protected:
    int id_;
    int qci_;
    double ambr;

public:
    Bearer();
    Bearer(int id);

    void setId(int id);
    int getId();

    int getQci();
};
