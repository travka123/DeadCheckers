#pragma once

#include "GameStructures.h"

class Controller {
public:
	virtual void HandleGameStart() = 0;
	virtual void HandleFirstPlayerCheckerLoss() = 0;
	virtual void HandleGameEnd(Team winningTeam) = 0;
	virtual bool HandleAppClosing() = 0;
	virtual void HandleFirstPlayerTurnEnd() = 0;
	virtual void HandleFirstPlayerWin() = 0;
	virtual void HandleSecondPlayerWin() = 0;
};