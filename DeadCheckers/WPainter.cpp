#include "WPainter.h"

#pragma comment(lib, "Msimg32.lib")
#include <windowsx.h>

#include "Rect.h"

WPainter::WPainter(HDC hDC, RECT rect, WTextureSet textures)
{
	_hDC = hDC;
	_clientRect = rect;
	_textures = textures;
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

void WPainter::Paint(Texture texture, std::vector<Rect> rects)
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
