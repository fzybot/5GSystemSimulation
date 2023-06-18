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
#include <QLoggingCategory>
#include <QFile>
#include <QDir>
#include <QScopedPointer>
#include <QTextStream>
#include <QDateTime>
#include <QGraphicsScene>

#include <QGeoCoordinate>

#include <QPainter>
#include <QRandomGenerator>
#include <QStyleOption>
#include <QtMath>

#include "src/visualization/menu/mainWindow.h"
#include "src/scenarios/tests.h"
#include "src/scenarios/simple.h"
#include "src/scenarios/modulationPerformance.h"
#include "src/tests/packet_test.h"
#include "src/tests/propagation_models_test.h"
#include "src/tests/tests.h"
#include "src/tests/test_antenna_array.h"

#include "src/debug.h"



 
// Умный указатель на файл логирования
QScopedPointer<QFile>   _logFile;
 
// Объявляение обработчика
void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

constexpr qreal Pi = M_PI;
constexpr qreal TwoPi = 2 * M_PI;

static qreal normalizeAngle(qreal angle)
{
    while (angle < 0)
        angle += TwoPi;
    while (angle > TwoPi)
        angle -= TwoPi;
    return angle;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    //##############################################################################
    //                                      Logging
    //##############################################################################

    // Устанавливаем файл логирования
    QString pwdLog = QString{PRO_FILE_PWD} + QString{"/src/logging/log.txt"};
    _logFile.reset(new QFile(pwdLog));
    // Открываем файл логирования c перезаписью файла 'QFile::ReadWrite'
    // Если нужно добавить в конец файла, меняем 'QFile::ReadWrite' на 'QFile::Append'
    _logFile.data()->open(QFile::WriteOnly | QFile::Text);
    qInstallMessageHandler(messageHandler);

    //##############################################################################

    

//    MainWindow mainWin;

//    mainWin.resize(1400, 1200);
//    mainWin.show();



    Simple();
    // propagation_model_test_plot();
    test_passing();
    QLineF lineToCenter(QPointF(100, 100), QPointF(150, 125));
    qreal angleToCenter = std::atan2(lineToCenter.dy(), lineToCenter.dx());
    qDebug() << "angleToCenter = " << angleToCenter ;
    angleToCenter = normalizeAngle((3.14 - angleToCenter) + 3.14 / 2);
    qDebug() << "angleToCenter = " << angleToCenter ;

    QGeoCoordinate point_1(55.013541, 82.951781, 10),
            point_2(55.013602, 82.954783, 10),
            point_3(55.014640, 82.954044),
            point_4(55.015385, 82.951817),
            point_5(55.014743, 82.948875),
            point_6(55.013855, 82.948339),
            point_7(55.011567, 82.951555);
    qDebug() << "azimuth to: " << point_1.azimuthTo(point_2);
    qDebug() << "azimuth to: " << point_1.azimuthTo(point_3);
    qDebug() << "azimuth to: " << point_1.azimuthTo(point_4);
    qDebug() << "azimuth to: " << point_1.azimuthTo(point_5);
    qDebug() << "azimuth to: " << point_1.azimuthTo(point_6);
    qDebug() << "azimuth to: " << point_1.azimuthTo(point_7);
    qDebug() << "atDistanceAndAzimuth: " << point_1.atDistanceAndAzimuth(10, 90).latitude() << ", " << point_1.atDistanceAndAzimuth(10, 90).longitude();




    //##############################################################################
    //                   Testing features (in src/scenarios/tests.h)
    //##############################################################################

    // simpleTest();
    // runModulationPerformance();
    //antennaArray();

    //##############################################################################
    return app.exec();

}

// Реализация обработчика
void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    // Открываем поток записи в файл
    QTextStream out(_logFile.data());
    // Записываем дату записи
    out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ");
    // По типу определяем, к какому уровню относится сообщение
    switch (type)
    {
    case QtInfoMsg:     out << "INF "; break;
    case QtDebugMsg:    out << "DBG "; break;
    case QtWarningMsg:  out << "WRN "; break;
    case QtCriticalMsg: out << "CRT "; break;
    case QtFatalMsg:    out << "FTL "; break;
    }
    // Записываем в вывод категорию сообщения и само сообщения
    out << " " << context.function <<  ": "
        << msg << Qt::endl;
    out.flush();    // Очищаем буферизированные данные
}
