#include "UseAIButton.h"

#include "Systems.h"

UseAIButton::UseAIButton()
{
	RegisterRenderable(RenderLayer::very_top);
	RegisterInteractive();
}

void UseAIButton::Render(Painter& painter)
{
	if (_useAI) {
		painter.Paint(Texture::btn_set_p2, Systems::GetRendering()->ButtonIndexToRect(2));
	}
	else {
		painter.Paint(Texture::btn_set_ai, Systems::GetRendering()->ButtonIndexToRect(2));
	}
	_needRedraw = false;
}

bool UseAIButton::NeedRedraw()
{
	return _needRedraw;
}

void UseAIButton::Click(int x, int y)
{
	Systems::GetGame()->SwitchSecondPlayerMode();
	_useAI = !_useAI;
	_needRedraw = true;
}

void UseAIButton::Drag(int x, int y)
{
}

void UseAIButton::Release()
{
}

bool UseAIButton::IsIn(int x, int y)
{
	Rect rect = Systems::GetRendering()->ButtonIndexToRect(2);
	return (rect.left <= x) && (rect.right >= x) && (rect.top <= y) && (rect.bottom >= y);
}
