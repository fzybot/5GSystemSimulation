#pragma once


#include <QMainWindow>
#include <QQmlApplicationEngine>
#include <QQuickWidget>
#include <QtWidgets>

#include "src/visualization/Map.h"


QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QPlainTextEdit;
class QSessionManager;
class QListWidget;
QT_END_NAMESPACE


//! [0]
class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    void newFile();
    void open();
    bool save();
    bool saveAs();
    void about();
    void documentWasModified();

//    void insertCustomer(const QString &customer);
//    void addParagraph(const QString &paragraph);
//    void runSimulation();
#ifndef QT_NO_SESSIONMANAGER
    void commitData(QSessionManager &);
#endif

private:
    QQuickWidget* my_quickWidget;

    QPlainTextEdit* textEdit;
    QString curFile;

    QListWidget* customerList;
    QListWidget* paragraphsList;

    QMenu* viewMenu;
    QGraphicsView* view;

    Map* map_;


    void createActions();
    void createStatusBar();
    void createDockWindows();
    void readSettings();
    void writeSettings();
    bool maybeSave();
    void setCurrentFile(const QString& fileName);

    bool saveFile(const QString &fileName);

    QString strippedName(const QString &fullFileName);

protected:
    void closeEvent(QCloseEvent* event) override;
    void resizeEvent(QResizeEvent *event) override;

public:
    MainWindow(QWidget* parent = nullptr);

    void loadFile(const QString& fileName);
};
//! [0]
