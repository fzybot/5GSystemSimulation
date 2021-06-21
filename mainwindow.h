#pragma once


#include <QMainWindow>
#include <QQmlApplicationEngine>
#include <QQuickWidget>
#include <QtWidgets>


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

public:
    MainWindow(QWidget *parent = nullptr);

    void loadFile(const QString &fileName);
protected:
    void closeEvent(QCloseEvent *event) override;

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
    void createActions();
    void createStatusBar();
    void createDockWindows();
    void readSettings();
    void writeSettings();
    bool maybeSave();
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);

    //tests
    QQuickWidget *my_quickWidget;
    //tests

    QPlainTextEdit *textEdit;
    QString curFile;

    QListWidget *customerList;
    QListWidget *paragraphsList;

    QMenu *viewMenu;
    QGraphicsView *view;
};
//! [0]
