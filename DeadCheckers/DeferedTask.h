#pragma once

#include "Processable.h"

class DeferedTask : Processable {
private:
	int _ticksBeforeCall;

public:
	DeferedTask(int ticksBeforeCall);
	virtual ~DeferedTask();

	void Process() override;
	virtual void Function() = 0;
};