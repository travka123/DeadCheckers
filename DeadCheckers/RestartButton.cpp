#include "RestartButton.h"

#include "Systems.h"

RestartButton::RestartButton()
{
	RegisterRenderable(RenderLayer::very_top);
	RegisterInteractive();
}

RestartButton::~RestartButton()
{
	UnregisterInteractive();
	UnregisterRenderable();
}

void RestartButton::Render(Painter& painter)
{
	painter.Paint(Texture::btn_restart, Systems::GetRendering()->ButtonIndexToRect(0));
}

bool RestartButton::NeedRedraw()
{
	return false;
}

void RestartButton::Click(int x, int y)
{
	Systems::GetGame()->Restart();
}

void RestartButton::Drag(int x, int y)
{
}

void RestartButton::Release()
{
}

bool RestartButton::IsIn(int x, int y)
{
	Rect rect = Systems::GetRendering()->ButtonIndexToRect(0);
	return (rect.left <= x) && (rect.right >= x) && (rect.top <= y) && (rect.bottom >= y);
}
