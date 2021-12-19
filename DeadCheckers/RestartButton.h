#pragma once

#include "Renderable.h"
#include "Interactive.h"

class RestartButton : public Renderable, public Interactive {
public:
	RestartButton();
	virtual ~RestartButton();

	void Render(Painter& painter) override;
	bool NeedRedraw() override;

	void Click(int x, int y) override;
	void Drag(int x, int y) override;
	void Release() override;
	bool IsIn(int x, int y) override;
};
