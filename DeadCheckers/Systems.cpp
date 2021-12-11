#include "Systems.h"

Rendering* Systems::_rendering;
Game* Systems::_game;

Rendering* Systems::GetRendering()
{
	return _rendering;
}

void Systems::SetRendering(Rendering* rendering) {
	_rendering = rendering;
}

Game* Systems::GetGame() {
	return _game;
}

void Systems::SetGame(Game* game) {
	_game = game;
}
