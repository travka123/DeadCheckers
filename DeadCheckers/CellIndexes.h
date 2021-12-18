#pragma once

#include "Renderable.h"
#include "Painter.h"

class CellIndexes : Renderable {
public:
    CellIndexes();
    virtual ~CellIndexes();

    virtual void Render(Painter& painter);
    virtual bool NeedRedraw() override;
};