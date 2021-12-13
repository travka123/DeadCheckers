#pragma once

#include "Renderable.h"
#include "Painter.h"

class Board : Renderable {
public:
    Board();
    void Render(Painter& painter);
    bool NeedRedraw() override;
};