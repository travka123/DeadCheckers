#pragma once

#include "Renderable.h"

#include "Painter.h"
#include "Texture.h"

class Checker : public Renderable {
private:
	int _cellX;
	int _cellY;
	Texture _texture;

public:
	Checker(Texture texture, int cellX, int cellY);

	void Render(Painter& painter) override;
};