#pragma once


class Bearer
{
public:
    enum class BearerType
    {
      SRB0,
      SRB1,
      SRB2,
      DRB
    };
protected:
    int id_;
    Bearer::BearerType type_;
    int qci_;
    double ambr;

public:
    Bearer(int id);

    void createDefaultBearer(int id);
    void createBearer(BearerType type, int qci);

    int getQci();
};
