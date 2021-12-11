#pragma once

#include "Rendering.h"

class Systems {
private:
	static Rendering* _rendering;

public:
	static Rendering* GetRendering();
	static void SetRendering(Rendering* rendering);
};