#pragma once

#include "CellIndexes.h"

class StringCellIndexes : public CellIndexes {

private:
	std::wstring _top;
	std::wstring _bottom;

public:
	StringCellIndexes(const std::wstring& top, const std::wstring& bottom);
	void Render(Painter& painter);
};