#include <QtDataVisualization/Q3DSurface>
#include <QtWidgets>
#include "Custom3dSurfaceWidget.h"

Custom3dSurfaceWidget::Custom3dSurfaceWidget(QWidget *parent)
    : QWidget(parent)
{
    QtDataVisualization::Q3DSurface *graph = new QtDataVisualization::Q3DSurface();
    QWidget *container = QWidget::createWindowContainer(graph);
    container->setMinimumSize(800, 600);
    container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    container->setFocusPolicy(Qt::StrongFocus);
    surface_ = new Custom3dSurface(graph);

    QVBoxLayout *mainLayout = new QVBoxLayout;

    QFont font = QFont("Century Gothic", 14);
    QLabel *label = new QLabel("Show:");
    font.setBold(true);
    label->setFont(font);
    mainLayout->addWidget(label);

    QCheckBox *checkboxOne = new QCheckBox("Height");
    checkboxOne->setChecked(true);
    checkboxOne->setFont(font);
    mainLayout->addWidget(checkboxOne);

    connect(checkboxOne, &QCheckBox::stateChanged,
                     surface_, &Custom3dSurface::toggleItem);

    QCheckBox *checkboxTwo = new QCheckBox("Buildings");
    checkboxTwo->setChecked(false);
    checkboxTwo->setFont(font);
    mainLayout->addWidget(checkboxTwo);

    connect(checkboxTwo, &QCheckBox::stateChanged,
                     surface_, &Custom3dSurface::toggleItem);

    QCheckBox *checkboxThree = new QCheckBox("Texture");
    checkboxThree->setChecked(false);
    checkboxThree->setFont(font);
    mainLayout->addWidget(checkboxThree);

    connect(checkboxThree, &QCheckBox::stateChanged,
                     surface_, &Custom3dSurface::toggleItem);

    mainLayout->addWidget(container);
    setLayout(mainLayout);

}


