#pragma once
#include <QString>
#include <QDebug>

#include <stdarg.h>
#include <iostream>


static const bool DEBUGGING = true;

template <typename T>
void debug(T a)
{
    qDebug() << a;
}

template <typename T, typename... Ts>
void debug(T a, Ts... args)
{
    if (DEBUGGING == true) {
        debug(a);
        debug(args...);
    }
}
