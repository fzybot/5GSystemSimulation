#include "mainwindow.h"

#include <QApplication>
#include <QDebug>

#include <src/equipment/Equipment.h>
#include <src/equipment/BaseStation.h>
#include <src/equipment/UserEquipment.h>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    BaseStation bs1;
    bs1.setLatitude(55.01);
    qDebug() << bs1.SCS;


    return a.exec();

}
