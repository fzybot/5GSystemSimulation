#include "Map.h"

#include <QPainter>



// ----- [ CONSTRUCTORS ] ----------------------------------------------------------------------------------------------

Map::Map(QWidget *parent) :
    QWidget(parent),
    mapQuickWidget_(new MapQuickWidget),
    heatmap_(new Heatmap(mapQuickWidget_))
{ }



// ----- [ PROTECTED METHODS ] -----------------------------------------------------------------------------------------

void Map::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
   // QPainter painter(this);
   // painter.drawImage(rect(), heatmap_);
}
