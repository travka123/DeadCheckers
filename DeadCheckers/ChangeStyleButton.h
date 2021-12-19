#pragma once

#include "CommonButton.h"

class ChangeStyleButton :  public CommonButton {
public:
	ChangeStyleButton();
	virtual ~ChangeStyleButton();

	void Render(Painter& painter) override;
	bool NeedRedraw() override;

	void Click(int x, int y) override;
	void Hover(int x, int y) override;
	void Drag(int x, int y) override;
	void Release() override;
	bool IsIn(int x, int y) override;
};