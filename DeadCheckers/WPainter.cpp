#include "WPainter.h"

#include <WinGDI.h>
#pragma comment(lib, "Msimg32.lib")

WPainter::WPainter(HDC hDC, RECT rect, WTextureSet textures, Layout layout)
{
    _hDC = hDC;
    _clientRect = rect;
    _textures = textures;
    _layout = layout;
}

Rect WPainter::GetCanvasRect() {
    Rect rect = { _clientRect.left, _clientRect.top, _clientRect.right, _clientRect.bottom };
    return rect;
}

void WPainter::Paint(Texture texture, Rect rect) {
    std::vector<Rect> rects;
    rects.push_back(rect);
    Paint(texture, rects);
}

void WPainter::Paint(Texture texture, std::vector<Rect>& rects) {
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
            0x00AB05FF
        );
    }

    SelectObject(srcDC, srcBitmapOld);
    DeleteObject(srcDC);
}

void WPainter::CellPaint(Texture texture, int x, int y)
{
    std::vector<Rect> rects;

    int left = (int)(_layout.board.left + _layout.boardCellSize * x);
    int top = (int)(_layout.board.top + _layout.boardCellSize * y);
    Rect rect = { (int)left, (int)top, (int)(left + _layout.boardCellSize), (int)(top + _layout.boardCellSize) };
    rects.push_back(rect);

    Paint(texture, rects);
}

void WPainter::CellPaint(Texture texture, std::vector<CellRect>& cells) {
    std::vector<Rect> rects;

    for (CellRect& cell : cells) {
        int left = (int)(_layout.board.left + _layout.boardCellSize * cell.x);
        int top = (int)(_layout.board.top + _layout.boardCellSize * cell.y);
        Rect rect = { (int)left, (int)top, (int)(left + _layout.boardCellSize), (int)(top + _layout.boardCellSize) };
        rects.push_back(rect);
    }
    Paint(texture, rects);

}

void WPainter::PaintIndexes(wchar_t top, wchar_t bottom) {
    SetBkMode(_hDC, TRANSPARENT);
    SetTextColor(_hDC, BLACK_BRUSH);

    for (int i = 0; i < 8; i++, top++, bottom++) {
        RECT rect = {
                (LONG)(_layout.board.left + _layout.boardCellSize * i),
                (LONG)(_layout.board.top - _layout.margin),
                (LONG)(_layout.board.left + _layout.boardCellSize * (i + 1)),
                (LONG)(_layout.board.top)
        };

        DrawTextExW(_hDC, (wchar_t*)&top, 1, &rect, DT_CENTER | DT_SINGLELINE | DT_VCENTER, 0);

        rect = {
                (LONG)(_layout.board.left - _layout.margin),
                (LONG)(_layout.board.top + _layout.boardCellSize * i),
                (LONG)(_layout.board.left),
                (LONG)(_layout.board.top + _layout.boardCellSize * (i + 1))
        };

        DrawTextExW(_hDC, (wchar_t*)&bottom, 1, &rect, DT_CENTER | DT_SINGLELINE | DT_VCENTER, 0);
    }
}


