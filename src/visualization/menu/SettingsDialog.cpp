#include <QtWidgets>
#include <QComboBox>
#include "SettingsDialog.h"
#include "src/visualization/menu/mainWindow.h"

SettingsDialog::SettingsDialog(QWidget *parent)
    :QDialog(parent)
{
    tabWidget = new QTabWidget;
    tabWidget->addTab(new GeneralTab(), tr("General Parameters"));
    tabWidget->addTab(new LinkBudgetTab(), tr("Link Budget"));

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    connect(this, &SettingsDialog::settingsChanged, (MainWindow*)parent, &MainWindow::changeSettings);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    setWindowTitle(tr("Tab Dialog"));
}

SettingsDialog::~SettingsDialog()
{
    int result = this->result();
    qDebug() << "settings accepted " << result;
    if(result){
        QObject* gnrl = tabWidget->widget(0);
        QObject* lnkBdgt = tabWidget->widget(1);
        GeneralTab *general = qobject_cast<GeneralTab*>(gnrl);
        LinkBudgetTab *linkBudget = qobject_cast<LinkBudgetTab*>(lnkBdgt);
        MainWindow* prnt = (MainWindow*)parent();

        int numberOfCell = general->numberOfCellLineEdit->text().toInt();
        QString band = general->bandComboBox->currentText();
        int numerology = general->numerologyComboBox->currentIndex();
        int bandwidth = general->bandwidthComboBox->currentIndex();
        int channelModel = general->channelModelComboBox->currentIndex();
        int doppler = general->dopplerRadioButton->isChecked();
        int numberOfUe = general->numberOfUeLineEdit->text().toInt();
        int mobilityModel = general->mobilityModelComboBox->currentIndex();
        int ueDistribution = general->distributionComboBox->currentIndex();

        prnt->simulationSettings.numberOfCell = numberOfCell;
        prnt->simulationSettings.band = (band.remove(0, 5)).toInt();
        prnt->simulationSettings.numerology = numerology;
        prnt->simulationSettings.bandwidth = bandwidth;
        prnt->simulationSettings.channelModel = channelModel;
        prnt->simulationSettings.dopplerUsage = doppler;
        prnt->simulationSettings.numberOfUEs = numberOfUe;
        prnt->simulationSettings.mobilityModel = mobilityModel;
        prnt->simulationSettings.ueDistribution = ueDistribution;

        double cellTxPower = linkBudget->cellTxPowerLineEdit->text().toDouble();
        double cellFeederLos = linkBudget->cellFeederLosLineEdit->text().toDouble();
        int antennaConfig = linkBudget->antennaConfigComboBox->currentIndex();
        double cellAntennaGain = linkBudget->antennaGainLineEdit->text().toDouble();
        double cellNoiseFigure = linkBudget->noiseFigureLineEdit->text().toDouble();
        int propagationModel = linkBudget->propagationModelComboBox->currentIndex();
        int heightUsage = linkBudget->heightUsageCheckBox->isChecked();
        int buildingsUsage = linkBudget->buildingsUsageCheckBox->isChecked();
        double ueTxPower = linkBudget->ueTxPowerLineEdit->text().toDouble();
        double ueFeederLos = linkBudget->ueFeederLosLineEdit->text().toDouble();
        double ueAntennaGain = linkBudget->ueAntennaGainLineEdit->text().toDouble();
        double ueNoiseFigure = linkBudget->ueNoiseFigureLineEdit->text().toDouble();

        prnt->simulationSettings.cellTxPower = cellTxPower;
        prnt->simulationSettings.cellFeederLos = cellFeederLos;
        prnt->simulationSettings.antennaConfig= antennaConfig;
        prnt->simulationSettings.cellAntennaGain = cellAntennaGain;
        prnt->simulationSettings.cellNoiseFigure = cellNoiseFigure;
        prnt->simulationSettings.propagationModel = propagationModel;
        prnt->simulationSettings.heightUsage = heightUsage;
        prnt->simulationSettings.buildingsUsage = buildingsUsage;
        prnt->simulationSettings.ueTxPower = ueTxPower;
        prnt->simulationSettings.ueFeederLos = ueFeederLos;
        prnt->simulationSettings.ueAntennaGain = ueAntennaGain;
        prnt->simulationSettings.ueNoiseFigure = ueNoiseFigure;

        emit settingsChanged(&(prnt->simulationSettings));
    }

}

GeneralTab::GeneralTab(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *globalVBox = new QVBoxLayout;

    // ---- Cell --------------------------------------------------
    QGroupBox *cellViewGroupBox = new QGroupBox(QStringLiteral("Cell settings"));

    numberOfCellLabel = new QLabel(tr("Number Of Cell:"));
    numberOfCellLineEdit = new QLineEdit("1");

    QStringList numerologyIndex;
    numerologyIndex << tr("15 [kHz]") << tr("30 [kHz]") << tr("60 [kHz]") << tr("120 [kHz]");
    numerologyModel = new QStringListModel(numerologyIndex, this);
    numerologyLabel = new QLabel(tr("Numerology:"));
    numerologyComboBox = new QComboBox();
    numerologyComboBox->setModel(numerologyModel);

    QStringList bandIndex;
    bandIndex   << tr("band 1") << tr("band 3") << tr("band 7") << tr("band 8") << tr("...")
                << tr("band 20") << tr("band 25") << tr("band 30") << tr("band 41") << tr("...")
                << tr("band 79") << tr("...") << tr("band 257");
    bandModel = new QStringListModel(bandIndex, this);
    bandLabel = new QLabel(tr("Band:"));
    bandComboBox = new QComboBox();
    bandComboBox->setModel(bandModel);

    QStringList bandwidthIndex;
    if (numerologyComboBox->currentIndex() == 0) {
        bandwidthIndex  << tr("10 [MHz]") << tr("15 [MHz]") << tr("20 [MHz]") << tr("25 [MHz]") 
                        << tr("30 [MHz]") << tr("40 [MHz]") << tr("50 [MHz]");
    } else if(numerologyComboBox->currentIndex() == 1) {
        bandwidthIndex  << tr("5 [MHz]") << tr("10 [MHz]") << tr("15 [MHz]") << tr("20 [MHz]") << tr("25 [MHz]") 
                        << tr("30 [MHz]") << tr("40 [MHz]") << tr("50 [MHz]") << tr("60 [MHz]") 
                        << tr("70 [MHz]") << tr("80 [MHz]") << tr("90 [MHz]") << tr("100 [MHz]");
    } else if(numerologyComboBox->currentIndex() == 2) {
        bandwidthIndex  << tr("15 [MHz]") << tr("20 [MHz]") << tr("25 [MHz]") 
                        << tr("30 [MHz]") << tr("40 [MHz]") << tr("50 [MHz]") << tr("60 [MHz]") 
                        << tr("70 [MHz]") << tr("80 [MHz]") << tr("90 [MHz]") << tr("100 [MHz]");
    } else if(numerologyComboBox->currentIndex() == 3) {
        bandwidthIndex  << tr("100 [MHz]") << tr("200 [MHz]") << tr("400 [MHz]");
    }
    bandwidthModel = new QStringListModel(bandwidthIndex, this);
    bandwidthLabel = new QLabel(tr("Bandwidth:"));
    bandwidthComboBox = new QComboBox();
    bandwidthComboBox->setModel(bandwidthModel);
    bandwidthComboBox->setCurrentIndex(6);

    QStringList channelModelIndex;
    channelModelIndex << tr("AWGN") << tr("Rician") << tr("Rayleigh") << tr("...");
    channelModelModel = new QStringListModel(channelModelIndex, this);
    channelModelLabel = new QLabel(tr("channelModel:"));
    channelModelComboBox = new QComboBox();
    channelModelComboBox->setModel(channelModelModel);

    dopplerLabel = new QLabel(tr("Doppler usage:"));
    dopplerRadioButton = new QRadioButton("Doppler");

    mapper = new QDataWidgetMapper(this);
    mapper->addMapping(numerologyComboBox, 1, "currentIndex");

    QGridLayout *cellLayout = new QGridLayout();
    cellLayout->addWidget(numberOfCellLabel, 0, 0, 1, 1);
    cellLayout->addWidget(numberOfCellLineEdit, 0, 1, 1, 1);
    cellLayout->addWidget(bandLabel, 1, 0, 1, 1);
    cellLayout->addWidget(bandComboBox, 1, 1, 1, 1);
    cellLayout->addWidget(numerologyLabel, 2, 0, 1, 1);
    cellLayout->addWidget(numerologyComboBox, 2, 1, 1, 1);
    cellLayout->addWidget(bandwidthLabel, 3, 0, 1, 1);
    cellLayout->addWidget(bandwidthComboBox, 3, 1, 1, 1);
    cellLayout->addWidget(channelModelLabel, 4, 0, 1, 1);
    cellLayout->addWidget(channelModelComboBox, 4, 1, 1, 1);
    cellLayout->addWidget(dopplerLabel, 5, 0, 1, 1);
    cellLayout->addWidget(dopplerRadioButton, 5, 1, 1, 1);

    cellViewGroupBox->setLayout(cellLayout);

    // ---- UE --------------------------------------------------
    QGroupBox *ueViewGroupBox = new QGroupBox(QStringLiteral("User Equipment settings"));

    numberOfUeLabel = new QLabel(tr("Number Of UEs:"));
    numberOfUeLineEdit = new QLineEdit("12");

    QStringList mobilityModelIndex;
    mobilityModelIndex << tr("Mixed") << tr("Random Walk") << tr("Random Waypoint") << tr("Gauss-Markov");
    mobilityModelModel = new QStringListModel(mobilityModelIndex, this);
    mobilityModelLabel = new QLabel(tr("Mobility Model:"));
    mobilityModelComboBox = new QComboBox();
    mobilityModelComboBox->setModel(mobilityModelModel);

    QStringList distributionIndex;
    distributionIndex << tr("Normal (Gaussian)") << tr("...");
    distributionModel = new QStringListModel(distributionIndex, this);
    distributionLabel = new QLabel(tr("UE distribution:"));
    distributionComboBox = new QComboBox();
    distributionComboBox->setModel(distributionModel);

    QGridLayout *ueLayout = new QGridLayout();
    ueLayout->addWidget(numberOfUeLabel, 0, 0, 1, 1);
    ueLayout->addWidget(numberOfUeLineEdit, 0, 1, 1, 1);
    ueLayout->addWidget(mobilityModelLabel, 1, 0, 1, 1);
    ueLayout->addWidget(mobilityModelComboBox, 1, 1, 1, 1);
    ueLayout->addWidget(distributionLabel, 2, 0, 1, 1);
    ueLayout->addWidget(distributionComboBox, 2, 1, 1, 1);

    ueViewGroupBox->setLayout(ueLayout);

    globalVBox->addWidget(cellViewGroupBox);
    globalVBox->addWidget(ueViewGroupBox);

    setLayout(globalVBox);
}

LinkBudgetTab::LinkBudgetTab(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *globalVBox = new QVBoxLayout;

    // ---- Cell --------------------------------------------------
    QGroupBox *cellViewGroupBox = new QGroupBox(QStringLiteral("Cell settings"));

    cellTxPowerLabel = new QLabel(tr("Tx Power [dBm]:"));
    cellTxPowerLineEdit = new QLineEdit("43");

    cellFeederLosLabel = new QLabel(tr("Feeder Los [dB]:"));
    cellFeederLosLineEdit = new QLineEdit("3");

    QStringList antennaConfigIndex;
    antennaConfigIndex << tr("Omni") << tr("2-sector") << tr("3-sector") << tr("6-sector");
    antennaConfigModel = new QStringListModel(antennaConfigIndex, this);
    antennaConfigLabel = new QLabel(tr("Antenna Config:"));
    antennaConfigComboBox = new QComboBox();
    antennaConfigComboBox->setModel(antennaConfigModel);

    antennaGainLabel = new QLabel(tr("Antenna Gain [dBi]:"));
    antennaGainLineEdit = new QLineEdit("12");

    noiseFigureLabel = new QLabel(tr("Noise Figure [dB]:"));
    noiseFigureLineEdit = new QLineEdit("4");

    QStringList propagationModelIndex;
    propagationModelIndex   << tr("Urban Macro") << tr("Urban Micro") << tr("Urban Micro - Street Canyon") << tr("RMa");
    propagationModelModel = new QStringListModel(propagationModelIndex, this);
    propagationModelLabel = new QLabel(tr("Propagation Model:"));
    propagationModelComboBox = new QComboBox();
    propagationModelComboBox->setModel(propagationModelModel);

    heightUsageLable = new QLabel(tr("Height Usage:"));
    heightUsageCheckBox = new QCheckBox("Height above sea level");
    heightUsageCheckBox->setCheckState(Qt::Checked);

    buildingsUsageLable = new QLabel(tr("Buildings Usage:"));
    buildingsUsageCheckBox = new QCheckBox("Number of floors in buildings");
    buildingsUsageCheckBox->setCheckState(Qt::Checked);

    QGridLayout *cellLayout = new QGridLayout();
    cellLayout->addWidget(cellTxPowerLabel, 0, 0, 1, 1);
    cellLayout->addWidget(cellTxPowerLineEdit, 0, 1, 1, 1);
    cellLayout->addWidget(cellFeederLosLabel, 1, 0, 1, 1);
    cellLayout->addWidget(cellFeederLosLineEdit, 1, 1, 1, 1);
    cellLayout->addWidget(antennaConfigLabel, 2, 0, 1, 1);
    cellLayout->addWidget(antennaConfigComboBox, 2, 1, 1, 1);
    cellLayout->addWidget(antennaGainLabel, 3, 0, 1, 1);
    cellLayout->addWidget(antennaGainLineEdit, 3, 1, 1, 1);
    cellLayout->addWidget(noiseFigureLabel, 4, 0, 1, 1);
    cellLayout->addWidget(noiseFigureLineEdit, 4, 1, 1, 1);
    cellLayout->addWidget(propagationModelLabel, 5, 0, 1, 1);
    cellLayout->addWidget(propagationModelComboBox, 5, 1, 1, 1);
    cellLayout->addWidget(heightUsageLable, 6, 0, 1, 1);
    cellLayout->addWidget(heightUsageCheckBox, 6, 1, 1, 1);
    cellLayout->addWidget(buildingsUsageLable, 7, 0, 1, 1);
    cellLayout->addWidget(buildingsUsageCheckBox, 7, 1, 1, 1);

    cellViewGroupBox->setLayout(cellLayout);

    // ---- UE --------------------------------------------------
    QGroupBox *ueViewGroupBox = new QGroupBox(QStringLiteral("User Equipment settings"));

    ueTxPowerLabel = new QLabel(tr("Tx Power [dBm]:"));
    ueTxPowerLineEdit = new QLineEdit("23");

    ueFeederLosLabel = new QLabel(tr("Feeder Los [dB]:"));
    ueFeederLosLineEdit = new QLineEdit("0");

    ueAntennaGainLabel = new QLabel(tr("Antenna Gain [dBi]:"));
    ueAntennaGainLineEdit = new QLineEdit("0");

    ueNoiseFigureLabel = new QLabel(tr("Noise Figure [dB]:"));
    ueNoiseFigureLineEdit = new QLineEdit("7");


    QGridLayout *ueLayout = new QGridLayout();
    ueLayout->addWidget(ueTxPowerLabel, 0, 0, 1, 1);
    ueLayout->addWidget(ueTxPowerLineEdit, 0, 1, 1, 1);
    ueLayout->addWidget(ueFeederLosLabel, 1, 0, 1, 1);
    ueLayout->addWidget(ueFeederLosLineEdit, 1, 1, 1, 1);
    ueLayout->addWidget(ueAntennaGainLabel, 2, 0, 1, 1);
    ueLayout->addWidget(ueAntennaGainLineEdit, 2, 1, 1, 1);
    ueLayout->addWidget(ueNoiseFigureLabel, 3, 0, 1, 1);
    ueLayout->addWidget(ueNoiseFigureLineEdit, 3, 1, 1, 1);

    ueViewGroupBox->setLayout(ueLayout);

    globalVBox->addWidget(cellViewGroupBox);
    globalVBox->addWidget(ueViewGroupBox);

    setLayout(globalVBox);
}
