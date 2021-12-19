#include "CursedButton.h"

CursedButton::CursedButton()
{
	RegisterRenderable(RenderLayer::very_top);
	RegisterInteractive();
}

CursedButton::~CursedButton()
{
	UnregisterInteractive();
	UnregisterRenderable();
}
