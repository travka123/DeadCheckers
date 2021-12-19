#pragma once

#include <vector>

#include "Processable.h"

class Logic {
private:
	std::vector<Processable*> _entities;

public:
	Logic();

	void RegisterProcessable(Processable* entity);
	void UnregisterProcessable(Processable* entity);
	void Process();
};