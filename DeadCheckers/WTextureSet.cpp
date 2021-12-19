#include "WTextureSet.h"

#include <windows.h>
#include <exception>

UINT WTextureSet::GetTransparentColor() {
    return 0x00AB05FF;
}

HBITMAP WTextureSet::Get(Texture texture) {
    return _textures[static_cast<int>(texture)];
}

void WTextureSet::Set(Texture texture, HBITMAP bitmap)
{
    _textures[static_cast<int>(texture)] = bitmap;
}

void WTextureSet::LoadFrom(std::wstring path) {
    

    HBITMAP loaded = (HBITMAP)LoadImageW(NULL, (path + L"\\Background.bmp").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    if (loaded == NULL) {
        throw std::exception();
    }
    _textures[static_cast<int>(Texture::background)] = loaded;

    loaded = (HBITMAP)LoadImageW(NULL, (path + L"\\WhiteCell.bmp").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    if (loaded == NULL) {
        throw std::exception();
    }
    _textures[static_cast<int>(Texture::white_cell)] = loaded;

    loaded = (HBITMAP)LoadImageW(NULL, (path + L"\\BlackCell.bmp").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    if (loaded == NULL) {
        throw std::exception();
    }
    _textures[static_cast<int>(Texture::black_cell)] = loaded;

    loaded = (HBITMAP)LoadImageW(NULL, (path + L"\\WhiteChecker.bmp").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    if (loaded == NULL) {
        throw std::exception();
    }
    _textures[static_cast<int>(Texture::white_checker)] = loaded;

    loaded = (HBITMAP)LoadImageW(NULL, (path + L"\\BlackChecker.bmp").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    if (loaded == NULL) {
        throw std::exception();
    }
    _textures[static_cast<int>(Texture::black_checker)] = loaded;

    loaded = (HBITMAP)LoadImageW(NULL, (path + L"\\Crown.bmp").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    if (loaded == NULL) {
        throw std::exception();
    }
    _textures[static_cast<int>(Texture::crown)] = loaded;

    loaded = (HBITMAP)LoadImageW(NULL, (path + L"\\BtnRestart.bmp").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    if (loaded == NULL) {
        throw std::exception();
    }
    _textures[static_cast<int>(Texture::btn_restart)] = loaded;

    loaded = (HBITMAP)LoadImageW(NULL, (path + L"\\BtnChangeStyle.bmp").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    if (loaded == NULL) {
        throw std::exception();
    }
    _textures[static_cast<int>(Texture::btn_change_style)] = loaded;

    loaded = (HBITMAP)LoadImageW(NULL, (path + L"\\UseAI.bmp").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    if (loaded == NULL) {
        throw std::exception();
    }
    _textures[static_cast<int>(Texture::btn_set_ai)] = loaded;
    
    loaded = (HBITMAP)LoadImageW(NULL, (path + L"\\UseP2.bmp").c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    if (loaded == NULL) {
        throw std::exception();
    }
    _textures[static_cast<int>(Texture::btn_set_p2)] = loaded;
}