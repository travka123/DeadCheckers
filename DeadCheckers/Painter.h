#pragma once

#include "Rect.h"
#include "Textures.h"

class Painter {
public:
	virtual Rect GetCanvasRect() = 0;
	virtual void Paint(Texture texture, Rect rect) = 0;
};