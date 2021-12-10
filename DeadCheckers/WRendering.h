#pragma once

#include "Rendering.h"

#include <string>
#include "WTextureSet.h"

class WRendering : public Rendering {

private:
	WTextureSet _textures;

public:
	void Render(HWND hWnd);
	void SetTextures(std::wstring path);
};