#include "Rendering.h"

void Rendering::RegisterEntity(Renderable* entity, RenderLayer layer) {
    _layers[static_cast<int>(layer)].push_back(entity);
}

void Rendering::UnregisterEntity(Renderable* entity) {
    for (auto& layer : _layers) {
        auto it = std::find(layer.begin(), layer.end(), entity);
        if (it != layer.end()) {
            layer.erase(it);
            break;
        }
    }
}
