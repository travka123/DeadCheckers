#include "WRendering.h"
#include "WPainter.h"
#include "RenderLayer.h"

WRendering::WRendering(RECT clientRect, float margin, float menuWidth, std::wstring texturesPath) {
    _textures = WTextureSet::LoadFrom(texturesPath);
    _clientRect = clientRect;
    _layout = Layout::GetLayout(clientRect, margin, menuWidth);
}

void WRendering::Render(HDC hDC) {

    WPainter painter(hDC, _clientRect, _textures, _layout);

    for (int i = 0; i < static_cast<int>(RenderLayer::LAYERS_COUNT); i++) {
        for (Renderable* entity : _layers[i]) {
            entity->Render(painter);
        }
    }
}

void WRendering::SetTextures(std::wstring path) {
    _textures = WTextureSet::LoadFrom(path);
}

void WRendering::SetCleintRect(RECT clientRect)
{
    _clientRect = clientRect;
    _layout = Layout::GetLayout(clientRect, _layout.margin, _layout.menuWidth);
}
