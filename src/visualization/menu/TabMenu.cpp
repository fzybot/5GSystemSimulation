#include <QtWidgets>

#include "TabMenu.h"


TabMenu::TabMenu(QWidget *parent)
    : QDialog(parent),
      map_(new Map),
      surfaceWidget_(new Custom3dSurfaceWidget)

{
#pragma region TemporaryCode // Crutch
    map_->resize(1600, 1200);
#pragma endregion TemporaryCode

    tabWidget = new QTabWidget;
    tabWidget->addTab(map_, tr("Map"));
    tabWidget->addTab(surfaceWidget_, tr("Plots"));
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    setLayout(mainLayout);
}
