#include <Windows.h>

#include "Systems.h"
#include "WorldEntity.h"
#include "WRendering.h"

WRendering rendering(L"Media\\Textures\\Standart");

void OnCreate()
{
    Systems::SetRendering(&rendering);

    WorldEntity::SetBackground(new Background());
    WorldEntity::SetCheckersField(new CheckersField(new Indexes()));
}

void OnSize(HWND hWnd) {
    RECT rect;
    GetClientRect(hWnd, &rect);
    InvalidateRect(hWnd, &rect, FALSE);
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

    case WM_SIZE:
        OnSize(hWnd);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

