#pragma once

#include "Rendering.h"
#include "Game.h"

class Systems {
private:
	static Rendering* _rendering;
	static Game* _game;

public:
	static Rendering* GetRendering();
	static void SetRendering(Rendering* rendering);

	static Game* GetGame();
	static void SetGame(Game* rendering);
};