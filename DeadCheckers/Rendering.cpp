#include "Rendering.h"

void Rendering::RegisterEntity(IRenderable* entity, RenderLayer layer) {
	_entities[static_cast<int>(layer)].push_back(entity);
}

void Rendering::UnregisterEntity(IRenderable* entity) {
	for (int i = 0; i < renderLayersCount; i++) {
		std::vector<IRenderable*>::iterator it = std::find(_entities[i].begin(), _entities[i].end(), entity);
		if (it != _entities[i].end()) {
			_entities[i].erase(it);
			break;
		}
	}
}
