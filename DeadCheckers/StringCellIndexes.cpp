#include "StringCellIndexes.h"

StringCellIndexes::StringCellIndexes(const std::wstring& top, const std::wstring& bottom) : CellIndexes()
{
	_top = top;
	_bottom = bottom;
}

void StringCellIndexes::Render(Painter& painter) {
	painter.PaintIndexes(_top, _bottom);
}
