#include "Processable.h"

#include "Systems.h"

void Processable::RegisterProcessable()
{
	Systems::GetLogic()->RegisterProcessable(this);
}

void Processable::UnregisterProcessable()
{
	Systems::GetLogic()->UnregisterProcessable(this);
}
