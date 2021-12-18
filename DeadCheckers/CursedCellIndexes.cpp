#include "CursedCellIndexes.h"

CursedCellIndexes::CursedCellIndexes() : CellIndexes()
{
	currentStartX = startX;
	currentStartY = startY;
}

void CursedCellIndexes::Render(Painter& painter)
{
	_beforeNextRedraw = framesBeforeRedraw;

	if (currentStartX > startY) {
		currentStartX = startX;
		currentStartY = startY;
	}

	painter.PaintIndexes(currentStartX, currentStartY);

	currentStartX += 8;
	currentStartY -= 8;
}

bool CursedCellIndexes::NeedRedraw()
{
	return !_beforeNextRedraw--;
}
