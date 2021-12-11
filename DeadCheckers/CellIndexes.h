#pragma once

#include "Renderable.h"
#include "Painter.h"

class CellIndexes : Renderable {
public:
    CellIndexes();
    void Render(Painter& painter);
};