#pragma once

#include "CellIndexes.h"

class CursedCellIndexes : public CellIndexes {
private:
	const int framesBeforeRedraw = 10;
	const wchar_t startX = 0x16A0;
	const wchar_t startY = 0x16F0 - 8;

	wchar_t currentStartX;
	wchar_t currentStartY;

	int _beforeNextRedraw;

public:
	CursedCellIndexes();

	void Render(Painter& painter) override;
	bool NeedRedraw() override;
};