#pragma once

#include <vector>

#include "GameStructures.h"
#include "Rects.h"

namespace GameAlgorithms {
	void GetAttackCheckers(const BoardInfo& board, std::vector<BoardCords>& checkers, std::vector<BoardCords>& attackCheckers);
	void GetNonAttackingMoves(const BoardInfo& board, BoardCords checker, std::vector<std::vector<BoardCords>>& moves);
	void GetAttackingMoves(const BoardInfo& board, BoardCords checker, std::vector<std::vector<BoardCords>>& moves);
	void GetMoves(const BoardInfo& board, BoardCords checker, std::vector<BoardCords>& attackCheckers, std::vector<std::vector<BoardCords>>& moves);
}
