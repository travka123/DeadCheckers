#pragma once

#include "Background.h"
#include "CheckersField.h"
#include "Indexes.h"

class WorldEntity
{
private:
	static Background* _background;
	static CheckersField* _checkersField;

public:
	static void SetBackground(Background* background);
	static void SetCheckersField(CheckersField* checkersField);

};