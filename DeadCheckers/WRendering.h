#pragma once

#include "WTextureSet.h"
#include "Rendering.h"
#include "Layout.h"

class WRendering : public Rendering {
private:
    WTextureSet _textures;
    Layout _layout;
    RECT _clientRect;

public:
    WRendering(RECT clientRect, float margin, float menuWidth, std::wstring texturesPath);

    void Render(HDC hDC);
    void SetTextures(std::wstring path);
    void SetCleintRect(RECT clientRect);
};