#include "DeferedTask.h"

DeferedTask::DeferedTask(int ticksBeforeCall)
{
	RegisterProcessable();

	_ticksBeforeCall = ticksBeforeCall;
}

DeferedTask::~DeferedTask()
{
	UnregisterProcessable();
}

void DeferedTask::Process()
{
	if (_ticksBeforeCall-- <= 0) {
		Function();
		delete this;
	}
}
