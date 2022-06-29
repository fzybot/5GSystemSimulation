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

#include "src/visualization/menu/mainWindow.h"
#include "src/scenarios/tests.h"
#include "src/scenarios/simple.h"
#include "src/scenarios/modulationPerformance.h"
#include "src/tests/packet_test.h"
#include "src/tests/propagation_models_test.h"
#include "src/tests/python_test.h"

#include "src/debug.h"



 
// Умный указатель на файл логирования
QScopedPointer<QFile>   _logFile;
 
// Объявляение обработчика
void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    //##############################################################################
    //                                      Logging
    //##############################################################################

    // Устанавливаем файл логирования
    _logFile.reset(new QFile("/home/ruslan/dev/git/5GSystemSimulation/src/logging/log.txt"));
    // Открываем файл логирования c перезаписью файла 'QFile::ReadWrite'
    // Если нужно добавить в конец файла, меняем 'QFile::ReadWrite' на 'QFile::Append'
    _logFile.data()->open(QFile::WriteOnly | QFile::Text);
    qInstallMessageHandler(messageHandler);

    //##############################################################################

    

    MainWindow mainWin;

    mainWin.resize(1400, 1200);
    //mainWin.show();


    Simple();
    vectorTest();
    propagation_model_test_plot();
    python_test();
    python_test_function_file();

    //##############################################################################
    //                   Testing features (in src/scenarios/tests.h)
    //##############################################################################

    // simpleTest();
    // runModulationPerformance();

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
        << msg << endl;
    out.flush();    // Очищаем буферизированные данные
}
