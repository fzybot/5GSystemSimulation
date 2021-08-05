#pragma once
#include <QString>
#include <QDebug>

#include <stdarg.h>


static const bool DEBUGGING = true;

template <typename T>
void debug(T a)
{
    qDebug() << a << endl;
}

template <typename T, typename... Ts>
void debug(T a, Ts... args)
{
    if (DEBUGGING == true) {
        debug(a);
        debug(args...);
    }
}
