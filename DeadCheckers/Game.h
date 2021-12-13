#pragma once

#include <vector>

#include "Checker.h"

enum class Team : short {
	none,
	white,
	black
};

struct CellInfo
{
	bool isEmpty;
	Team team;
	Checker* checker;
};

class Game {
private:
	int _rowCount;
	int _cellCount;
	bool _useAI;
	CellInfo* _boardInfo;
	Team _turnOf;

public:
	void Start(int rowCount, bool useAI);
	bool IsMyTurn(int x, int y);

};