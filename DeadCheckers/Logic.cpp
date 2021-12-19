#include "Logic.h"

Logic::Logic() : _entities()
{
}

void Logic::RegisterProcessable(Processable* entity)
{
	_entities.push_back(entity);
}

void Logic::UnregisterProcessable(Processable* entity)
{
	auto it = std::find(_entities.begin(), _entities.end(), entity);
	if (it != _entities.end()) {
		_entities.erase(it);
	}
}

void Logic::Process()
{
	for (Processable* entity : _entities) {
		entity->Process();
	}
}
