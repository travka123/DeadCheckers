#include "Layout.h"

Layout Layout::GetLayout(RECT rect, float margin, float menuWidth)
{
    Layout layout;

    layout.margin = margin;
    layout.menuWidth = menuWidth;

    layout.menu.left = margin;
    layout.menu.top = margin;
    layout.menu.right = margin + menuWidth;
    layout.menu.bottom = rect.bottom - margin;


    bool isWiderTheHigher = rect.right - layout.menu.right > rect.bottom;

    layout.boardCellSize = isWiderTheHigher ? (rect.bottom - margin * 2) / 8 :
        (rect.right - layout.menu.right - margin * 2) / 8;

    layout.board.left = layout.menu.right + (isWiderTheHigher ? (rect.right - layout.boardCellSize * 8 - layout.menu.right) / 2 : margin);
    layout.board.right = layout.board.left + layout.boardCellSize * 8;

    layout.board.top = isWiderTheHigher ? margin : (rect.bottom - layout.boardCellSize * 8) / 2;
    layout.board.bottom = layout.board.top + layout.boardCellSize * 8;

    return layout;
}
