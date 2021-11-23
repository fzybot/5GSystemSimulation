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


class QComboBox;
class QStringListModel;
class QDataWidgetMapper;
class QGroupBox;
class QVBoxLayout;
class QRadioButton;

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

private:

    QVBoxLayout *globalVBox;

    QGroupBox *cellViewGroupBox;
    QGroupBox *ueViewGroupBox;

    QDataWidgetMapper *mapper;

    QLabel *numberOfCellLabel;
    QLineEdit *numberOfCellLineEdit;

    QLabel *numberOfUeLabel;
    QLineEdit *numberOfUeLineEdit;

    QStringListModel *numerologyModel;
    QLabel *numerologyLabel;
    QComboBox *numerologyComboBox;

    QStringListModel *bandModel;
    QLabel *bandLabel;
    QComboBox *bandComboBox;

    QStringListModel *bandwidthModel;
    QLabel *bandwidthLabel;
    QComboBox *bandwidthComboBox;

    QStringListModel *channelModelModel;
    QLabel *channelModelLabel;
    QComboBox *channelModelComboBox;

    QLabel *dopplerLabel;
    QRadioButton *dopplerRadioButton;

    QStringListModel *mobilityModelModel;
    QLabel *mobilityModelLabel;
    QComboBox *mobilityModelComboBox;

    QStringListModel *distributionModel;
    QLabel *distributionLabel;
    QComboBox *distributionComboBox;


public:
    explicit GeneralTab(QWidget *parent = nullptr);
};



class LinkBudgetTab : public QWidget
{
    Q_OBJECT

private:

    QVBoxLayout *globalVBox;

    QGroupBox *cellViewGroupBox;
    QGroupBox *ueViewGroupBox;

    QDataWidgetMapper *mapper;

    QLabel *cellTxPowerLabel;
    QLineEdit *cellTxPowerLineEdit;

    QLabel *cellFeederLosLabel;
    QLineEdit *cellFeederLosLineEdit;

    QLabel *antennaGainLabel;
    QLineEdit *antennaGainLineEdit;

    QLabel *noiseFigureLabel;
    QLineEdit *noiseFigureLineEdit;

    QStringListModel *antennaConfigModel;
    QLabel *antennaConfigLabel;
    QComboBox *antennaConfigComboBox;

    QStringListModel *propagationModelModel;
    QLabel *propagationModelLabel;
    QComboBox *propagationModelComboBox;

    QLabel *ueTxPowerLabel;
    QLineEdit *ueTxPowerLineEdit;

    QLabel *ueFeederLosLabel;
    QLineEdit *ueFeederLosLineEdit;

    QLabel *ueAntennaGainLabel;
    QLineEdit *ueAntennaGainLineEdit;

    QLabel *ueNoiseFigureLabel;
    QLineEdit *ueNoiseFigureLineEdit;

public:
    explicit LinkBudgetTab(QWidget *parent = nullptr);
};
