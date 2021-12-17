#include "ChangeStyleButton.h"

#include "Systems.h"

ChangeStyleButton::ChangeStyleButton()
{
	RegisterRenderable(RenderLayer::very_top);
	RegisterInteractive();
}

void ChangeStyleButton::Render(Painter& painter)
{
	painter.Paint(Texture::btn_change_style, Systems::GetRendering()->ButtonIndexToRect(1));
}

bool ChangeStyleButton::NeedRedraw()
{
	return false;
}

void ChangeStyleButton::Click(int x, int y)
{
	Systems::GetRendering()->SetNextStyle();
}

void ChangeStyleButton::Drag(int x, int y) { }

void ChangeStyleButton::Release() { }

bool ChangeStyleButton::IsIn(int x, int y)
{
	Rect rect = Systems::GetRendering()->ButtonIndexToRect(1);
	return (rect.left <= x) && (rect.right >= x) && (rect.top <= y) && (rect.bottom >= y);
}
