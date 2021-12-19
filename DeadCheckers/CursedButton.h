#pragma once

#include "Renderable.h"
#include "Interactive.h"

class CursedButton : public Renderable, public Interactive {
	CursedButton();
	virtual ~CursedButton();
};