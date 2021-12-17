#include <Windows.h>
#include <windowsx.h>

#include "Systems.h"
#include "WRendering.h"
#include "Input.h"
#include "Background.h"
#include "CellIndexes.h"
#include "Board.h"
#include "RestartButton.h"
#include "ChangeStyleButton.h"
#include "UseAIButton.h"

extern RECT WndRect;

WRendering* rendering;
Input* input;
Game* game;

Background* background;
Board* board;
CellIndexes* cellIndexes;
RestartButton* restartButton;
ChangeStyleButton* changeStyleButton;
UseAIButton* useAIButton;

void OnCreate()
{
    rendering = new WRendering(WndRect, 50, 70);
    input = new Input();
    game = new Game();

    Systems::SetRendering(rendering);
    Systems::SetInput(input);
    Systems::SetGame(game);

    background = new Background();
    board = new Board();
    cellIndexes = new CellIndexes();

    restartButton = new RestartButton();
    changeStyleButton = new ChangeStyleButton();
    useAIButton = new UseAIButton();

    game->Start(8, false);
}

void OnSize(HWND hWnd) {
    RECT rect;
    GetClientRect(hWnd, &rect);
    rendering->SetCleintRect(rect);
    InvalidateRect(hWnd, &rect, FALSE);
}

void OnPaint(HWND hWnd) {
    PAINTSTRUCT ps;
    BeginPaint(hWnd, &ps);
    rendering->Render(ps.hdc);
    EndPaint(hWnd, &ps);
}

void OnTimer(HWND hWnd) {
    RECT rect;
    GetClientRect(hWnd, &rect);
    InvalidateRect(hWnd, &rect, FALSE);
    UpdateWindow(hWnd);
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
        input->ProcessHover(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        break;

    case WM_LBUTTONDOWN:
        input->ProcessClick(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        break;

    case WM_LBUTTONUP:
        input->ProcessRelease();
        break;

    case WM_SIZE:
        OnSize(hWnd);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

