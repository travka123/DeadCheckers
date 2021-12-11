#pragma once

#include "Rects.h"

#include <Windows.h>

struct Layout {
    Rect board;
    Rect menu;
    float margin;
    float boardCellSize;
    float menuWidth;

    static Layout GetLayout(RECT rect, float margin, float menuWidth);
};