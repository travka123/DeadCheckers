#pragma once

#include "Renderable.h"

#include "Painter.h"
#include "Texture.h"

class Checker : public Renderable {
protected:
	int _cellX;
	int _cellY;
	Texture _texture;

public:
	Checker(Texture texture, int cellY, int cellX);

	void Render(Painter& painter) override;
	bool NeedRedraw() override;
};