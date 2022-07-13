#pragma once

#include <QVector>
#include <complex>

#define BPSK_LEVEL M_SQRT1_2

#define QPSK_LEVEL M_SQRT1_2

#define QAM16_LEVEL_1 (1.0f / sqrtf(10.0f))
#define QAM16_LEVEL_2 (3.0f / sqrtf(10.0f))

#define QAM64_LEVEL_1 (1.0f / sqrtf(42.0f))
#define QAM64_LEVEL_2 (3.0f / sqrtf(42.0f))
#define QAM64_LEVEL_3 (5.0f / sqrtf(42.0f))
#define QAM64_LEVEL_4 (7.0f / sqrtf(42.0f))

#define QAM16_THRESHOLD (2 / sqrtf(10))
#define QAM64_THRESHOLD_1 (2 / sqrtf(42))
#define QAM64_THRESHOLD_2 (4 / sqrtf(42))
#define QAM64_THRESHOLD_3 (6 / sqrtf(42))
#define QAM256_THRESHOLD_1 (2 / sqrtf(170))
#define QAM256_THRESHOLD_2 (4 / sqrtf(170))
#define QAM256_THRESHOLD_3 (6 / sqrtf(170))
#define QAM256_THRESHOLD_4 (8 / sqrtf(170))
#define QAM256_THRESHOLD_5 (10 / sqrtf(170))
#define QAM256_THRESHOLD_6 (12 / sqrtf(170))
#define QAM256_THRESHOLD_7 (14 / sqrtf(170))

QVector<std::complex<double>> QPSK(QVector<bool> &dataArray);
QVector<std::complex<double>> QAM16(QVector<bool> &dataArray);
QVector<std::complex<double>> QAM64(QVector<bool> &dataArray);
QVector<std::complex<double>> QAM256(QVector<bool> &dataArray);

QVector<bool> demQPSK(QVector<std::complex<double>> &IQvalues);
QVector<bool> demQAM16(QVector<std::complex<double>> &IQvalues);
QVector<bool> demQAM64(QVector<std::complex<double>> &IQvalues);
QVector<bool> demQAM256(QVector<std::complex<double>> &IQvalues);
