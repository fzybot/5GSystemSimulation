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
    Bearer::BearerType type_;
    int qci_;

public:
    Bearer();

    void createDefaultBearer();
};
