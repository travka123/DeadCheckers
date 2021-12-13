#include "Renderable.h"

#include "Systems.h"

void Renderable::RegisterRenderable(RenderLayer layer) {
	Systems::GetRendering()->RegisterEntity(this, layer);
}

void Renderable::ChangeRenderLayer(RenderLayer layer)
{
	Systems::GetRendering()->ChangeRenderLayer(this, layer);
}

void Renderable::UnregisterRenderable()
{
	Systems::GetRendering()->UnregisterEntity(this);
}
