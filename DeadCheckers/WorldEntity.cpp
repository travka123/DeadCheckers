#include "WorldEntity.h"

Background* WorldEntity::_background;
CheckersField* WorldEntity::_checkersField;

void WorldEntity::SetBackground(Background* background) 
{
	_background = background;
}

void WorldEntity::SetCheckersField(CheckersField* checkersField)
{
	_checkersField = checkersField;
}
