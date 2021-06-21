#pragma once


#include <QPixmap>


class gNodeB;
class UserEquipment;

class Heatmap: public QImage
{
public:
    Heatmap();

    void drawHeatmap();
};
