#pragma once

#include "IRenderable.h"

class Background : public IRenderable {
public:
	Background();
	void Render(Painter* canvas);
};