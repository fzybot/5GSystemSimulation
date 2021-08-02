#include "Cell.h"


Cell::Cell(int id)
{
	setCellID(id);
}

void Cell::setCellID(int cellID)
{
	id_ = cellID;
}

int Cell::getCellID()
{
	return id_;
}
