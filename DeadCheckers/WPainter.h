#pragma once

#include "Painter.h"
#include "WTextureSet.h"
#include "Rects.h"
#include <windows.h>
#include <vector>

#include "Layout.h"

class WPainter : public Painter {
private:
    HDC _hDC;
    WTextureSet _textures;
    RECT _clientRect;
    Layout _layout;

public:
    WPainter(HDC hDC, RECT rect, WTextureSet textures, Layout layout);
    Rect GetCanvasRect() override;
    void Paint(Texture texture, Rect rect) override;
    void Paint(Texture texture, std::vector<Rect>& rects);
    void CellPaint(Texture texture, int x, int y) override;
    void CellPaint(Texture texture, std::vector<CellRect>& cells) override;
    void PaintIndexes(wchar_t top, wchar_t bottom) override;
};