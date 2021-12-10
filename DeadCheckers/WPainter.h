#pragma once

#include "Painter.h"

#include <Windows.h>
#include <string>
#include <vector>

#include "Rect.h"
#include "CellRect.h"
#include "WTextureSet.h"

class WPainter : public Painter {

private:
	HDC _hDC;
	WTextureSet _textures;
	RECT _clientRect;

	float _cellSize;
	float _marginLeft;
	float _marginTop;

public:
	WPainter(HDC hDC, RECT rect, WTextureSet textures);

	Rect GetCanvasRect();
	void Paint(Texture texture, Rect rect);
	void Paint(Texture texture, std::vector<Rect>& rects);
	void CellPaint(Texture texture, std::vector<CellRect>& cells);
	void PaintIndexes(wchar_t top, wchar_t bottom);
};