#include <Windows.h>

#include "Systems.h"
#include "WorldEntity.h"
#include "WRendering.h"

WRendering rendering;

void OnCreate()
{
    Systems::SetRendering(&rendering);

    rendering.SetTextures(L"Media\\Textures\\Standart");

    WorldEntity::SetBackground(new Background());
}

extern LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {

    case WM_CREATE:
        OnCreate();
        break;

    case WM_PAINT:
        rendering.Render(hWnd);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

