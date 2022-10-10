#include "src/visualization/HeatmapModel.h"
#include "src/equipment/Cell.h"
#include "src/equipment/antenna/Beam.h"
#include "src/protocols/phy/Physical.h"

class HeatmapModelTest : public HeatmapModel
{
public:
    HeatmapModelTest():HeatmapModel(){};
    void setCell(Cell*);
	Cell* cell_;
	void calculateHeatmap3DDDA();
	float calculateAngle(int x, int y);
public slots:
    void calculateHeatmap();
    void changeSettings(void*);
};

//HeatmapModelTest()::HeatmapModel()
//{
//
//}