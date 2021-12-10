#include "Background.h"

#include "Textures.h"

Background::Background()
{
	RegisterRenderable(RenderLayer::background);
}

void Background::Render(Painter* canvas) {
	canvas->Paint(Texture::background, canvas->GetCanvasRect());
}