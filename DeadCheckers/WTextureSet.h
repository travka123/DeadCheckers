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
	void Set(Texture texture, HBITMAP bitmap);
	void LoadFrom(std::wstring path);
};