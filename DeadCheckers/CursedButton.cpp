#include "CursedButton.h"

#include <stdlib.h>

#include "Systems.h"

CursedButton::CursedButton(Texture texture, int buttonIndex)
{
	RegisterRenderable(RenderLayer::very_top);
	RegisterInteractive();

	_texture = texture;
	_rect = Systems::GetRendering()->ButtonIndexToRect(buttonIndex);
	_size = _rect.right - _rect.left;
	_needRedraw = false;
}

CursedButton::~CursedButton()
{
	UnregisterInteractive();
	UnregisterRenderable();
}

void CursedButton::Render(Painter& painter)
{
	painter.Paint(_texture, _rect);
}

bool CursedButton::NeedRedraw()
{
	return _needRedraw;
}

void CursedButton::Click(int x, int y)
{
	
}

void CursedButton::Hover(int x, int y)
{
	int direction = rand() % 4;
	int xOffset = (_size + 20) * ((direction & 1) ? 1 : -1);
	int yOffset = (_size + 20) * ((direction & 2) ? 1 : -1);

	_rect.left += xOffset;
	_rect.right += xOffset;

	_rect.top += yOffset;
	_rect.bottom += yOffset;

	_needRedraw = true;
}

void CursedButton::Drag(int x, int y)
{
}

void CursedButton::Release()
{
}

bool CursedButton::IsIn(int x, int y)
{
	return (_rect.left <= x) && (_rect.top <= y) && (_rect.right >= x) && (_rect.bottom >= y);
}
