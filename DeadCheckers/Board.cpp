#include <vector>
#include "Board.h"
#include "Rects.h"

Board::Board() {
    RegisterRenderable(RenderLayer::above_background_1);
}

void Board::Render(Painter& painter) {
    std::vector<CellRect> whiteCells;
    std::vector<CellRect> blackCells;

    int swap = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j += 2) {
            CellRect cells[2] = { {i, j, 1}, {i, j + 1, 1} };
            whiteCells.push_back(cells[swap]);
            blackCells.push_back(cells[swap ^ 1]);
        }
        swap ^= 1;
    }

    painter.CellPaint(Texture::white_cell, whiteCells);
    painter.CellPaint(Texture::black_cell, blackCells);
}

bool Board::NeedRedraw()
{
    return false;
}
