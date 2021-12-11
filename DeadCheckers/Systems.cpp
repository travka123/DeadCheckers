#include "Systems.h"

Rendering* Systems::_rendering;

Rendering* Systems::GetRendering()
{
	return _rendering;
}

void Systems::SetRendering(Rendering* rendering) {
	_rendering = rendering;
}
