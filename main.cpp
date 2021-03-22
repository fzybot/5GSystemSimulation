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



#include <src/equipment/equipment.h>
#include <src/equipment/base_station.h>
#include <src/equipment/user_equipment.h>
#include <src/equipment/walker.h>
#include <src/channel/propagation_models.h>
#include <src/scheduler/simulation.h>


int main(int argc, char *argv[])
{

//    Q_INIT_RESOURCE(application);
//#ifdef Q_OS_ANDROID
//    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
//#endif

    QApplication app(argc, argv);
//    QCoreApplication::setOrganizationName("QtProject");
//    QCoreApplication::setApplicationName("Application Example");
//    QCoreApplication::setApplicationVersion(QT_VERSION_STR);
//    QCommandLineParser parser;
//    parser.setApplicationDescription(QCoreApplication::applicationName());
//    parser.addHelpOption();
//    parser.addVersionOption();
//    parser.addPositionalArgument("file", "The file to open.");
//    parser.process(app);

    MainWindow mainWin;
//    if (!parser.positionalArguments().isEmpty())
//        mainWin.loadFile(parser.positionalArguments().first());
    //QQmlApplicationEngine engine;
    //engine.load(QUrl(QStringLiteral("qrc:///qml/map.qml"))); //"src/qml/map.qml"

    mainWin.show();

//###########################################################################################
//                                       Testing
//###########################################################################################
    BaseStation bs1;
    qDebug() << bs1.PCI << bs1.bandwidth << "Number of BS: " << bs1.dataSize;
//  bs1.printData();
    Simulation sim1;
    QGraphicsScene scene;
    scene.setSceneRect(-500, -500, 1500, 1500);
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);
    int walkerCount = 40;
    for (int i = 0; i < walkerCount; ++i) {
        walker *ue = new walker;
        ue->setPos(::sin((i * 6.28) / walkerCount) * 500,
                      ::cos((i * 6.28) / walkerCount) * 500);
        scene.addItem(ue);
    }
    QGraphicsView view(&scene);
    view.setScene(&scene);
    view.setRenderHint(QPainter::Antialiasing);

    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view.setDragMode(QGraphicsView::ScrollHandDrag);


    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Random UEs"));
    view.resize(700, 500);
    view.show();

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, &scene, &QGraphicsScene::advance);
    timer.start(1000 / 33);


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
    return app.exec();

}
