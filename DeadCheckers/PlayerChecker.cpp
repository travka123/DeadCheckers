#include "PlayerChecker.h"
#include "Systems.h"

PlayerChecker::PlayerChecker(Texture texture, int cellY, int cellX) : Checker(texture, cellY, cellX)
{
	RegisterInteractive();

	_size = _draggingXOffset = _draggingYOffset = _draggingX = _draggingY = 0;
	_selected = false;
}

void PlayerChecker::Render(Painter& painter)
{
	if (_selected) {
		Rect rect;
		rect.left = _draggingX - _draggingXOffset;
		rect.top = _draggingY - _draggingYOffset;
		rect.right = rect.left + _size;
		rect.bottom = rect.top + _size;

		painter.Paint(_texture, rect);
	}
	else {
		Checker::Render(painter);
	}
}

void PlayerChecker::Click(int x, int y)
{
	_selected = true;
	Rect rect = Systems::GetRendering()->CellCordsToRect(_cellX, _cellY, 1);

	int normalSize = rect.right - rect.left;
	int lateralEnlargement = (normalSize * 1.25 - normalSize) / 2;

	_draggingXOffset = x - rect.left;
	_draggingYOffset = y - rect.top;
	_draggingX = x - lateralEnlargement;
	_draggingY = y - lateralEnlargement;
	_size = normalSize + lateralEnlargement * 2;

	ChangeRenderLayer(RenderLayer::above_middle_1);
}

void PlayerChecker::Drag(int x, int y)
{
	if (_selected) {
		_draggingX = x;
		_draggingY = y;
	}
}

void PlayerChecker::Release()
{
	if (_selected) {
		_selected = false;
		_draggingXOffset = _draggingYOffset = _draggingX = _draggingY = 0;
		ChangeRenderLayer(RenderLayer::middle);
	}
}

bool PlayerChecker::IsIn(int x, int y)
{
	Systems::GetRendering()->CordsToCellCords(x, y);
	return (x == _cellX) && (y == _cellY);
}
