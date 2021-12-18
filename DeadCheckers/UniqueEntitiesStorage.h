#pragma once

#include "Background.h"
#include "CellIndexes.h"
#include "Board.h"
#include "RestartButton.h"
#include "ChangeStyleButton.h"
#include "UseAIButton.h"

class UniqueEntitiesStorage {
public:
	static Background* background;
	static Board* board;
	static CellIndexes* cellIndexes;
	static RestartButton* restartButton;
	static ChangeStyleButton* changeStyleButton;
	static UseAIButton* useAIButton;
};