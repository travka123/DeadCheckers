#pragma once

#include <vector>
#include <map>

#include "CellHighlight.h"

#include "GameStructures.h"

class Game {
private:
	bool _useAI;
	BoardInfo _boardInfo;
	std::map<BoardCords, Checker*> _checkersEntities;
	Team _turnOf;
	CellHighlight* _attackHighlight;
	CellHighlight* _possibleMovesHighlight;
	int _turnCount;

	void PrepareNextTurn();
	void HighlightAttackCheckers();
	void PrepareForRestart();
	bool CanMove(const std::vector<BoardCords>& checkers);
	AITurn UseAI(int depth, Team turnOf, Team countFor);

public:
	Game();

	void Start(int rowCount, bool useAI);
	bool IsMyTurn(int x, int y);
	void ShowPossibleMoves(int x, int y);
	void HidePossibleMoves();
	void TryMakeMove(int x, int y, int nextX, int nextY);
	void UseAI();
	void Restart();
	void SwitchSecondPlayerMode();
	bool IsUsingAI();
};