#pragma once
#include <QString>
#include <QDebug>

#include <stdarg.h>
#include <iostream>


static const bool DEBUGGING = true;

template <typename T>
void debug1(int v, T a)
{
    if (DEBUGGING == true) {
        if (v == 1) {
            qDebug() << a;
        } else if (v == 2) {
            qDebug() <<"    "<< a;
        } else if (v == 3) {
            qDebug() <<"        "<< a;
        } else if (v == 4) {
            qDebug() <<"            "<< a;
        } else if (v == 5) {
            qDebug() <<"                "<< a;
        }
    }
}

template <typename T, typename... Ts>
void debug1(int v, T a, Ts... args)
{
    if (DEBUGGING == true) {
        debug1(v, a);
        debug1(v, args...);
    }
}

template <typename T>
void debug(T a)
{
    if (DEBUGGING == true) {
        qDebug() << a;
    }
}

template <typename T, typename... Ts>
void debug(T a, Ts... args)
{
    if (DEBUGGING == true) {
        debug(a);
        debug(args...);
    }
}
