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

#include "src/visualization/menu/mainWindow.h"
#include "src/scenarios/tests.h"
#include "src/scenarios/simple.h"

#include "src/debug.h"

int main(int argc, char *argv[])
{

//    Q_INIT_RESOURCE(application);
//#ifdef Q_OS_ANDROID
//    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
//#endif

    QApplication app(argc, argv);

    MainWindow mainWin;
    mainWin.resize(1900, 1200);
    mainWin.show();

    // Simple();

    //##############################################################################
    //                   Testing features (in src/scenarios/tests.h)
    //##############################################################################

    simpleTest();

//##############################################################################
    return app.exec();

}
