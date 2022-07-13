#pragma once

#include <QVector>
#include <QtMath>
#include <complex>


QVector<std::complex<double>> ifft(QVector<std::complex<double>> vector);
QVector<std::complex<double>> fft(QVector<std::complex<double>> vector);
QVector<std::complex<double>> ifft_carrier(QVector<std::complex<double>> vector, int numerology, double speed);
