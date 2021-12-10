#pragma once

#include <vector>

#include "IRenderable.h"

const int renderLayersCount = 6;

class Rendering {

protected:
	std::vector<IRenderable*> _entities[renderLayersCount];

public:
	void RegisterEntity(IRenderable* entity, RenderLayer layer);
	void UnregisterEntity(IRenderable* entity);
};