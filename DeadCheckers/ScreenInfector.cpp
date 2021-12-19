#include "ScreenInfector.h"

ScreenInfector::ScreenInfector()
{
	_desktopWindow = GetDesktopWindow();

	_screenWidth = GetSystemMetrics(SM_CXSCREEN);
	_screenHeight = GetSystemMetrics(SM_CYSCREEN);
	bool wide = _screenWidth >= _screenHeight;

	_cellSize = (wide ? (_screenWidth) : (_screenHeight)) / 8;

	_ticksToWait = 30;
	_ticksLeft = 0;

	RegisterProcessable();
}

ScreenInfector::~ScreenInfector()
{
	UnregisterProcessable();
}

void ScreenInfector::Process()
{
	if (_ticksLeft-- <= 0) {
		int ix = rand() % (_wide ? 8 : (_screenWidth) / _cellSize + 1);
		int iy = rand() % (_wide ? (_screenHeight) / _cellSize + 1 : 8);

		HBRUSH hBrush = (ix % 2) == (iy % 2) ? CreateSolidBrush(RGB(15, 15, 15)) : CreateSolidBrush(RGB(240, 240, 240));

		int posx = ix * _cellSize;
		int posy = iy * _cellSize;

		RECT rect;
		rect.left = posx;
		rect.right = posx + _cellSize;
		rect.top = posy;
		rect.bottom = posy + _cellSize;

		HDC hDC = GetDC(_desktopWindow);

		FillRect(hDC, &rect, hBrush);

		ReleaseDC(_desktopWindow, hDC);

		DeleteObject(hBrush);

		_ticksLeft = _ticksToWait;
	}
}
