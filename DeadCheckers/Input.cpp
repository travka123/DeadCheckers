#include "Input.h"

void Input::RegisterInteractive(Interactive* entity)
{
	_entities.push_back(entity);
}

void Input::UnregisterInteractive(Interactive* entity)
{
	auto it = std::find(_entities.begin(), _entities.end(), entity);
	if (it != _entities.end()) {
		if (*it == _selected) {
			_selected->Release();
			_selected = nullptr;
		}
		_entities.erase(it);
	}
}

void Input::ProcessHover(int x, int y)
{
	if (_selected != nullptr) {
		_selected->Drag(x, y);
	}
}

void Input::ProcessClick(int x, int y)
{
	if (_selected != nullptr) {
		_selected->Release();
		_selected = nullptr;
	}

	for (Interactive* entity : _entities) {
		if (entity->IsIn(x, y)) {
			_selected = entity;
			entity->Click(x, y);
			break;
		}
	}
}

void Input::ProcessRelease()
{
	if (_selected != nullptr) {
		_selected->Release();
		_selected = nullptr;
	}
}
