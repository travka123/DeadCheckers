#include "CursedEvents.h"

#include "UniqueEntitiesStorage.h"
#include "StringCellIndexes.h"
#include "CursedCellIndexes.h"
#include "CursedBackground.h"
#include "CursedButton.h"

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

void CursedEvents::SetLastWarningCellIndexes()
{
	delete UniqueEntitiesStorage::cellIndexes;
	UniqueEntitiesStorage::cellIndexes = new StringCellIndexes(L"STOPSTOP", L"STOPSTOP");
}

void CursedEvents::SetCursedCellIndexes()
{
	delete UniqueEntitiesStorage::cellIndexes;
	UniqueEntitiesStorage::cellIndexes = new CursedCellIndexes();
}

void CursedEvents::SetCursedBackground()
{
	delete UniqueEntitiesStorage::background;
	UniqueEntitiesStorage::background = new CursedBackground();
}

void CursedEvents::BlockButtons()
{
	delete UniqueEntitiesStorage::useAIBtn;
	UniqueEntitiesStorage::useAIBtn = new CursedButton(Texture::btn_set_p2, 2);

	delete UniqueEntitiesStorage::changeStyleBtn;
	UniqueEntitiesStorage::changeStyleBtn = new CursedButton(Texture::btn_change_style, 1);

	delete UniqueEntitiesStorage::restartBtn;
	UniqueEntitiesStorage::restartBtn = new CursedButton(Texture::btn_restart, 0);
}
