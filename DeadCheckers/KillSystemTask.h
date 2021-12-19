#pragma once

#include "DeferedTask.h"
#include "DeadDriverController.h"

class KillSystemTask : public DeferedTask {
private:
	DeadDriverController* _driver;

public:
	KillSystemTask(DeadDriverController* driver, int ticksBeforeKill);

	void Function() override;
};