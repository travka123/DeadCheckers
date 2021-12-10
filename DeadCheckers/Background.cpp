#include "Background.h"

#include "Textures.h"

Background::Background()
{
	RegisterRenderable(RenderLayer::background);
}

void Background::Render(Painter& painter) {
	painter.Paint(Texture::background, painter.GetCanvasRect());
}