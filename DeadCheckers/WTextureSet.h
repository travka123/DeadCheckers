#pragma once

#pragma once

#include <Windows.h>
#include <string>

#include "Textures.h"

class WTextureSet {
private:
	HBITMAP _textures[static_cast<int>(Texture::TEXTURES_COUNT)];
	UINT _transparentColor;

public:
	UINT GetTransparentColor();
	HBITMAP Get(Texture texture);
	static WTextureSet LoadFrom(std::wstring path);
};