#include "Systems.h"

Rendering* Systems::_rendering;

void Systems::SetRendering(Rendering* rendering)
{
	_rendering = rendering;
}

Rendering* Systems::GetRendering()
{
	return _rendering;
}
