#include "ResourceGrid.h"

ResourceGrid::ResourceGrid(int nPrb, int nOfdmSymbols, QVector<QVector<int>> &dmrsPattern, QVector<QVector<int>> &coresetPattern)
{

}


void ResourceGrid::createResourceGrid(int nPrb, int nOfdmSymbols)
{
    _resourceGrid.resize(nOfdmSymbols);
    for (int i = 0; i < _resourceGrid.size(); i++){
        _resourceGrid[i].resize(nPrb * 12);
    }
}