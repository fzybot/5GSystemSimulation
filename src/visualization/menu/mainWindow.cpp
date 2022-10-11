#include "mainWindow.h"

#include <QtWidgets>
#include <QQuickWidget>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QObject>

#include <QPixmap>
#include <QImage>
#include <QRgb>
#include <QPainter>

#include "src/equipment/Walker.h"
#include "src/visualization/ChartGroupWidget.h"
#include "src/visualization/menu/SettingsDialog.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent)
{
    qDebug() << "MainWindow::MainWindow";
    tabMenu_= new TabMenu;
    tabMenu_->resize(700, 800);
    // fixed size for widget
    // tabMenu_->setFixedSize(500, 500);
    setCentralWidget(tabMenu_);
    qDebug() << "setCentralWidget(tabMenu_);";

    connect(this, &MainWindow::settingsChanged, tabMenu_, &TabMenu::changeSettings);

    createActions();
    createStatusBar();
    createDockWindows();
    readSettings();

    // QGraphicsView* view_ = new QGraphicsView(scene);
    // setCentralWidget(view_);


//    connect(textEdit->document(), &QTextDocument::contentsChanged,
//            this, &MainWindow::documentWasModified);

//#ifndef QT_NO_SESSIONMANAGER
//    QGuiApplication::setFallbackSessionManagementEnabled(false);
//    connect(qApp, &QGuiApplication::commitDataRequest,
//            this, &MainWindow::commitData);
//#endif

//    setCurrentFile(QString());
//    setUnifiedTitleAndToolBarOnMac(true);
}


void MainWindow::createDockWindows()
{
    QDockWidget *dock = new QDockWidget(tr("Simulation config"), this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    customerList_ = new QListWidget(dock);
    customerList_->addItems(QStringList()
            << "John Doe, Harmony Enterprises, 12 Lakeside, Ambleton"
            << "Jane Doe, Memorabilia, 23 Watersedge, Beaton"
            << "Tammy Shea, Tiblanka, 38 Sea Views, Carlton"
            << "Tim Sheen, Caraba Gifts, 48 Ocean Way, Deal"
            << "Sol Harvey, Chicos Coffee, 53 New Springs, Eccleston"
            << "Sally Hobart, Tiroli Tea, 67 Long River, Fedula");
    dock->setWidget(customerList_);
    addDockWidget(Qt::LeftDockWidgetArea, dock);
//    viewMenu_->addAction(dock->toggleViewAction());

    dock = new QDockWidget(tr("Debug && etc."), this);
    dock->setMaximumHeight(700);
    paragraphsList_ = new QListWidget(dock);
    paragraphsList_->addItems(QStringList()
            << ">>>>>>>>>" << "Lets start the debugging");
    dock->setWidget(paragraphsList_);
    addDockWidget(Qt::BottomDockWidgetArea, dock);

    dock = new QDockWidget(tr("Should be a PLOTS"), this);
    customerList_2_ = new QListWidget(dock);
    customerList_2_->addItems(QStringList()
            << "John Doe, Harmony Enterprises, 12 Lakeside, Ambleton");
    dock->setWidget(customerList_2_);

    // dock->setMaximumWidth(600);
    // dock->setMinimumWidth(500);
    // ChartsWidget *charts = new ChartsWidget(dock);
    // dock->setWidget(charts);
    
    addDockWidget(Qt::RightDockWidgetArea, dock);
//    viewMenu_->addAction(dock->toggleViewAction());

//    connect(customerList_, &QListWidget::currentTextChanged,
//            this, &MainWindow::insertCustomer);
//    connect(paragraphsList_, &QListWidget::currentTextChanged,
//            this, &MainWindow::addParagraph);
}

void MainWindow::closeEvent(QCloseEvent *event)
//! [3] //! [4]
{
    if (maybeSave()) {
        writeSettings();
        event->accept();
    } else {
        event->ignore();
    }
}
//! [4]


//! [5]
void MainWindow::newFile()
//! [5] //! [6]
{
    if (maybeSave()) {
        textEdit->clear();
        setCurrentFile(QString());
    }
}
//! [6]

//! [7]
void MainWindow::open()
//! [7] //! [8]
{
    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this);
        if (!fileName.isEmpty()) {
            loadFile(fileName);
        }
    }
}
//! [8]

//! [9]
bool MainWindow::save()
//! [9] //! [10]
{
    if (curFile_.isEmpty()) {
        return saveAs();
    }
    else {
        return saveFile(curFile_);
    }
}
//! [10]

//! [11]
bool MainWindow::saveAs()
//! [11] //! [12]
{
    QFileDialog dialog(this);
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setAcceptMode(QFileDialog::AcceptSave);

    if (dialog.exec() != QDialog::Accepted) {
        return false;
    }
    else {
        return saveFile(dialog.selectedFiles().first());
    }
}
//! [12]

//! [13]
void MainWindow::about()
//! [13] //! [14]
{
   QMessageBox::about(this, tr("About Application"),
            tr("The <b>Application</b> example demonstrates how to "
               "write modern GUI applications using Qt, with a menu bar, "
               "toolbars, and a status bar."));
}

void MainWindow::settings()
{
    //SettingsDialog tabdialog(this);
    const QRect screenGeometry = QApplication::desktop()->screenGeometry();
    settingsDialog_ = new SettingsDialog(this);
    settingsDialog_->setWindowTitle(tr("Settings"));
    settingsDialog_->setAttribute(Qt::WA_DeleteOnClose);
    settingsDialog_->resize(screenGeometry.width() / 4, screenGeometry.height() / 4);
    settingsDialog_->show();
}

void MainWindow::settingsLinkBudget()
{

}

void MainWindow::documentWasModified()
//! [15] //! [16]
{
    setWindowModified(textEdit->document()->isModified());
}

void MainWindow::changeSettings(void* settings)
{
    emit settingsChanged(settings);
}
//! [16]

//! [17]
void MainWindow::createActions()
//! [17] //! [18]
{

    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    QToolBar *fileToolBar = addToolBar(tr("File"));
    const QIcon newIcon = QIcon::fromTheme("document-new", QIcon(":/images/menu/new.png"));
    QAction *newAct = new QAction(newIcon, tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, &QAction::triggered, this, &MainWindow::newFile);
    fileMenu->addAction(newAct);
    fileToolBar->addAction(newAct);

//! [19]
    const QIcon openIcon = QIcon::fromTheme("document-open", QIcon(":/images/menu/open.png"));
    QAction *openAct = new QAction(openIcon, tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, &QAction::triggered, this, &MainWindow::open);
    fileMenu->addAction(openAct);
    fileToolBar->addAction(openAct);
//! [18] //! [19]

    const QIcon saveIcon = QIcon::fromTheme("document-save", QIcon(":/images/menu/save.png"));
    QAction *saveAct = new QAction(saveIcon, tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, &QAction::triggered, this, &MainWindow::save);
    fileMenu->addAction(saveAct);
    fileToolBar->addAction(saveAct);

    const QIcon saveAsIcon = QIcon::fromTheme("document-save-as");
    QAction *saveAsAct = fileMenu->addAction(saveAsIcon, tr("Save &As..."), this, &MainWindow::saveAs);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(tr("Save the document under a new name"));

//! [20]

    fileMenu->addSeparator();

    const QIcon exitIcon = QIcon::fromTheme("application-exit");
    QAction *exitAct = fileMenu->addAction(exitIcon, tr("E&xit"), this, &QWidget::close);
    exitAct->setShortcuts(QKeySequence::Quit);
//! [20]
    exitAct->setStatusTip(tr("Exit the application"));

//! [21]
    QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));
    QToolBar *editToolBar = addToolBar(tr("Edit"));
//!
#ifndef QT_NO_CLIPBOARD
    const QIcon cutIcon = QIcon::fromTheme("edit-cut", QIcon(":/images/menu/cut.png"));
    QAction *cutAct = new QAction(cutIcon, tr("Cu&t"), this);
//! [21]
    cutAct->setShortcuts(QKeySequence::Cut);
    cutAct->setStatusTip(tr("Cut the current selection's contents to the "
                            "clipboard"));
    //connect(cutAct, &QAction::triggered, textEdit, &QPlainTextEdit::cut); //!!!!
    editMenu->addAction(cutAct);
    editToolBar->addAction(cutAct);

    const QIcon copyIcon = QIcon::fromTheme("edit-copy", QIcon(":/images/menu/copy.png"));
    QAction *copyAct = new QAction(copyIcon, tr("&Copy"), this);
    copyAct->setShortcuts(QKeySequence::Copy);
    copyAct->setStatusTip(tr("Copy the current selection's contents to the "
                             "clipboard"));
    //connect(copyAct, &QAction::triggered, textEdit, &QPlainTextEdit::copy); //!!!!!
    editMenu->addAction(copyAct);
    editToolBar->addAction(copyAct);

    const QIcon pasteIcon = QIcon::fromTheme("edit-paste", QIcon(":/images/menu/paste.png"));
    QAction *pasteAct = new QAction(pasteIcon, tr("&Paste"), this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
                              "selection"));
    //connect(pasteAct, &QAction::triggered, textEdit, &QPlainTextEdit::paste); //!!!!!
    editMenu->addAction(pasteAct);
    editToolBar->addAction(pasteAct);

    menuBar()->addSeparator();

#endif // !QT_NO_CLIPBOARD

// Settings
    QMenu *settingsMenu = menuBar()->addMenu(tr("&Settings"));
    QAction *settingsAct = settingsMenu->addAction(tr("&Config. simulation"), this, &MainWindow::settings);
    settingsAct->setStatusTip(tr("Show the application's About box"));

    // Settings link budget
    // QAction *settingsLinkBudgetAct = settingsMenu->addAction(tr("&Config. link budget"), this, &MainWindow::settingsLinkBudget);
    // settingsLinkBudgetAct->setStatusTip(tr("Show the application's About box"));

// Help
    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    QAction *aboutAct = helpMenu->addAction(tr("&About"), this, &MainWindow::about);
    aboutAct->setStatusTip(tr("Show the application's About box"));

    QAction *aboutQtAct = helpMenu->addAction(tr("About &Qt"), qApp, &QApplication::aboutQt);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
//! [22]

//! [23]
#ifndef QT_NO_CLIPBOARD
    cutAct->setEnabled(false);
//! [23] //! [24]
    copyAct->setEnabled(false);
    //connect(textEdit, &QPlainTextEdit::copyAvailable, cutAct, &QAction::setEnabled);      //!!!
    //connect(textEdit, &QPlainTextEdit::copyAvailable, copyAct, &QAction::setEnabled);     //!!!
#endif // !QT_NO_CLIPBOARD
}
//! [24]

//! [32]
void MainWindow::createStatusBar()
//! [32] //! [33]
{
    statusBar()->showMessage(tr("Ready"));
}
//! [33]

//! [34] //! [35]
void MainWindow::readSettings()
//! [34] //! [36]
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    const QByteArray geometry = settings.value("geometry", QByteArray()).toByteArray();
    if (geometry.isEmpty()) {
        const QRect availableGeometry = QApplication::desktop()->availableGeometry();
        resize(availableGeometry.width() / 2, availableGeometry.height() / 2);
        move((availableGeometry.width() - width()) / 2,
             (availableGeometry.height() - height()) / 2);
    } else {
        restoreGeometry(geometry);
    }
}
//! [35] //! [36]

//! [37] //! [38]
void MainWindow::writeSettings()
//! [37] //! [39]
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    settings.setValue("geometry", saveGeometry());
}
//! [38] //! [39]

//! [40]
bool MainWindow::maybeSave()
//! [40] //! [41]
{
    if (!textEdit->document()->isModified())
        return true;
    const QMessageBox::StandardButton ret
        = QMessageBox::warning(this, tr("Application"),
                               tr("The document has been modified.\n"
                                  "Do you want to save your changes?"),
                               QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    switch (ret) {
    case QMessageBox::Save:
        return save();
    case QMessageBox::Cancel:
        return false;
    default:
        break;
    }
    return true;
}
//! [41]

//! [42]
void MainWindow::loadFile(const QString &fileName)
//! [42] //! [43]
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return;
    }

    QTextStream in(&file);
#ifndef QT_NO_CURSOR
    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    textEdit->setPlainText(in.readAll());
#ifndef QT_NO_CURSOR
    QGuiApplication::restoreOverrideCursor();
#endif

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
}
//! [43]

//! [44]
bool MainWindow::saveFile(const QString &fileName)
//! [44] //! [45]
{
    QString errorMessage;

    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
    QSaveFile file(fileName);
    if (file.open(QFile::WriteOnly | QFile::Text)) {
        QTextStream out(&file);
        out << textEdit->toPlainText();
        if (!file.commit()) {
            errorMessage = tr("Cannot write file %1:\n%2.")
                           .arg(QDir::toNativeSeparators(fileName), file.errorString());
        }
    } else {
        errorMessage = tr("Cannot open file %1 for writing:\n%2.")
                       .arg(QDir::toNativeSeparators(fileName), file.errorString());
    }
    QGuiApplication::restoreOverrideCursor();

    if (!errorMessage.isEmpty()) {
        QMessageBox::warning(this, tr("Application"), errorMessage);
        return false;
    }

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}
//! [45]

//! [46]
void MainWindow::setCurrentFile(const QString &fileName)
//! [46] //! [47]
{
    curFile_ = fileName;
    textEdit->document()->setModified(false);
    setWindowModified(false);

    QString shownName = curFile_;
    if (curFile_.isEmpty())
        shownName = "untitled.txt";
    setWindowFilePath(shownName);
}
//! [47]

//! [48]
QString MainWindow::strippedName(const QString &fullFileName)
//! [48] //! [49]
{
    return QFileInfo(fullFileName).fileName();
}
//! [49]
#ifndef QT_NO_SESSIONMANAGER
void MainWindow::commitData(QSessionManager &manager)
{
    if (manager.allowsInteraction()) {
        if (!maybeSave())
            manager.cancel();
    } else {
        // Non-interactive: save without asking
        if (textEdit->document()->isModified())
            save();
    }
}
#endif
