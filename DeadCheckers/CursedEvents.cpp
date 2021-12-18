#include "CursedEvents.h"

#include "UniqueEntitiesStorage.h"
#include "StringCellIndexes.h"
#include "CursedCellIndexes.h"

void CursedEvents::SetNormalCellIndexes()
{
	delete UniqueEntitiesStorage::cellIndexes;
	UniqueEntitiesStorage::cellIndexes = new CellIndexes();
}

void CursedEvents::SetWarningCellIndexes()
{
	delete UniqueEntitiesStorage::cellIndexes;
	UniqueEntitiesStorage::cellIndexes = new StringCellIndexes(L"ABCDSTOP", L"12345678");
}

void CursedEvents::SetCursedCellIndexes()
{
	delete UniqueEntitiesStorage::cellIndexes;
	UniqueEntitiesStorage::cellIndexes = new CursedCellIndexes();
}
