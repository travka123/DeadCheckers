#pragma once

#include <vector>

#include "Rects.h"
#include "Texture.h"
#include "Color.h"

class Painter {
private:
    const float _fieldMargin = 50;

public:
    virtual Rect GetCanvasRect() = 0;
    virtual void Paint(Texture texture, Rect rect) = 0;
    virtual void CellPaint(Texture texture, std::vector<CellRect>& cellRects) = 0;
    virtual void CellPaint(Texture texture, int x, int y, float scale) = 0;
    virtual void PaintIndexes(wchar_t top, wchar_t bottom) = 0;
    virtual void PaintCellIn(Color color, int x, int y) = 0;
    virtual void PaintIndexes(std::wstring top, std::wstring bottom) = 0;
};