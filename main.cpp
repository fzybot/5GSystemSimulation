#include "mainwindow.h"

#include <QApplication>
#include <QDebug>

#include <src/equipment/Equipment.h>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Equipment bs1;
    bs1.setLatitude(55.01);
    qDebug() << bs1.SCS;


    return a.exec();

}
