#include "ResourceGrid.h"
#include "src/protocols/phy/Bandwidth.h"

#include <QDebug>

ResourceGrid::ResourceGrid()
{

}

void ResourceGrid::setBw(Bandwidth *bw)
{
    _bw = bw;
}

Bandwidth *ResourceGrid::getBw()
{
    return _bw;
}

void ResourceGrid::configResourceGrid(bool cpType, int nPrb)
{
    qDebug() << "Configuring resource grid...";
    int cp = 14;
    if (cpType == false){
        cp = 12;
    }
    _resourceGrid.resize(cp);
    for (int i = 0; i < _resourceGrid.size(); i++){
        _resourceGrid[i].resize(nPrb * 12);
    }
}
