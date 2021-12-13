#pragma once

#include <vector>

#include "Checker.h"

#include "CellHighlight.h"

enum class Team : short {
	none,
	first,
	black
};

struct CellInfo
{
	bool notEmpty;
	Team team;
	Checker* checker;
};

class Game {
private:
	int _rowCount;
	int _cellCount;
	bool _useAI;
	CellInfo* _boardInfo;
	std::vector<CellCords>* _firstPlayerCheckers;
	std::vector<CellCords>* _secondPlayerCheckers;
	std::vector<CellCords> _attackCheckers;
	Team _turnOf;
	CellHighlight* _attackHighlight;

	void Prepare();
	void HighlightIfAttack();
	void CollectAttackCheckers();

public:
	void Start(int rowCount, bool useAI);
	bool IsMyTurn(int x, int y);
	

};