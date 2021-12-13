#include "Checker.h"

#include "Texture.h"

Checker::Checker(Texture texture, int cellY, int cellX)
{
	RegisterRenderable(RenderLayer::middle);

	_texture = texture;
	_cellY = cellY;
	_cellX = cellX;
}

void Checker::Render(Painter& painter) {
	painter.CellPaint(_texture, _cellX, _cellY, 1);
}

bool Checker::NeedRedraw()
{
	return false;
}
