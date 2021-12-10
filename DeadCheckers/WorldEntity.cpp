#include "WorldEntity.h"

Background* WorldEntity::_background;

void WorldEntity::SetBackground(Background* background) {
	_background = background;
}