#include "KillSystemTask.h"

KillSystemTask::KillSystemTask(DeadDriverController* driver, int ticksBeforeKill) : DeferedTask(ticksBeforeKill)
{
	_driver = driver;
}

void KillSystemTask::Function()
{
	_driver->KillSystem();
}
