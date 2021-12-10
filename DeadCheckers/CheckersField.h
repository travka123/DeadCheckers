#pragma once

#include "IRenderable.h"
#include "Painter.h"
#include "Indexes.h"

class CheckersField : IRenderable {
private:
	Indexes* _indexes;

public:
	CheckersField(Indexes* indexes);

	void Render(Painter& painter);
};