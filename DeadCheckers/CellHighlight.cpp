#include "CellHighlight.h"

#include "RenderLayer.h"

CellHighlight::CellHighlight()
{
	RegisterRenderable(RenderLayer::under_middle);

	_isHiden = false;
	_needRedraw = true;
}

void CellHighlight::Add(HighlightInfo info)
{
	_highlightCells.push_back(info);
	_needRedraw = true;
}

void CellHighlight::Clear()
{
	_highlightCells.clear();
	_needRedraw = true;
}

void CellHighlight::Hide()
{
	_isHiden = true;
	_needRedraw = true;
}

void CellHighlight::Show()
{
	_isHiden = false;
	_needRedraw = true;
}

void CellHighlight::Render(Painter& painter)
{
	if (!_isHiden) {
		for (HighlightInfo& info : _highlightCells) {
			painter.PaintCellIn(info.color, info.x, info.y);
		}
	}
	_needRedraw = false;
}

bool CellHighlight::NeedRedraw()
{
	return _needRedraw;
}
