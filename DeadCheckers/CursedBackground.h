#pragma once

#include "Background.h"

class CursedBackground : public Background {
private:
	const int witheNoiseFramesCount = 20;
	const int minFramesBeforWitheNoise = 50;
	const int maxFramesBeforWitheNoise = 300;
	
	bool _showWiteNoise;
	int _framesBeforWitheNoise;
	int _whiteNoiseFrames;

public:
	CursedBackground();

	void Render(Painter& painter) override;
	bool NeedRedraw() override;
};