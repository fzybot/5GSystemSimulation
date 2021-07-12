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
    mainLayout->addWidget(container);
    setLayout(mainLayout);

}
