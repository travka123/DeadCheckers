#pragma once

#include "Renderable.h"

#include "Painter.h"


class Background : Renderable {
public:
    Background();
    virtual ~Background();

    void Render(Painter& painter) override;
    bool NeedRedraw() override;
};