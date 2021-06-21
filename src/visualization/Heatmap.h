#ifndef HEATMAP_H
#define HEATMAP_H

#include<QPixmap>

class gNodeB;
class UserEquipment;

class Heatmap: public QImage
{
    //Q_OBJECT

public:
    Heatmap();
    void drawHeatmap();

public:

};

#endif // HEATMAP_H
