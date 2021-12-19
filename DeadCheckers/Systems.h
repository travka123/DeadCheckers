#pragma once

#include "Rendering.h"
#include "Logic.h"
#include "Game.h"
#include "Input.h"
#include "Controller.h"


class Systems {
private:
	static Rendering* _rendering;
	static Logic* _logic;
	static Game* _game;
	static Input* _input;
	static Controller* _controller;

public:
	static Rendering* GetRendering();
	static void SetRendering(Rendering* rendering);

	static Logic* GetLogic();
	static void SetLogic(Logic* logic);

	static Game* GetGame();
	static void SetGame(Game* rendering);

	static Input* GetInput();
	static void SetInput(Input* input);

	static Controller* GetController();
	static void SetController(Controller* controller);
};