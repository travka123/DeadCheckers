#include "Checker.h"

#include "Texture.h"

Checker::Checker(Texture texture, int cellY, int cellX)
{
	RegisterRenderable(RenderLayer::middle);

	_texture = texture;
	_cellY = cellY;
	_cellX = cellX;
	_needRedraw = true;
}

void Checker::SetCords(int cellX, int cellY)
{
	_cellY = cellY;
	_cellX = cellX;
	_needRedraw = true;
}

void Checker::Render(Painter& painter) {
	painter.CellPaint(_texture, _cellX, _cellY, 1);
	_needRedraw = false;
}

bool Checker::NeedRedraw()
{
	return _needRedraw;
}
