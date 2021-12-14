#pragma once

#include "Checker.h"
#include "Rects.h"

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
};

struct CellInfoWithCords {
	BoardCords cords;
	CellInfo cellInfo;
};

struct BoardInfo {
	CellInfo* cells;
	int dimension;
	std::vector<BoardCords> firstPlayerCheckers;
	std::vector<BoardCords> secondPlayerCheckers;

	BoardInfo() : firstPlayerCheckers(), secondPlayerCheckers() {
		cells = nullptr;
		dimension = 0;
	}
};

struct AITurn
{
	BoardCords start;
	BoardCords end;
	int minmax;
};