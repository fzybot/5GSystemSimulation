#pragma once
#include <QVector>

class TransportBlock
{

private:
    int size_;
    QVector<bool> tbsData_;

    bool HARQ = false;

public:
    TransportBlock();

    
};

