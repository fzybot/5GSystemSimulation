#include <QtWidgets>
#include <QComboBox>
#include "SettingsDialog.h"

SettingsDialog::SettingsDialog(QWidget *parent)
    :QDialog(parent)
{
    tabWidget = new QTabWidget;
    tabWidget->addTab(new GeneralTab(), tr("General Parameters"));
    tabWidget->addTab(new LinkBudgetTab(), tr("Link Budget"));

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    setWindowTitle(tr("Tab Dialog"));
}

GeneralTab::GeneralTab(QWidget *parent)
    : QWidget(parent)
{
    QStringList numerologyIndex;
    numerologyIndex << tr("15 [kHz]") << tr("30 [kHz]") << tr("60 [kHz]") << tr("120 [kHz]");
    numerologyModel = new QStringListModel(numerologyIndex, this);
    numerologyLabel = new QLabel(tr("&Numerology:"));
    numerologyComboBox = new QComboBox();
    numerologyComboBox->setModel(numerologyModel);

    mapper = new QDataWidgetMapper(this);
    mapper->addMapping(numerologyComboBox, 1, "currentIndex");

    QGridLayout *mainLayout = new QGridLayout();
    mainLayout->addWidget(numerologyLabel, 0, 0, 1, 1);
    mainLayout->addWidget(numerologyComboBox, 0, 1, 1, 1);
    setLayout(mainLayout);
}


LinkBudgetTab::LinkBudgetTab(QWidget *parent)
    : QWidget(parent)
{
    QString fileName = "/src/hello.txt";
    QFileInfo fileInfo(fileName);
    QGroupBox *permissionsGroup = new QGroupBox(tr("Permissions"));

    QCheckBox *readable = new QCheckBox(tr("Readable"));
    if (fileInfo.isReadable())
        readable->setChecked(true);

    QCheckBox *writable = new QCheckBox(tr("Writable"));
    if ( fileInfo.isWritable() )
        writable->setChecked(true);

    QCheckBox *executable = new QCheckBox(tr("Executable"));
    if ( fileInfo.isExecutable() )
        executable->setChecked(true);

    QGroupBox *ownerGroup = new QGroupBox(tr("Ownership"));

    QLabel *ownerLabel = new QLabel(tr("Owner"));
    QLabel *ownerValueLabel = new QLabel(fileInfo.owner());
    ownerValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QLabel *groupLabel = new QLabel(tr("Group"));
    QLabel *groupValueLabel = new QLabel(fileInfo.group());
    groupValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QVBoxLayout *permissionsLayout = new QVBoxLayout;
    permissionsLayout->addWidget(readable);
    permissionsLayout->addWidget(writable);
    permissionsLayout->addWidget(executable);
    permissionsGroup->setLayout(permissionsLayout);

    QVBoxLayout *ownerLayout = new QVBoxLayout;
    ownerLayout->addWidget(ownerLabel);
    ownerLayout->addWidget(ownerValueLabel);
    ownerLayout->addWidget(groupLabel);
    ownerLayout->addWidget(groupValueLabel);
    ownerGroup->setLayout(ownerLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(permissionsGroup);
    mainLayout->addWidget(ownerGroup);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}
