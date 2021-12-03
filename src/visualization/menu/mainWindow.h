#pragma once


#include <QMainWindow>
#include <QQmlApplicationEngine>
#include <QQuickWidget>
#include <QtWidgets>

#include "src/visualization/Map.h"
#include "src/visualization/menu/TabMenu.h"
#include "src/visualization/menu/SettingsDialog.h"


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
private:
    QQuickWidget* quickWidget_;

    QPlainTextEdit* textEdit;
    QString curFile_;

    QListWidget* customerList_;
    QListWidget* customerList_2_;
    QListWidget* paragraphsList_;

    QMenu* viewMenu_;
    QGraphicsView* view_;

    TabMenu* tabMenu_;

    SettingsDialog *settingsDialog_;

private slots:
    void newFile();
    void open();
    bool save();
    bool saveAs();
    void about();
    void settings();
    void settingsLinkBudget();
    void documentWasModified();

public slots:
    void changeSettings(int*);

signals:
    void settingsChanged(int*);

public:
    MainWindow(QWidget* parent = nullptr);

    void loadFile(const QString& fileName);
    int simulationSettings[19];
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
    void setCurrentFile(const QString& fileName);

    bool saveFile(const QString &fileName);

    QString strippedName(const QString &fullFileName);

protected:
    void closeEvent(QCloseEvent* event) override;

};
//! [0]
