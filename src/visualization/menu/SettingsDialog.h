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
    ~SettingsDialog();

private:
    QTabWidget *tabWidget;
    QDialogButtonBox *buttonBox;

signals:
    void settingsChanged(int*);

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

    QLabel *numberOfUeLabel;

    QStringListModel *numerologyModel;
    QLabel *numerologyLabel;

    QStringListModel *bandModel;
    QLabel *bandLabel;

    QStringListModel *bandwidthModel;
    QLabel *bandwidthLabel;

    QStringListModel *channelModelModel;
    QLabel *channelModelLabel;

    QLabel *dopplerLabel;

    QStringListModel *mobilityModelModel;
    QLabel *mobilityModelLabel;

    QStringListModel *distributionModel;
    QLabel *distributionLabel;


public:
    explicit GeneralTab(QWidget *parent = nullptr);

    QLineEdit *numberOfCellLineEdit;
    QLineEdit *numberOfUeLineEdit;
    QComboBox *bandComboBox;
    QComboBox *numerologyComboBox;
    QComboBox *bandwidthComboBox;
    QComboBox *channelModelComboBox;
    QRadioButton *dopplerRadioButton;
    QComboBox *mobilityModelComboBox;
    QComboBox *distributionComboBox;

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

    QLabel *cellFeederLosLabel;

    QLabel *antennaGainLabel;

    QLabel *noiseFigureLabel;

    QStringListModel *antennaConfigModel;
    QLabel *antennaConfigLabel;

    QStringListModel *propagationModelModel;
    QLabel *propagationModelLabel;

    QLabel *ueTxPowerLabel;

    QLabel *ueFeederLosLabel;

    QLabel *ueAntennaGainLabel;

    QLabel *ueNoiseFigureLabel;

public:
    explicit LinkBudgetTab(QWidget *parent = nullptr);

    QLineEdit *cellTxPowerLineEdit;
    QLineEdit *cellFeederLosLineEdit;
    QLineEdit *antennaGainLineEdit;
    QLineEdit *noiseFigureLineEdit;
    QComboBox *antennaConfigComboBox;
    QComboBox *propagationModelComboBox;
    QLineEdit *ueTxPowerLineEdit;
    QLineEdit *ueFeederLosLineEdit;
    QLineEdit *ueAntennaGainLineEdit;
    QLineEdit *ueNoiseFigureLineEdit;
};
