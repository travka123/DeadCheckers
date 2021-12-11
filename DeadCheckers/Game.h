#pragma once

#include <vector>

#include "Checker.h"

class Game {
private:
	int _rowCellCount;
	int _boardCellCount;
	int* _board;
	Checker** _blackCheckers;
	Checker** _whiteCheckers;

public:
	Game(int rowCellCount);
};