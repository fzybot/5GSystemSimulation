#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QObject>
#include <QTime>
#include <QBasicTimer>
#include <QEasingCurve>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QtMath>
#include <QtWidgets>
#include <QQuickView>



#include <src/equipment/equipment.h>
#include <src/equipment/gNodeB.h>
#include <src/equipment/user_equipment.h>
#include <src/equipment/walker.h>
#include <src/phy/propagation_models.h>
#include <src/simulation/simulation.h>

#include <armadillo>


int main(int argc, char *argv[])
{

//    Q_INIT_RESOURCE(application);
//#ifdef Q_OS_ANDROID
//    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
//#endif

    QApplication app(argc, argv);

    MainWindow mainWin;
    mainWin.show();

//###########################################################################################
//                                       Testing
//###########################################################################################
    gNodeB bs1;
    qDebug() << bs1.PCI << bs1.bandwidth << "Number of BS: " << bs1.dataSize;
//  bs1.printData();
    Simulation sim1;
    qDebug() <<"Path Loss:" << sim1.calculatePathLoss(100, 0);
    qDebug() <<"SINR:" << sim1.userEqipmnets[0].SINR;
//    for (int i = 0; i < sim1.userEqipmnets.length(); i ++){
//        qDebug() <<"SINR:" << sim1.userEqipmnets[i].SINR;
//        qDebug() << "Step size:" << sim1.userEqipmnets[i].speed;
//        qDebug() << "Step size:" << sim1.userEqipmnets[i].stepSize;
//        qDebug() << "Longtitude: " << sim1.userEqipmnets[i].longtitude;
//        qDebug() << "Latitude: "<< sim1.userEqipmnets[i].latitude;
//        qDebug() <<"---------------------------------";
//    }
    sim1.showBordersll();
//###########################################################################################
    return app.exec();

}
