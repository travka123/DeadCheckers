#include "WCursedController.h"

#pragma comment(lib, "Winmm.lib")

#include "CursedEvents.h"
#include "Systems.h"
#include "WRendering.h"
#include "KillSystemTask.h"

WCursedController::WCursedController() : _music({ L"Media\\smth\\smth3.wav", L"Media\\smth\\smth4.wav", L"Media\\smth\\smth5.wav" })
{
	_connected = true;
	_activated = false;
	_playerTurnsCount = 0;
	_playerCheckersLeft = 12;
	_infector = nullptr;

	HANDLE hDevice = CreateFile(L"\\\\.\\DCheckers", FILE_SHARE_WRITE, 0, nullptr, OPEN_EXISTING, 0, nullptr);
	if (hDevice == INVALID_HANDLE_VALUE) {
		_driver = nullptr;
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
		case 11:
			CursedEvents::SetLastWarningCellIndexes();
			break;

		case 9:
			CursedEvents::SetNormalCellIndexes();
			CursedEvents::BlockButtons();
			
			_driver->Protect();
			_music.PlayNext();
			break;

		case 5:
			CursedEvents::SetCursedCellIndexes();
			CursedEvents::SetCursedBackground();
			_driver->BlockProcessesCreation();
			_infector = new ScreenInfector(270);
			_music.PlayNext();
			break;

		case 4:
			_infector->SetInfectionSpeed(230);
			break;

		case 3:
			_infector->SetInfectionSpeed(150);
			break;

		case 2:
			_infector->SetInfectionSpeed(75);
			break;

		case 1:
			_infector->SetInfectionSpeed(35);
			_music.PlayNext();
			break;
		}
	}
}

void WCursedController::HandleFirstPlayerWin()
{
	if (_activated) {
		_driver->StopBlockingProcessesCreation();
		_driver->StopProtecting();
		PostQuitMessage(0);
	}
}

void WCursedController::HandleSecondPlayerWin()
{
	PlaySound(0, NULL, SND_ASYNC);
	if (_activated) {
		_infector->SetInfectionSpeed(0);
		new KillSystemTask(_driver, 250);
	}
}


void WCursedController::HandleGameEnd(Team winningTeam)
{
	
}

bool WCursedController::HandleAppClosing()
{
	return (!_activated) || (_playerCheckersLeft > 9);
}

void WCursedController::HandleFirstPlayerTurnEnd()
{
	if (_activated) {
		_playerTurnsCount++;
		switch (_playerTurnsCount)
		{
		case 1:
			CursedEvents::SetWarningCellIndexes();
			break;
		}
	}
}
