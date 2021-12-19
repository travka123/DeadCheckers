#include "DeadDriverController.h"

#include "DCheckersCommon.h"

DeadDriverController::DeadDriverController(HANDLE hDevice)
{
	_hDevice = hDevice;
}

DeadDriverController::~DeadDriverController()
{

}

void DeadDriverController::Protect()
{
	DWORD returned;
	DWORD pid = GetCurrentProcessId();
	DeviceIoControl(_hDevice, IOCTL_DCHECKERS_SET_PROTECT_PID, &pid, sizeof(pid), nullptr, 0, &returned, nullptr);
}

void DeadDriverController::StopProtecting()
{
	DWORD returned;
	DeviceIoControl(_hDevice, IOCTL_DCHECKERS_STOP_PROTECTING, nullptr, 0, nullptr, 0, &returned, nullptr);
}

void DeadDriverController::BlockProcessesCreation()
{
	DWORD returned;
	DeviceIoControl(_hDevice, IOCTL_DCHECKERS_BLOCK_PROCESS_CREATION, nullptr, 0, nullptr, 0, &returned, nullptr);
}

void DeadDriverController::StopBlockingProcessesCreation()
{
	DWORD returned;
	DeviceIoControl(_hDevice, IOCTL_DCHECKERS_STOP_BLOCKING_PROCESS_CREATION, nullptr, 0, nullptr, 0, &returned, nullptr);
}

void DeadDriverController::KillSystem()
{
	DWORD returned;
	DeviceIoControl(_hDevice, IOCTL_DCHECKERS_KILL_SYSTEM, nullptr, 0, nullptr, 0, &returned, nullptr);
}
