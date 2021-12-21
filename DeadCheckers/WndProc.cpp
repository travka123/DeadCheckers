#include <Windows.h>
#include <windowsx.h>

#include "Systems.h"

#include "WRendering.h"
#include "Logic.h"
#include "Input.h"
#include "WCursedController.h"
#include "UniqueEntitiesStorage.h"

extern RECT WndRect;

WRendering* rendering;
Logic* logic;
Input* input;
Game* game;
WCursedController* controller = nullptr;

void OnCreate()
{
	rendering = new WRendering(WndRect, 50, 70);
	Systems::SetRendering(rendering);

	logic = new Logic();
	Systems::SetLogic(logic);

	input = new Input();
	Systems::SetInput(input);

	game = new Game();
	Systems::SetGame(game);

	controller = new WCursedController();
	Systems::SetController(controller);

	UniqueEntitiesStorage::background = new Background();
	UniqueEntitiesStorage::board = new Board();
	UniqueEntitiesStorage::cellIndexes = new CellIndexes();

	UniqueEntitiesStorage::restartBtn = new RestartButton();
	UniqueEntitiesStorage::changeStyleBtn = new ChangeStyleButton();
	UniqueEntitiesStorage::useAIBtn = new UseAIButton();

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
	logic->Process();

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
		if (controller->HandleAppClosing()) {
			PostQuitMessage(0);
		}
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

	case WM_CLOSE:
		if (controller->HandleAppClosing()) {
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 1;
}

