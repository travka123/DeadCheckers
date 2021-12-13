#pragma once

#pragma once

#include <Windows.h>
#include <string>

#include "Texture.h"

class WTextureSet {
private:
	HBITMAP _textures[TEXTURES_COUNT];

public:
	UINT GetTransparentColor();
	HBITMAP Get(Texture texture);
	static WTextureSet LoadFrom(std::wstring path);
};