#pragma once

#include "Checker.h"

enum class Species : short {
	none,
	common,
	queen
};

enum class Team : short {
	none,
	first,
	second
};

struct CellInfo
{
	bool notEmpty;
	Team team;
	Species species;
	Checker* checker;
};

struct BoardInfo {
	CellInfo* cells;
	int dimension;
};