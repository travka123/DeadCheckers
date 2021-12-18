#include "Background.h"
#include "RenderLayer.h"

Background::Background() {
    RegisterRenderable(RenderLayer::background);
}

Background::~Background()
{
    UnregisterRenderable();
}

void Background::Render(Painter& painter) {
    painter.Paint(Texture::background, painter.GetCanvasRect());
}

bool Background::NeedRedraw()
{
    return false;
}
