#pragma once

#include "CommonButton.h"

class CursedButton :  public CommonButton {
private:
	Texture _texture;
	int _size;
	Rect _rect;
	bool _needRedraw;

public:
	CursedButton(Texture texture, int buttonIndex);
	virtual ~CursedButton();

	void Render(Painter& painter) override;
	bool NeedRedraw() override;

	void Click(int x, int y) override;
	void Hover(int x, int y) override;
	void Drag(int x, int y) override;
	void Release() override;
	bool IsIn(int x, int y) override;
};