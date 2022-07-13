

#include "fft.h"

#include <QVector>
#include <complex>

QVector<std::complex<double>> ifft(QVector<std::complex<double>> vector)
{
    int N = vector.length();
    QVector<std::complex<double>> afterIFFT;
    for (int i = 0; i < N; i++)
    {
        double localSummReal = 0.0;
        double localSummImag = 0.0;
        double arg = 0.0;
        for (int j = 0; j < N; j++)
        {
            arg = (2 * 3.14 * j * i) / N;
            localSummReal += (vector[j].real() * cos(arg)) - (vector[j].imag() * sin(arg));
            localSummImag += (vector[j].real() * sin(arg)) + (cos(arg) * vector[j].imag());
        }
        std::complex<double> value(localSummReal / N, localSummImag / N);
        afterIFFT.push_back(value);
    }

    return afterIFFT;
}

QVector<std::complex<double>> fft(QVector<std::complex<double>> vector)
{
    int N = vector.length();
    QVector<std::complex<double>> afterFFT;
    for (int i = 0; i < N; i++)
    {
        double localSummReal = 0.0;
        double localSummImag = 0.0;
        double arg = 0;
        for (int j = 0; j < N; j++)
        {
            arg = (2 * 3.14 * j * i) / N ;
            localSummReal += (vector[j].real() * cos(arg)) - (vector[j].imag() * (-1) * sin(arg));
            localSummImag += (vector[j].real() * (-1) * sin(arg)) + (cos(arg) * vector[j].imag());
        }
        std::complex<double> value(localSummReal, localSummImag);
        afterFFT.push_back(value);
    }

    return afterFFT;   
}