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



#include <src/equipment/equipment.h>
#include <src/equipment/base_station.h>
#include <src/equipment/user_equipment.h>
#include <src/channel/propagation_models.h>

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);
    MainWindow w;
    //w.show();


    BaseStation bs1;
    bs1.setLatitude(55.01);

    for(int i = 1; i < 1000; i++){
        //qDebug() << UMa_NLOS(i, 0, 50, 1, 2600, 50, 20, 6);
    }

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:///qml/map.qml"))); //"src/qml/map.qml"


    return app.exec();

}
