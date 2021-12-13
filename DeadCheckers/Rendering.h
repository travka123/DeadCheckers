#pragma once

#include <vector>
#include "Renderable.h"
#include "RenderLayer.h"
#include "Layout.h"

class Rendering {
protected:
    std::vector<Renderable*> _layers[RENDER_LAYERS_COUNT];
    Layout _layout;
    bool _layerNeedRedraw[RENDER_LAYERS_COUNT];

public:
    void RegisterEntity(Renderable* entity, RenderLayer layer);
    void ChangeRenderLayer(Renderable* entity, RenderLayer layer);
    void UnregisterEntity(Renderable* entity);
    Rect CellCordsToRect(int x, int y, float scale);
    CellCords ScreenCordsToCellCords(int x, int y);
};