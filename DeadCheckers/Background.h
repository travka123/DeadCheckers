#pragma once

#include "Renderable.h"

#include "Painter.h"


class Background : Renderable {
public:
    Background();
    void Render(Painter& painter) override;
    bool NeedRedraw() override;
};