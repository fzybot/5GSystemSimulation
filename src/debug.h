#pragma once
#include <QString>
#include <QDebug>

#include <stdarg.h>


static const bool DEBUGGING = true;

template <typename T>

static void debug(int n, ...)
{
    if (DEBUGGING == true) {
        va_list factor;
        va_start(factor, n);
        for (int i = 0; i < n; i++) {
            qDebug() << va_arg(factor, T);
        }
        va_end(factor);
    }
}
