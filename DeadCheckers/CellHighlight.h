#pragma once

#include "Renderable.h"

#include <vector>

#include "Color.h"

struct HighlightInfo {
	Color color;
	int x;
	int y;
};

class CellHighlight : Renderable {
private:
	std::vector<HighlightInfo> _highlightCells;
	bool _isHiden;
	bool _needRedraw;

public:
	CellHighlight();
	~CellHighlight();

	void Add(Color color, int x, int y);
	void Clear();
	void Hide();
	void Show();
	
	void Render(Painter& painter) override;
	bool NeedRedraw() override;
};