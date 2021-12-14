#pragma once

#include <vector>

#include "GameStructures.h"
#include "Rects.h"

namespace GameAlgorithms {
	void GetAttackCheckers(const BoardInfo& board, const std::vector<BoardCords>& checkers, std::vector<BoardCords>& attackCheckers);
	void GetNonAttackingMoves(const BoardInfo& board, BoardCords checker, std::vector<std::vector<BoardCords>>& moves);
	void GetAttackingMoves(const BoardInfo& board, BoardCords checker, std::vector<std::vector<BoardCords>>& moves);
	void GetMoves(const BoardInfo& board, BoardCords checker, std::vector<std::vector<BoardCords>>& moves);
	void ApplyMove(BoardInfo& board, const std::vector<BoardCords>& move, std::vector<BoardCords>& removedCheckers);
	void ApplyMoveWithHistory(BoardInfo& board, const std::vector<BoardCords>& move, std::vector<CellInfoWithCords>& changedCells, std::vector<BoardCords>& removedCheckers);
	void RollBack(BoardInfo& board, const std::vector<CellInfoWithCords>& changedCells, const std::vector<BoardCords>& removedCheckers,
		BoardCords start, BoardCords end, Team turnOf);
}
