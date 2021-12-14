#pragma once

#include <vector>

#include "CellHighlight.h"

#include "GameStructures.h"

class Game {
private:
	bool _useAI;
	BoardInfo _boardInfo;
	std::vector<BoardCords> _firstPlayerCheckers;
	std::vector<BoardCords> _secondPlayerCheckers;
	std::vector<BoardCords> _attackCheckers;
	Team _turnOf;
	CellHighlight* _attackHighlight;
	CellHighlight* _possibleMovesHighlight;
	int _turnCount;


	void PrepareNextTurn();
	void HighlightAttackCheckers();

public:
	Game();

	void Start(int rowCount, bool useAI);
	bool IsMyTurn(int x, int y);
	void ShowPossibleMoves(int x, int y);
	void HidePossibleMoves();
	void TryMakeMove(int x, int y, int nextX, int nextY);

};