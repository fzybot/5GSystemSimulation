#pragma once

#include <QApplication>
#include <QDialog>
#include <QDialogButtonBox>
#include <QEventLoop>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QListView>
#include <QPointer>
#include <QPushButton>
#include <QResizeEvent>
#include <QScrollArea>
#include <QScrollBar>
#include <QSet>
#include <QSettings>
#include <QSortFilterProxyModel>
#include <QSpacerItem>
#include <QStackedLayout>
#include <QStyle>
#include <QStyledItemDelegate>

const int kInitialWidth = 750;
const int kInitialHeight = 450;
const int kMaxMinimumWidth = 250;
const int kMaxMinimumHeight = 250;

class SettingsDialog : public QDialog
{
    Q_OBJECT
// private:
//     const QList<IOptionsPage *> m_pages;

//     QSet<IOptionsPage *> m_visitedPages;
//     CategoryFilterModel m_proxyModel;
//     CategoryModel m_model;
//     Id m_currentCategory;
//     Id m_currentPage;
//     QStackedLayout *m_stackedLayout;
//     QListView *m_categoryList;
//     QLabel *m_headerLabel;
//     std::vector<QEventLoop *> m_eventLoops;
//     bool m_running = false;
//     bool m_applied = false;
//     bool m_finished = false;
public:
    explicit SettingsDialog(QWidget *parent = nullptr);

private:
    QTabWidget *tabWidget;
    QDialogButtonBox *buttonBox;
};



class GeneralTab : public QWidget
{
    Q_OBJECT

public:
    explicit GeneralTab(QWidget *parent = nullptr);
};



class LinkBudgetTab : public QWidget
{
    Q_OBJECT

public:
    explicit LinkBudgetTab(QWidget *parent = nullptr);
};
