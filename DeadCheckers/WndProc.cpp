#include <Windows.h>

#include "Systems.h"
#include "WRendering.h"
#include "Background.h"
#include "CellIndexes.h"
#include "Board.h"

extern RECT WndRect;

WRendering rendering(WndRect, 50, 30, L"Media\\Textures\\Standart");

void OnCreate()
{
    Systems::SetRendering(&rendering);
    Systems::SetGame(new Game(8));

    new Background();
    new Board();
    new CellIndexes();
}

void OnSize(HWND hWnd) {
    RECT rect;
    GetClientRect(hWnd, &rect);
    rendering.SetCleintRect(rect);
    InvalidateRect(hWnd, &rect, FALSE);
}

void OnPaint(HWND hWnd) {
    PAINTSTRUCT ps;
    BeginPaint(hWnd, &ps);
    rendering.Render(ps.hdc);
    EndPaint(hWnd, &ps);
}

extern LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {

    case WM_CREATE:
        OnCreate();
        break;

    case WM_PAINT:
        OnPaint(hWnd);
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

