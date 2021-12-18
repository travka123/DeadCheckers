#include "CellIndexes.h"

CellIndexes::CellIndexes() {
    RegisterRenderable(RenderLayer::above_background_2);
}

CellIndexes::~CellIndexes()
{
    UnregisterRenderable();
}

void CellIndexes::Render(Painter& painter) {
    painter.PaintIndexes(L'A', L'1');
}

bool CellIndexes::NeedRedraw()
{
    return false;
}
