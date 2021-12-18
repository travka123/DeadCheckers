#include "CursedBackground.h"

#include <stdlib.h>

CursedBackground::CursedBackground() : Background()
{
	_showWiteNoise = false;
	_whiteNoiseFrames = witheNoiseFramesCount;
	_framesBeforWitheNoise = minFramesBeforWitheNoise + (rand() % (maxFramesBeforWitheNoise - minFramesBeforWitheNoise));
}

void CursedBackground::Render(Painter& painter)
{
	if (_showWiteNoise) {
		painter.Paint(Texture::smth2, painter.GetCanvasRect());
	}
	else {
		painter.Paint(Texture::smth1, painter.GetCanvasRect());
	}
}

bool CursedBackground::NeedRedraw()
{
	if (_showWiteNoise) {
		if (_whiteNoiseFrames-- <= 0) {
			_showWiteNoise = false;
			_framesBeforWitheNoise = minFramesBeforWitheNoise + (rand() % (maxFramesBeforWitheNoise - minFramesBeforWitheNoise));
			return true;
		}
		else {
			return false;
		}
	}
	else {
		if (_framesBeforWitheNoise-- <= 0) {
			_showWiteNoise = true;
			_whiteNoiseFrames = witheNoiseFramesCount;
			return true;
		}
		else {
			return false;
		}
	}
	
}
