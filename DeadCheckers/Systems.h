#pragma once

#include "Rendering.h"
#include "Game.h"
#include "Input.h"
#include "Controller.h"

class Systems {
private:
	static Rendering* _rendering;
	static Game* _game;
	static Input* _input;
	static Controller* _controller;

public:
	static Rendering* GetRendering();
	static void SetRendering(Rendering* rendering);

	static Game* GetGame();
	static void SetGame(Game* rendering);

	static Input* GetInput();
	static void SetInput(Input* input);

	static Controller* GetController();
	static void SetController(Controller* controller);
};