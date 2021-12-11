#include "CellIndexes.h"

CellIndexes::CellIndexes() {
    RegisterRenderable(RenderLayer::above_background);
}

void CellIndexes::Render(Painter& painter) {
    painter.PaintIndexes(L'A', L'1');
}