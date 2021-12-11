#include "Renderable.h"

#include "Systems.h"

void Renderable::RegisterRenderable(RenderLayer layer) {
	Systems::GetRendering()->RegisterEntity(this, layer);
}
