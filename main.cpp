#include "mainWindow.h"

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

#include <armadillo>

#include <src/scenarios/tests.h>

int main(int argc, char *argv[])
{

//    Q_INIT_RESOURCE(application);
//#ifdef Q_OS_ANDROID
//    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
//#endif

    QApplication app(argc, argv);

    MainWindow mainWin;
    mainWin.show();

//##############################################################################
//                   Testing features (in src/scenarios/tests.h)
//##############################################################################

    //simpleTest();

//##############################################################################
    return app.exec();

}
