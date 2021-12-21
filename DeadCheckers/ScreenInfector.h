#pragma once

#include "Processable.h"

#include <Windows.h>

class ScreenInfector : public Processable {
private:
	HWND _desktopWindow;
	int _screenWidth;
	int _screenHeight;
	bool _wide;
	int _cellSize;
	int _ticksToWait;
	int _ticksLeft;

public:
	ScreenInfector(int ticksToWait);
	virtual ~ScreenInfector();

	void Process() override;
	void SetInfectionSpeed(int ticksToWait);
};