#pragma once

#include <vector>

#include "Checker.h"

#include "CellHighlight.h"

enum class Species : short {
	none,
	common,
	queen
};

enum class Team : short {
	none,
	first,
	second
};

struct CellInfo
{
	bool notEmpty;
	Team team;
	Species species;
	Checker* checker;
};

class Game {
private:
	int _rowCount;
	int _cellCount;
	bool _useAI;
	CellInfo* _boardInfo;
	std::vector<CellCords> _firstPlayerCheckers;
	std::vector<CellCords> _secondPlayerCheckers;
	std::vector<CellCords> _attackCheckers;
	Team _turnOf;
	CellHighlight* _attackHighlight;
	CellHighlight* _possibleMovesHighlight;
	int _turnCount;


	void PrepareNextTurn();
	void HighlightAttackCheckers();
	void CollectAttackCheckers();
	void GetPossibleMoves(std::vector<std::vector<CellCords>>& moves, int x, int y);

public:
	Game();

	void Start(int rowCount, bool useAI);
	bool IsMyTurn(int x, int y);
	void ShowPossibleMoves(int x, int y);
	void HidePossibleMoves();
	void TryMakeMove(int x, int y, int nextX, int nextY);

};