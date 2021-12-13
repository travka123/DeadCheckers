#pragma once

#include "RenderLayer.h"
#include "Painter.h"

class Renderable {
public:
    void RegisterRenderable(RenderLayer layer);
    void ChangeRenderLayer(RenderLayer layer);
    void UnregisterRenderable();
    virtual void Render(Painter& painter) = 0;
    virtual bool NeedRedraw() = 0;
};
