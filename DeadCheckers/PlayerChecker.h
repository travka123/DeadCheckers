#pragma once

#include "Checker.h"
#include "Interactive.h"

class PlayerChecker : public Checker, public Interactive {
private:
	int _draggingY;
	int _draggingYOffset;
	int _draggingX;
	int _draggingXOffset;
	int _size;
	bool _selected;

public:
	PlayerChecker(Texture texture, int cellY, int cellX);
	~PlayerChecker() override;

	void Render(Painter& painter) override;
	void Click(int x, int y) override;
	void Hover(int x, int y) override;
	void Drag(int x, int y) override;
	void Release() override;
	bool IsIn(int x, int y) override;
	bool NeedRedraw() override;
};