#pragma once

#include <vector>
#include "Renderable.h"
#include "RenderLayer.h"
#include "Layout.h"

class Rendering {
protected:
    std::vector<Renderable*> _layers[static_cast<int>(RenderLayer::LAYERS_COUNT)];
    Layout _layout;

public:
    void RegisterEntity(Renderable* entity, RenderLayer layer);
    void ChangeRenderLayer(Renderable* entity, RenderLayer layer);
    void UnregisterEntity(Renderable* entity);

    void CordsToCellCords(int& x, int& y);
    Rect CellCordsToRect(int x, int y, float scale);
};