#pragma once

#include "Background.h"

class WorldEntity
{
private:
	static Background* _background;

public:
	static void SetBackground(Background* background);
};