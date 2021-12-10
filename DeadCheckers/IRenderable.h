#pragma once

#include "Painter.h"
#include "RenderLayer.h"

class IRenderable {
protected:
	void RegisterRenderable(RenderLayer layer);
public:
	virtual void Render(Painter* canvas) = 0;
};