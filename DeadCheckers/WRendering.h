#pragma once

#include "WTextureSet.h"
#include "Rendering.h"
#include "Layout.h"

class WRendering : public Rendering {
private:
    std::vector<std::wstring> _styles = { 
        L"Media\\Textures\\Standart",
        L"Media\\Textures\\Custom1"
    };
    int _currentStyle;
    WTextureSet _textures;
    RECT _clientRect;
    HBITMAP _layersCache[RENDER_LAYERS_COUNT];
    HBITMAP _totalCache;
    bool _invalidateCache;

    void ReinitCache(HDC compDC);

public:
    WRendering(RECT clientRect, float margin, float menuWidth);

    void Render(HDC hDC);
    void SetTextures(std::wstring path);
    void SetCleintRect(RECT clientRect);
    void SetNextStyle();
};