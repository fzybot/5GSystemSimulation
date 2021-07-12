#include <QtWidgets>

#include "TabMenu.h"
#include "src/visualization/Custom3dSurfaceWidget.h"


TabMenu::TabMenu(QWidget *parent)
    : QDialog(parent),
      map_(new Map)
{
#pragma region TemporaryCode // Crutch
    map_->resize(1600, 1200);
#pragma endregion TemporaryCode

    tabWidget = new QTabWidget;
    tabWidget->addTab(map_, tr("Map"));

    //tabWidget->addTab();
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    setLayout(mainLayout);
}
