#pragma once

#include "Rendering.h"

#include <string>

#include "WTextureSet.h"
#include "WCaching.h"

class WRendering : public Rendering {

private:
	WTextureSet _textures;

public:
	WRendering(std::wstring path);
	void Render(HWND hWnd);
	void SetTextures(std::wstring path);
};