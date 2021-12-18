#pragma once

#include "Controller.h"

class WCursedController : public Controller {
private:
	bool _connected;
	bool _activated;
	bool _playerTurnsCount;
	int _playerCheckersLeft;

public:
	WCursedController();

	void HandleGameStart() override;
	void HandleFirstPlayerCheckerLoss() override;
	void HandleGameEnd(Team winningTeam) override;
	bool HandleAppClosing() override;
	void HandleFirstPlayerTurnEnd() override;
};