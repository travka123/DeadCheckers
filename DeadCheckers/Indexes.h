#pragma once

#include "IRenderable.h"

class Indexes : IRenderable {
public:
	Indexes();
	void Render(Painter& painter);
};