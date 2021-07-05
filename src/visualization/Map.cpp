#include "Map.h"

#include <QPainter>
#include <QGridLayout>



// ----- [ CONSTRUCTORS ] ----------------------------------------------------------------------------------------------

Map::Map(QWidget *parent) :
    QWidget(parent),
    mapQuickWidget_(new MapQuickWidget),
    heatmap_(new Heatmap(mapQuickWidget_))
{
    heatmap_->resize(500, 500);
}



// ----- [ PROTECTED METHODS ] -----------------------------------------------------------------------------------------

void Map::paintEvent(QPaintEvent*)
{
    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(mapQuickWidget_, 0, 0);
}
void Map::resizeEvent(QResizeEvent* event)
{
    mapQuickWidget_->resize(event->size());
}
