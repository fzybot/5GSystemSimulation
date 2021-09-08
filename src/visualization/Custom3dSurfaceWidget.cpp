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
                     surface_, &Custom3dSurface::toggleCheckBoxItem);

    QRadioButton *radioButtonOne = new QRadioButton("Heightmap");
    radioButtonOne->setChecked(true);
    radioButtonOne->setFont(font);
    mainLayout->addWidget(radioButtonOne);

    connect(radioButtonOne, &QRadioButton::clicked,
                     surface_, &Custom3dSurface::toggleRadioButtonItem);

    QRadioButton *radioButtonTwo = new QRadioButton("City picture");
    radioButtonTwo->setChecked(false);
    radioButtonTwo->setFont(font);
    mainLayout->addWidget(radioButtonTwo);

    connect(radioButtonTwo, &QRadioButton::clicked,
                     surface_, &Custom3dSurface::toggleRadioButtonItem);

    QRadioButton *radioButtonThree = new QRadioButton("Heatmap");
    radioButtonThree->setChecked(false);
    radioButtonThree->setFont(font);
    mainLayout->addWidget(radioButtonThree);

    connect(radioButtonThree, &QRadioButton::clicked,
                     surface_, &Custom3dSurface::toggleRadioButtonItem);


    QPushButton *modelButton = new QPushButton("CALCULATE");
    modelButton->setFont(font);
    mainLayout->addWidget(modelButton);
    connect(modelButton, &QPushButton::pressed,
                    surface_, &Custom3dSurface::calculateModel);


    mainLayout->addWidget(container);
    setLayout(mainLayout);

}


