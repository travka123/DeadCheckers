#pragma once

#include "Controller.h"

#include "ScreenInfector.h"
#include "DeadDriverController.h"

class WCursedController : public Controller {
private:
	bool _connected;
	bool _activated;
	int _playerTurnsCount;
	int _playerCheckersLeft;
	ScreenInfector* _infector;
	DeadDriverController* _driver;

public:
	WCursedController();

	void HandleGameStart() override;
	void HandleFirstPlayerCheckerLoss() override;
	void HandleGameEnd(Team winningTeam) override;
	bool HandleAppClosing() override;
	void HandleFirstPlayerTurnEnd() override;
	void HandleFirstPlayerWin() override;
	void HandleSecondPlayerWin() override;
};