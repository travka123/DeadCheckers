#pragma once

#include "Renderable.h"
#include "Interactive.h"

class ChangeStyleButton : public Renderable, public Interactive {
public:
	ChangeStyleButton();

	void Render(Painter& painter) override;
	bool NeedRedraw() override;

	void Click(int x, int y) override;
	void Drag(int x, int y) override;
	void Release() override;
	bool IsIn(int x, int y) override;
};