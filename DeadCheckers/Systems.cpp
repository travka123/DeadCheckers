#include "Systems.h"

Rendering* Systems::_rendering;
Game* Systems::_game;
Input* Systems::_input;

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

Input* Systems::GetInput() {
	return _input;
}

void Systems::SetInput(Input* input) {
	_input = input;
}