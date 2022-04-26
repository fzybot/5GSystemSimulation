#pragma once

#include <QVector>

#include <armadillo>

class Manipulator
{
private:
    int MO_;
    QVector<bool> bitBurst_;
    QVector<arma::cx_double> arrayIO_;

public:
    Manipulator(int MO, QVector<bool> bitBurst);
};

