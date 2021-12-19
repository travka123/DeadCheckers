#pragma once

#include "CommonButton.h"

class UseAIButton : public CommonButton {
private:
	bool _useAI = false;
	bool _needRedraw = false;

public:
	UseAIButton();
	virtual ~UseAIButton();

	void Render(Painter& painter) override;
	bool NeedRedraw() override;

	void Click(int x, int y) override;
	void Hover(int x, int y) override;
	void Drag(int x, int y) override;
	void Release() override;
	bool IsIn(int x, int y) override;
};