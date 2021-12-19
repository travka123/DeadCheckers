#include "Systems.h"

Rendering* Systems::_rendering;
Logic* Systems::_logic;
Game* Systems::_game;
Input* Systems::_input;
Controller* Systems::_controller;

Rendering* Systems::GetRendering()
{
	return _rendering;
}

void Systems::SetRendering(Rendering* rendering) {
	_rendering = rendering;
}

Logic* Systems::GetLogic()
{
	return _logic;
}

void Systems::SetLogic(Logic* logic)
{
	_logic = logic;
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

Controller* Systems::GetController()
{
	return _controller;
}

void Systems::SetController(Controller* controller)
{
	_controller = controller;
}
