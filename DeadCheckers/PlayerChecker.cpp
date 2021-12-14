#include "PlayerChecker.h"
#include "Systems.h"

PlayerChecker::PlayerChecker(Texture texture, int cellY, int cellX) : Checker(texture, cellY, cellX)
{
	RegisterInteractive();

	_size = _draggingXOffset = _draggingYOffset = _draggingX = _draggingY = 0;
	_selected = false;
	_needRedraw = false;
}

PlayerChecker::~PlayerChecker()
{
	UnregisterInteractive();
}

void PlayerChecker::Render(Painter& painter)
{
	if (_selected) {
		Rect rect;
		rect.left = _draggingX - _draggingXOffset;
		rect.top = _draggingY - _draggingYOffset;
		rect.right = rect.left + _size;
		rect.bottom = rect.top + _size;

		Checker::Render(painter, rect);
	}
	else {
		Checker::Render(painter);
		_needRedraw = false;
	}
}

void PlayerChecker::Click(int x, int y)
{
	Game* game = Systems::GetGame();
	if (game->IsMyTurn(_cellX, _cellY)) {
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

		game->ShowPossibleMoves(_cellX, _cellY);

		_needRedraw = true;
	}
}

void PlayerChecker::Drag(int x, int y)
{
	int lateralEnlargement = _size * 0.25 / 1.25 / 2;
	if (_selected) {
		_draggingX = x - lateralEnlargement;
		_draggingY = y - lateralEnlargement;
	}
}

void PlayerChecker::Release()
{
	if (_selected) {
		_selected = false;
		ChangeRenderLayer(RenderLayer::middle);

		BoardCords cords = Systems::GetRendering()->ScreenCordsToCellCords(_draggingX - _draggingXOffset + _size / 2, 
			_draggingY - _draggingYOffset + _size / 2);

		_draggingXOffset = _draggingYOffset = _draggingX = _draggingY = 0;

		Game* game = Systems::GetGame();
		game->HidePossibleMoves();
		game->TryMakeMove(_cellX, _cellY, cords.x, cords.y);
	}
}

bool PlayerChecker::IsIn(int x, int y)
{
	Rect rect = Systems::GetRendering()->CellCordsToRect(_cellX, _cellY, 1);
	return (x >= rect.left) && (x <= rect.right) && (y >= rect.top) && (y <= rect.bottom);
}

bool PlayerChecker::NeedRedraw()
{
	return _needRedraw || _selected;
}
