#include "GameAlgorithms.h"

void GameAlgorithms::GetAttackCheckers(const BoardInfo& board, std::vector<BoardCords>& checkers, std::vector<BoardCords>& attackCheckers)
{
	for (BoardCords cords : checkers) {

		BoardCords incs[] = { {-1, -1}, {1, -1}, {-1, 1}, {1, 1} };

		bool added = false;
		Team checkerTeam = board.cells[cords.y * board.dimension + cords.x].team;
		for (int i = 0; (i < 4) && (!added); i++) {

			if (board.cells[cords.y * board.dimension + cords.x].species == Species::common) {

				if ((cords.x + 2 * incs[i].x >= 0) && (cords.y + 2 * incs[i].y >= 0) &&
					(cords.x + 2 * incs[i].x < board.dimension) && (cords.y + 2 * incs[i].y < board.dimension) &&
					(board.cells[(cords.y + incs[i].y) * board.dimension + cords.x + incs[i].x].notEmpty) &&
					(board.cells[(cords.y + incs[i].y) * board.dimension + cords.x + incs[i].x].team != checkerTeam) &&
					(!board.cells[(cords.y + 2 * incs[i].y) * board.dimension + cords.x + 2 * incs[i].x].notEmpty)) {
					attackCheckers.push_back(cords);
					added = true;
				}

			}
			else if (board.cells[cords.y * board.dimension + cords.x].species == Species::queen) {

				int eCellX = cords.x + incs[i].x;
				int eCellY = cords.y + incs[i].y;
				int nextX = eCellX + incs[i].x;
				int nextY = eCellY + incs[i].y;

				while ((!added) && ((nextX >= 0) && (nextY >= 0) && (nextX < board.dimension) && (nextY < board.dimension))) {
					if (board.cells[eCellY * board.dimension + eCellX].notEmpty) {

						if ((board.cells[eCellY * board.dimension + eCellX].team != checkerTeam) &&
							(!board.cells[nextY * board.dimension + nextX].notEmpty)) {
							attackCheckers.push_back(cords);
							added = true;
						}
						else {
							break;
						}

					}
					eCellX += incs[i].x;
					eCellY += incs[i].y;
					nextX += incs[i].x;
					nextY += incs[i].y;
				}

			}
		}
	}
}

void GameAlgorithms::GetNonAttackingMoves(const BoardInfo& board, BoardCords checker, std::vector<std::vector<BoardCords>>& moves)
{
	if (board.cells[checker.y * board.dimension + checker.x].species == Species::common) {

		Team checkerTeam = board.cells[checker.y * board.dimension + checker.x].team;
		int direction = checkerTeam == Team::first ? -1 : 1;

		if ((checker.y + direction < board.dimension) && (checker.y + direction >= 0) && (checker.x - 1 >= 0) &&
			(!board.cells[(checker.y + direction) * board.dimension + (checker.x - 1)].notEmpty)) {

			BoardCords cords = { checker.x - 1, checker.y + direction };
			std::vector<BoardCords> move;
			move.push_back(checker);
			move.push_back(cords);
			moves.push_back(move);
		}

		if ((checker.y + direction < board.dimension) && (checker.y + direction >= 0) && (checker.x + 1 < board.dimension) &&
			(!board.cells[(checker.y + direction) * board.dimension + (checker.x + 1)].notEmpty)) {

			BoardCords cords = { checker.x + 1, checker.y + direction };
			std::vector<BoardCords> move;
			move.push_back(checker);
			move.push_back(cords);
			moves.push_back(move);
		}

	}
	else {
		BoardCords incs[] = { {-1, -1}, {1, -1}, {-1, 1}, {1, 1} };
		for (int i = 0; i < 4; i++) {
			int nextX = checker.x + incs[i].x;
			int nextY = checker.y + incs[i].y;
			while ((nextX >= 0) && (nextY >= 0) && (nextX < board.dimension) && (nextY < board.dimension) &&
				(!board.cells[nextY * board.dimension + nextX].notEmpty)) {

				BoardCords cords = { nextX, nextY };
				std::vector<BoardCords> move;
				move.push_back(checker);
				move.push_back(cords);
				moves.push_back(move);

				nextX += incs[i].x;
				nextY += incs[i].y;
			}
		}
	}
}

void GameAlgorithms::GetAttackingMoves(const BoardInfo& board, BoardCords checker, std::vector<std::vector<BoardCords>>& moves)
{
	
	BoardCords incs[] = { {-1, -1}, {1, -1}, {-1, 1}, {1, 1} };
	std::vector<BoardCords> path;
	std::vector<int> iterations;

	Species species = board.cells[checker.y * board.dimension + checker.x].species;
	Team checkerTeam = board.cells[checker.y * board.dimension + checker.x].team;

	path.push_back(checker);
	iterations.push_back(0);

	do {

		BoardCords curCords = path.back();
		int i = iterations.back();
		iterations.pop_back();
		bool criticalPath = !i;

		for (; i < 4; i++) {
			int nextX = curCords.x + incs[i].x;
			int nextY = curCords.y + incs[i].y;
			bool canBite = false;

			if (species == Species::common) {
				canBite = (nextX + incs[i].x >= 0) && (nextY + incs[i].y >= 0) &&
					(nextX + incs[i].x < board.dimension) && (nextY + incs[i].y < board.dimension) &&
					(board.cells[nextY * board.dimension + nextX].notEmpty) &&
					(board.cells[nextY * board.dimension + nextX].team != checkerTeam) &&
					(!board.cells[(nextY + incs[i].y) * board.dimension + nextX + incs[i].x].notEmpty);
			}
			else {
				while ((nextX + incs[i].x >= 0) && (nextY + incs[i].y >= 0) &&
					(nextX + incs[i].x < board.dimension) && (nextY + incs[i].y < board.dimension)) {

					if (board.cells[nextY * board.dimension + nextX].notEmpty) {

						if ((board.cells[nextY * board.dimension + nextX].team != checkerTeam) &&
							(!board.cells[(nextY + incs[i].y) * board.dimension + nextX + incs[i].x].notEmpty)) {
							canBite = true;
						}
						break;
					}

					nextX += incs[i].x;
					nextY += incs[i].y;
				}
			}

			if (canBite) {
				iterations.push_back(i + 1);
				iterations.push_back(0);
				BoardCords move = { nextX, nextY };
				path.push_back(move);
				move = { nextX + incs[i].x, nextY + incs[i].y };
				path.push_back(move);

				board.cells[curCords.y * board.dimension + curCords.x].notEmpty = false;
				board.cells[nextY * board.dimension + nextX].notEmpty = false;

				break;
			}
		}

		if (i == 4) {
			if (criticalPath) {
				std::vector<BoardCords> copyOfPath = path;
				moves.push_back(copyOfPath);
			}

			if (path.size() >= 2) {
				path.pop_back();
			}

			BoardCords cords = path.back();
			path.pop_back();
			board.cells[cords.y * board.dimension + cords.x].notEmpty = true;
		}

	} while (iterations.size());
}

void GameAlgorithms::GetMoves(const BoardInfo& board, BoardCords checker, std::vector<BoardCords>& attackCheckers, std::vector<std::vector<BoardCords>>& moves)
{
	auto it = std::find(attackCheckers.begin(), attackCheckers.end(), checker);
	if (it == attackCheckers.end()) {
		GetNonAttackingMoves(board, checker, moves);
	}
	else {
		GetAttackingMoves(board, checker, moves);
	}
}
