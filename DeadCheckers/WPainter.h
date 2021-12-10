#pragma once

#include "Painter.h"

#include <Windows.h>
#include <string>
#include <vector>

#include "Rect.h"
#include "WTextureSet.h"

class WPainter : public Painter {

private:
	HDC _hDC;
	WTextureSet _textures;
	RECT _clientRect;

public:
	WPainter(HDC hDC, RECT rect, WTextureSet textures);

	Rect GetCanvasRect();
	void Paint(Texture texture, Rect rect);
	void Paint(Texture texture, std::vector<Rect> rects);
};