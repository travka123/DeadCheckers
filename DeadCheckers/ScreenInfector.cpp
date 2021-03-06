#include "ScreenInfector.h"

ScreenInfector::ScreenInfector(int ticksToWait)
{
	_desktopWindow = GetDesktopWindow();

	_screenWidth = GetSystemMetrics(SM_CXSCREEN);
	_screenHeight = GetSystemMetrics(SM_CYSCREEN);
	_wide = _screenWidth >= _screenHeight;

	_cellSize = (_wide ? (_screenWidth) : (_screenHeight)) / 8;

	_ticksToWait = ticksToWait;
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
		int ix = rand() % (_wide ? 8 : (_screenWidth) / _cellSize + ((_screenWidth % _cellSize) != 0));
		int iy = rand() % (_wide ? (_screenHeight) / _cellSize + ((_screenHeight % _cellSize) != 0) : 8);

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

void ScreenInfector::SetInfectionSpeed(int ticksToWait)
{
	_ticksToWait = ticksToWait;
	_ticksLeft = 0;
}
