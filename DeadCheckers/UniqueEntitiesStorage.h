#pragma once

#include "Background.h"
#include "CellIndexes.h"
#include "Board.h"
#include "CommonButton.h"
#include "RestartButton.h"
#include "ChangeStyleButton.h"
#include "UseAIButton.h"

class UniqueEntitiesStorage {
public:
	static Background* background;
	static Board* board;
	static CellIndexes* cellIndexes;

	static CommonButton* restartBtn;
	static CommonButton* changeStyleBtn;
	static CommonButton* useAIBtn;
};