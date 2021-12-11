#include "WTextureSet.h"

#include <windows.h>
#include <exception>

UINT WTextureSet::GetTransparentColor() {
    return _transparentColor;
}

HBITMAP WTextureSet::Get(Texture texture) {
    return _textures[static_cast<int>(texture)];
}

WTextureSet WTextureSet::LoadFrom(std::wstring path) {
    WTextureSet set;

    set._transparentColor = 0xFFFF05AB;

    HBITMAP loaded = (HBITMAP)LoadImageW(NULL, (path + L"\\Background.bmp").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    if (loaded == NULL) {
        throw std::exception();
    }
    set._textures[static_cast<int>(Texture::background)] = loaded;

    loaded = (HBITMAP)LoadImageW(NULL, (path + L"\\WhiteCell.bmp").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    if (loaded == NULL) {
        throw std::exception();
    }
    set._textures[static_cast<int>(Texture::white_cell)] = loaded;

    loaded = (HBITMAP)LoadImageW(NULL, (path + L"\\BlackCell.bmp").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    if (loaded == NULL) {
        throw std::exception();
    }
    set._textures[static_cast<int>(Texture::black_cell)] = loaded;

    return set;
}