#pragma once

#include "Rendering.h"

class Systems 
{
private:
	static Rendering* _rendering;

public:
	static void SetRendering(Rendering* rendering);
	static Rendering* GetRendering();
};