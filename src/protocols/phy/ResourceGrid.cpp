#include "ResourceGrid.h"
#include "src/protocols/phy/Bandwidth.h"

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

void ResourceGrid::configResourceGrid(Bandwidth *bw)
{
    setBw(bw);
    int cp = 14;
    if (bw->getCpType() == false){
        cp = 12;
    }
    _resourceGrid.resize(cp);
    for (int i = 0; i < _resourceGrid.size(); i++){
        _resourceGrid[i].resize(bw->getNumberOfPRB() * 12);
    }
}
