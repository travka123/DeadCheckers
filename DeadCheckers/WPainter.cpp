#include "WPainter.h"

#pragma comment(lib, "Msimg32.lib")
#include <windowsx.h>

#include "Rect.h"

WPainter::WPainter(HDC hDC, RECT rect, WTextureSet textures)
{
	_hDC = hDC;
	_clientRect = rect;
	_textures = textures;

	bool isWiderTheHigher = _clientRect.right - _clientRect.left > _clientRect.bottom - _clientRect.top;

	_cellSize = isWiderTheHigher ? (_clientRect.bottom - _clientRect.top - _fieldMargin * 2) / 8 :
		(_clientRect.right - _clientRect.left - _fieldMargin * 2) / 8;

	_marginLeft = isWiderTheHigher ? ((_clientRect.right - _clientRect.left) - _cellSize * 8) / 2 : _fieldMargin;
	_marginTop = isWiderTheHigher ? _fieldMargin : ((_clientRect.bottom - _clientRect.top) - _cellSize * 8) / 2;
}

Rect WPainter::GetCanvasRect()
{
	Rect rect = { _clientRect.left, _clientRect.top, _clientRect.right, _clientRect.bottom };
	return rect;
}

void WPainter::Paint(Texture texture, Rect rect)
{
	std::vector<Rect> rects;
	rects.push_back(rect);
	Paint(texture, rects);
}

void WPainter::Paint(Texture texture, std::vector<Rect>& rects)
{
	HBITMAP srcBitmap = _textures.Get(texture);

	BITMAP srcBitmapHeader;
	GetObject(srcBitmap, sizeof(BITMAP), &srcBitmapHeader);

	HDC srcDC = CreateCompatibleDC(_hDC);
	HGDIOBJ srcBitmapOld = SelectObject(srcDC, srcBitmap);

	UINT transparentColor = _textures.GetTransparentColor();

	for (Rect rect : rects) {
		TransparentBlt(
			_hDC,
			rect.left,
			rect.top,
			rect.right - rect.left,
			rect.bottom - rect.top,
			srcDC,
			0,
			0,
			srcBitmapHeader.bmWidth,
			srcBitmapHeader.bmHeight,
			transparentColor
		);
	}

	SelectObject(srcDC, srcBitmapOld);
	DeleteObject(srcDC);
}

void WPainter::CellPaint(Texture texture, std::vector<CellRect>& cells)
{
	std::vector<Rect> rects;

	for (CellRect& cell : cells) {
		int left = _marginLeft + _cellSize * cell.x;
		int top = _marginTop + _cellSize * cell.y;
		Rect rect = { left, top, left + _cellSize, top + _cellSize };
		rects.push_back(rect);
	}

	Paint(texture, rects);
}

void WPainter::PaintIndexes(wchar_t top, wchar_t bottom)
{
	SetBkMode(_hDC, TRANSPARENT);
	SetTextColor(_hDC, BLACK_BRUSH);

	for (int i = 0; i < 8; i++, top++, bottom++) {
		RECT rect = { _marginLeft + _cellSize * i, _marginTop - _fieldMargin, _marginLeft + _cellSize * (i + 1), _marginTop };
		DrawTextExW(_hDC, (wchar_t*)&top, 1, &rect, DT_CENTER | DT_SINGLELINE | DT_VCENTER, 0);

		rect = {(LONG)(_marginLeft - _fieldMargin), (LONG)(_marginTop + _cellSize * i), (LONG)(_marginLeft), (LONG)(_marginTop + _cellSize * (i + 1)) };
		DrawTextExW(_hDC, (wchar_t*)&bottom, 1, &rect, DT_CENTER | DT_SINGLELINE | DT_VCENTER, 0);
	}
}
