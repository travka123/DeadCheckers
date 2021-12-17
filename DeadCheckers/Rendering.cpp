#include "Rendering.h"

void Rendering::RegisterEntity(Renderable* entity, RenderLayer layer) {
	_layers[static_cast<int>(layer)].push_back(entity);
	_layerNeedRedraw[static_cast<int>(layer)] = true;
}

void Rendering::ChangeRenderLayer(Renderable* entity, RenderLayer layer)
{
	UnregisterEntity(entity);
	RegisterEntity(entity, layer);
}

void Rendering::UnregisterEntity(Renderable* entity) {
	for (int i = 0; i < RENDER_LAYERS_COUNT; i++) {
		auto it = std::find(_layers[i].begin(), _layers[i].end(), entity);
		if (it != _layers[i].end()) {
			_layers[i].erase(it);
			_layerNeedRedraw[i] = true;
			break;
		}
	}
}

Rect Rendering::CellCordsToRect(int x, int y, float scale)
{
	Rect rect;

	rect.left = _layout.board.left + _layout.boardCellSize * x;
	rect.top = _layout.board.top + _layout.boardCellSize * y;
	rect.right = rect.left + _layout.boardCellSize;
	rect.bottom = rect.top + _layout.boardCellSize;

	return rect;
}

BoardCords Rendering::ScreenCordsToCellCords(int x, int y)
{
	BoardCords cords;

	cords.x = (x - _layout.board.left) / _layout.boardCellSize;
	cords.x -= (x - _layout.board.left < 0);

	cords.y = (y - _layout.board.top) / _layout.boardCellSize;
	cords.y -= (y - _layout.board.top < 0);

	return cords;
}

Rect Rendering::ButtonIndexToRect(int index)
{
	Rect menu = _layout.menu;
	menu.bottom -= index * 2 * _layout.menuWidth;
	menu.top = menu.bottom - _layout.menuWidth;
	return menu;
}
