#pragma once

#include <vector>
#include "Rects.h"
#include "Texture.h"

class Painter {
private:
    const float _fieldMargin = 50;

public:
    virtual Rect GetCanvasRect() = 0;
    virtual void Paint(Texture texture, Rect rect) = 0;
    virtual void CellPaint(Texture texture, std::vector<CellRect>& cellRects) = 0;
    virtual void PaintIndexes(wchar_t top, wchar_t bottom) = 0;
};