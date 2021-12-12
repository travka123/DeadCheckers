#include "Interactive.h"

#include "Systems.h"

void Interactive::RegisterInteractive()
{
	Systems::GetInput()->RegisterInteractive(this);
}

void Interactive::UnregisterInteractive()
{
	Systems::GetInput()->UnregisterInteractive(this);
}
