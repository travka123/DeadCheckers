#include "Checker.h"

#include "Texture.h"

void Checker::Render(Painter& painter, Rect rect)
{
	painter.Paint(_texture, rect);
	if (_queen) {
		painter.Paint(Texture::crown, rect);
	}
	_needRedraw = false;
}

Checker::Checker(Texture texture, int cellY, int cellX)
{
	RegisterRenderable(RenderLayer::middle);

	_texture = texture;
	_cellY = cellY;
	_cellX = cellX;
	_needRedraw = true;
	_queen = false;
}

Checker::~Checker()
{
	UnregisterRenderable();
}

void Checker::SetCords(int cellX, int cellY)
{
	_cellY = cellY;
	_cellX = cellX;
	_needRedraw = true;
}

void Checker::Crown()
{
	_queen = true;
	_needRedraw = true;
}

void Checker::Render(Painter& painter) {
	
	painter.CellPaint(_texture, _cellX, _cellY, 1);
	if (_queen) {
		painter.CellPaint(Texture::crown, _cellX, _cellY, 1);
	}
	_needRedraw = false;
}

bool Checker::NeedRedraw()
{
	return _needRedraw;
}
