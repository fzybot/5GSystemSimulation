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
    // Tab widget for Map
    tabWidget->addTab(map_, tr("Map"));

    // Tab widget for 3D plot
    tabWidget->addTab(surfaceWidget_, tr("3D Surface"));
    
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    setLayout(mainLayout);
}
