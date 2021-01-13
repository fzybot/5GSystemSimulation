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



#include <src/equipment/equipment.h>
#include <src/equipment/base_station.h>
#include <src/equipment/user_equipment.h>
#include <src/channel/propagation_models.h>
#include<src/scheduler/simulation.h>


#include <armadillo>
int main(int argc, char *argv[])
{

//    QApplication app(argc, argv);
//    MainWindow w;
//    //w.show();
//    BaseStation bs1;
//    bs1.setLatitude(55.01);
//    for(int i = 1; i < 1000; i++){
//        //qDebug() << UMa_NLOS(i, 0, 50, 1, 2600, 50, 20, 6);
//    }
//    QQmlApplicationEngine engine;
//    engine.load(QUrl(QStringLiteral("qrc:///qml/map.qml"))); //"src/qml/map.qml"
//    return app.exec();

    Q_INIT_RESOURCE(application);
#ifdef Q_OS_ANDROID
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName("QtProject");
    QCoreApplication::setApplicationName("Application Example");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);
    QCommandLineParser parser;
    parser.setApplicationDescription(QCoreApplication::applicationName());
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("file", "The file to open.");
    parser.process(app);

    MainWindow mainWin;
    if (!parser.positionalArguments().isEmpty())
        mainWin.loadFile(parser.positionalArguments().first());
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:///qml/map.qml"))); //"src/qml/map.qml"

    mainWin.show();


    BaseStation bs1;
    qDebug() << bs1.PCI << bs1.bandwidth << "Number of BS: " << bs1.dataSize;
//    bs1.printData();
    Simulation sim1;
    qDebug() <<"Number of UEs:" << sim1.userEqipmnets.length();
    for (int i = 0; i < sim1.baseStations.length(); i ++){
        qDebug() << sim1.baseStations[i].data[0];
    }
    return app.exec();

}
