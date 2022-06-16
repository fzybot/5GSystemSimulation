#pragma once

#define BPSK_LEVEL M_SQRT1_2

#define QPSK_LEVEL M_SQRT1_2

#define QAM16_LEVEL_1 (1.0f / sqrtf(10.0f))
#define QAM16_LEVEL_2 (3.0f / sqrtf(10.0f))

#define QAM64_LEVEL_1 (1.0f / sqrtf(42.0f))
#define QAM64_LEVEL_2 (3.0f / sqrtf(42.0f))
#define QAM64_LEVEL_3 (5.0f / sqrtf(42.0f))
#define QAM64_LEVEL_4 (7.0f / sqrtf(42.0f))

/* HARD DEMODULATION Thresholds, necessary for obtaining the zone of received symbol for optimized LLR approx
 * implementation */
#define QAM16_THRESHOLD (2.0f / sqrtf(10.0f))
#define QAM64_THRESHOLD_1 (2.0f / sqrtf(42.0f))
#define QAM64_THRESHOLD_2 (4.0f / sqrtf(42.0f))
#define QAM64_THRESHOLD_3 (6.0f / sqrtf(42.0f))
