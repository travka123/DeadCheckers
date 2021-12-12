#pragma once

#include <vector>

#include "Interactive.h"

class Input {
private:
	Interactive* _selected = nullptr;
	std::vector<Interactive*> _entities;

public:
	void RegisterInteractive(Interactive* entity);
	void UnregisterInteractive(Interactive* entity);
	void ProcessHover(int x, int y);
	void ProcessClick(int x, int y);
	void ProcessRelease();
};