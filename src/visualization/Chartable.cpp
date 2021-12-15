#include "Chartable.h"

#include <QDebug>
#include <QtMath>
#include <QtDataVisualization/Q3DSurface>
#include <QtWidgets>

#include "src/visualization/Custom3dSurface.h"

Chartable::Chartable()
{

}

void Chartable::visualize3D()
{
    QtDataVisualization::Q3DSurface *graph = new QtDataVisualization::Q3DSurface();
    QWidget *container = QWidget::createWindowContainer(graph);
    container->setMinimumSize(800, 600);
    container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    container->setFocusPolicy(Qt::StrongFocus);
    surface_ = new Custom3dSurface(graph, dataArray3d_);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(container);

    container->show();
}

void Chartable::visualize2D(float elevation)
{

}