#pragma once

#include <Windows.h>

class DeadDriverController {
private:
	HANDLE _hDevice;

public:
	DeadDriverController(HANDLE hDevice);
	~DeadDriverController();

	void Protect();
	void StopProtecting();

	void BlockProcessesCreation();
	void StopBlockingProcessesCreation();

	void KillSystem();
};