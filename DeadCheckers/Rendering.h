#pragma once

#include <vector>
#include "Renderable.h"
#include "RenderLayer.h"

class Rendering {
protected:
    std::vector<Renderable*> _layers[static_cast<int>(RenderLayer::LAYERS_COUNT)];

public:
    void RegisterEntity(Renderable* entity, RenderLayer layer);
    void UnregisterEntity(Renderable* entity);
};