#pragma once

#include <ntddk.h>

struct Globals {
	bool protect;
	bool blockCreation;
	ULONG processId;
	PVOID regHandle;
};