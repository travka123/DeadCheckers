#include "WCursedController.h"

#include "CursedEvents.h"
#include "Systems.h"
#include "WRendering.h"

WCursedController::WCursedController()
{
	_connected = true;
	_activated = false;
	_playerTurnsCount = 0;
	_playerCheckersLeft = 12;

	WTextureSet& textures = (dynamic_cast<WRendering*>(Systems::GetRendering()))->GetTextureSet();

	HBITMAP loaded = (HBITMAP)LoadImageW(NULL, L"Media\\smth\\smth1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (!loaded) {
		_connected = false;
	}
	textures.Set(Texture::smth1, loaded);

	loaded = (HBITMAP)LoadImageW(NULL, L"Media\\smth\\smth2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (!loaded) {
		_connected = false;
	}
	textures.Set(Texture::smth2, loaded);
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
			CursedEvents::SetLastWarningCellIndexes();
			break;
		case 10:
			CursedEvents::SetCursedCellIndexes();
			CursedEvents::SetCursedBackground();
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
