#include "Rendering.h"

void Rendering::RegisterEntity(Renderable* entity, RenderLayer layer) {
	_layers[static_cast<int>(layer)].push_back(entity);
}

void Rendering::ChangeRenderLayer(Renderable* entity, RenderLayer layer)
{
	UnregisterEntity(entity);
	RegisterEntity(entity, layer);
}

void Rendering::UnregisterEntity(Renderable* entity) {
	for (auto& layer : _layers) {
		auto it = std::find(layer.begin(), layer.end(), entity);
		if (it != layer.end()) {
			layer.erase(it);
			break;
		}
	}
}

void Rendering::CordsToCellCords(int& x, int& y)
{
	x = (x - _layout.board.left) / _layout.boardCellSize;
	y = (y - _layout.board.top) / _layout.boardCellSize;
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
