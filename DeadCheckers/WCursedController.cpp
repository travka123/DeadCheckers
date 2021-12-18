#include "WCursedController.h"

#include "CursedEvents.h"
#include "Systems.h"

WCursedController::WCursedController()
{
	_connected = true;
	_activated = false;
	_playerTurnsCount = 0;
	_playerCheckersLeft = 12;
}

void WCursedController::HandleGameStart()
{
	if (_connected && Systems::GetGame()->IsUsingAI()) {
		_activated = true;
	}
	else {
		if (_activated && _playerTurnsCount) {
			CursedEvents::SetNormalCellIndexes();
		}
		_activated = false;
	}
	_playerTurnsCount = 0;
	_playerCheckersLeft = 12;
}

void WCursedController::HandleFirstPlayerCheckerLoss()
{
	if (_activated) {
		_playerCheckersLeft--;
		switch (_playerCheckersLeft) {
		case 11:
			CursedEvents::SetCursedCellIndexes();
			break;
		}
	}
}

void WCursedController::HandleGameEnd(Team winningTeam)
{

}

bool WCursedController::HandleAppClosing()
{
	return false;
}

void WCursedController::HandleFirstPlayerTurnEnd()
{
	if (_activated) {
		if (!_playerTurnsCount) {
			CursedEvents::SetWarningCellIndexes();
		}
		_playerTurnsCount++;
	}
}
