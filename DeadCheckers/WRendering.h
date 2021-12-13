#pragma once

#include "WTextureSet.h"
#include "Rendering.h"
#include "Layout.h"

class WRendering : public Rendering {
private:
    WTextureSet _textures;
    RECT _clientRect;
    HBITMAP _layersCache[RENDER_LAYERS_COUNT];
    HBITMAP _totalCache;
    bool _invalidateCache;

    void ReinitCache(HDC compDC);

public:
    WRendering(RECT clientRect, float margin, float menuWidth, std::wstring texturesPath);

    void Render(HDC hDC);
    void SetTextures(std::wstring path);
    void SetCleintRect(RECT clientRect);
};