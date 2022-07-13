#include "Physical.h"
#include "src/protocols/phy/Bandwidth.h"
#include "src/protocols/phy/Symbol.h"
#include "src/protocols/phy/Channel/RadioChannel.h"
#include "src/commonParameters.h"
#include "src/protocols/phy/ResourceGrid.h"
#include "src/equipment/antenna/AntennaArray.h"

Physical::Physical()
{

}

void Physical::defaultPhyConfig(Physical::MIMO_MODE mode, int carrierAgg)
{
    _mimoMode = mode;
    getBandwidthContainer().resize(carrierAgg);
    getResourceGridContainer().resize(carrierAgg);
    for (int i = 0; i < carrierAgg; i++)
    {
        switch (_mimoMode)
        {
            // IMPORTANT! -- do not miss MIMO Indexes
            case Physical::MIMO_MODE::MIMO_2x2:
                getResourceGridContainer()[i].resize(2);
                configNewBandwidth("FR1", "n3", NUMEROLOGY[numerologyIndex_], true, 50, 50, 0, 0, true, 0, i);
                configNewBandwidth("FR1", "n3", NUMEROLOGY[numerologyIndex_], true, 50, 50, 0, 0, true, 1, i);
                break;
            case Physical::MIMO_MODE::MIMO_4x4:
                getResourceGridContainer()[i].resize(4);
                configNewBandwidth("FR1", "n3", NUMEROLOGY[numerologyIndex_], true, 50, 50, 0, 0, true, 0, i);
                configNewBandwidth("FR1", "n3", NUMEROLOGY[numerologyIndex_], true, 50, 50, 0, 0, true, 1, i);
                configNewBandwidth("FR1", "n3", NUMEROLOGY[numerologyIndex_], true, 50, 50, 0, 0, true, 2, i);
                configNewBandwidth("FR1", "n3", NUMEROLOGY[numerologyIndex_], true, 50, 50, 0, 0, true, 3, i);
                break;
            default:
                getResourceGridContainer()[i].resize(1);
                configNewBandwidth("FR1", "n3", NUMEROLOGY[numerologyIndex_], true, 50, 50, 0, 0, true, 0, i);
        }
    }
}

void Physical::addBandwidth(int carrierAggIndex, Bandwidth *b)
{
    _bandwidthContainerMimoCarrierAgg[carrierAggIndex].push_back(b);
}

QVector< QVector<Bandwidth*> > &Physical::getBandwidthContainer()
{
    return _bandwidthContainerMimoCarrierAgg;
}

QVector<QVector<ResourceGrid *>> &Physical::getResourceGridContainer()
{
    return _resourceGridContainer;
}

ResourceGrid *Physical::getResourceGridPerMimoCarrAgg(int carrAggIndex, int mimoIndex)
{
    return _resourceGridContainer[carrAggIndex][mimoIndex];
}

void Physical::configNewBandwidth( QString fr, QString band, int scs, bool cpType, double ulBw,
                                double dlBw, int ulOffset, int dlOffset, bool tddTrue, int mimoIndex, int carrAggIndex)
{
    //QString fr, QString band, int scs, double ulBw, double dlBw, int ulOffset, int dlOffset, bool tddTrue = true
    Bandwidth *bw = new Bandwidth(fr, band, scs, cpType, ulBw, dlBw, ulOffset, dlOffset, mimoIndex, tddTrue);
    bw->setCoresetSize(2, bw->getNumberOfPRB() - 30);
    addBandwidth(carrAggIndex, bw);
    configResourceGrid(bw, carrAggIndex, mimoIndex);
}

void Physical::configResourceGrid(Bandwidth *bw, int carrAggIndex, int mimoIndex)
{
    _resourceGridContainer[carrAggIndex][mimoIndex] = new ResourceGrid();
    _resourceGridContainer[carrAggIndex][mimoIndex]->configResourceGrid(bw);
}

Physical::MIMO_MODE &Physical::getMimoMode()
{
    return _mimoMode;
}

void Physical::addAntennaArray(AntennaArray::AntennaType type, int sizeX, int sizeY, 
                    float azimuth, float elevation, float beamWidth, float sectorWidth)
{

    _antennaArray = new AntennaArray(type, sizeX, sizeY, azimuth, elevation, beamWidth, sectorWidth);
}

AntennaArray *Physical::getAntennaArray()
{
    return _antennaArray;
}
