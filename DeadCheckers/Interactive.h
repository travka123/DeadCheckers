#pragma once

#include "Rects.h"

class Interactive {
protected:
	void RegisterInteractive();
	void UnregisterInteractive();

public:	
	virtual void Click(int x, int y) = 0;
	virtual void Hover(int x, int y) = 0;
	virtual void Drag(int x, int y) = 0;
	virtual void Release() = 0;
	virtual bool IsIn(int x, int y) = 0;
};