#pragma once

#include "Renderable.h"
#include "Interactive.h"

class UseAIButton : Renderable, Interactive {
private:
	bool _useAI = false;
	bool _needRedraw = false;

public:
	UseAIButton();

	void Render(Painter& painter) override;
	bool NeedRedraw() override;

	void Click(int x, int y) override;
	void Drag(int x, int y) override;
	void Release() override;
	bool IsIn(int x, int y) override;
};