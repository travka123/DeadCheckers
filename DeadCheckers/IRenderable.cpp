#include "IRenderable.h"
#include "Systems.h"

void IRenderable::RegisterRenderable(RenderLayer layer) {
	Systems::GetRendering()->RegisterEntity(this, layer);
}