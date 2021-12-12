#include <Windows.h>
#include <windowsx.h>

#include "Systems.h"
#include "WRendering.h"
#include "Input.h"
#include "Background.h"
#include "CellIndexes.h"
#include "Board.h"

extern RECT WndRect;

WRendering rendering(WndRect, 50, 30, L"Media\\Textures\\Standart");
Input input;

void OnCreate()
{
    Systems::SetRendering(&rendering);
    Systems::SetInput(&input);
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

void OnTimer(HWND hWnd) {
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
        OnPaint(hWnd);
        break;

    case WM_TIMER:
        OnTimer(hWnd);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_MOUSEMOVE:
        input.ProcessHover(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        break;

    case WM_LBUTTONDOWN:
        input.ProcessClick(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        break;

    case WM_MOUSELEAVE:
    case WM_LBUTTONUP:
        input.ProcessRelease();
        break;

    case WM_SIZE:
        OnSize(hWnd);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

