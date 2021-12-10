#include "Indexes.h"

Indexes::Indexes()
{
	RegisterRenderable(RenderLayer::above_background);
}

void Indexes::Render(Painter& painter)
{
	painter.PaintIndexes(L'A', L'1');
}