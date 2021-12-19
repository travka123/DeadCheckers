#pragma once

#include "Renderable.h"
#include "Interactive.h"

class CommonButton : public Renderable, public Interactive {
public:
	virtual ~CommonButton();
};