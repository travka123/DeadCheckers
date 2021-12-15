#include "GameAlgorithms.h"

void GameAlgorithms::GetAttackCheckers(const BoardInfo& board, const std::vector<BoardCords>& checkers, std::vector<BoardCords>& attackCheckers)
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
	int lastUsedDirection = -1;

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
			
			if ((lastUsedDirection >= 0) && (incs[lastUsedDirection].x != incs[i].x) && (incs[lastUsedDirection].y != incs[i].y)) {
				lastUsedDirection = -1;
				continue;
			}

			int nextX = curCords.x + incs[i].x;
			int nextY = curCords.y + incs[i].y;
			bool canBite = false;

			if (species == Species::common) {
				canBite = (nextX + incs[i].x >= 0) && (nextY + incs[i].y >= 0) &&
					(nextX + incs[i].x < board.dimension) && (nextY + incs[i].y < board.dimension) &&
					(board.cells[nextY * board.dimension + nextX].notEmpty) &&
					(board.cells[nextY * board.dimension + nextX].team != checkerTeam) &&
					(!board.cells[(nextY + incs[i].y) * board.dimension + nextX + incs[i].x].notEmpty) &&
					((board.cells[(nextY + incs[i].y) * board.dimension + nextX + incs[i].x].team == Team::none));
			}
			else {
				while ((nextX + incs[i].x >= 0) && (nextY + incs[i].y >= 0) &&
					(nextX + incs[i].x < board.dimension) && (nextY + incs[i].y < board.dimension)) {

					if (board.cells[nextY * board.dimension + nextX].notEmpty) {

						if (((board.cells[nextY * board.dimension + nextX].team != checkerTeam) &&
							(!board.cells[(nextY + incs[i].y) * board.dimension + nextX + incs[i].x].notEmpty)) &&
							((board.cells[(nextY + incs[i].y) * board.dimension + nextX + incs[i].x].team == Team::none))) {
							canBite = true;
						}
						break;
					}

					nextX += incs[i].x;
					nextY += incs[i].y;
				}
			}

			if (canBite) {
				lastUsedDirection = i;
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

void GameAlgorithms::GetMoves(const BoardInfo& board, BoardCords checker, std::vector<std::vector<BoardCords>>& moves)
{
	std::vector<BoardCords> attackCheckers;
	Team team = board.cells[checker.y * board.dimension + checker.x].team;
	const auto& teamCheckers = team == Team::first ? board.firstPlayerCheckers : board.secondPlayerCheckers;

	GetAttackCheckers(board, teamCheckers, attackCheckers);

	if (attackCheckers.size()) {
		auto it = std::find(attackCheckers.begin(), attackCheckers.end(), checker);
		if (it != attackCheckers.end()) {
			GetAttackingMoves(board, checker, moves);
		}
	}
	else {
		GetNonAttackingMoves(board, checker, moves);
	}
}

void GameAlgorithms::ApplyMove(BoardInfo& board, const std::vector<BoardCords>& move, std::vector<BoardCords>& removedCheckers)
{
	const BoardCords& currentPosition = move[0];
	const BoardCords& nextPosition = move[move.size() - 1];

	memcpy(&board.cells[nextPosition.y * board.dimension + nextPosition.x], &board.cells[currentPosition.y * board.dimension + currentPosition.x], sizeof(CellInfo));
	memset(&board.cells[currentPosition.y * board.dimension + currentPosition.x], 0, sizeof(CellInfo));

	CellInfo& movedCheckerCell = board.cells[nextPosition.y * board.dimension + nextPosition.x];

	auto& teamCheckers = movedCheckerCell.team == Team::first ? board.firstPlayerCheckers : board.secondPlayerCheckers;
	auto it = std::find(teamCheckers.begin(), teamCheckers.end(), currentPosition);
	teamCheckers[it - teamCheckers.begin()] = nextPosition;

	if (((movedCheckerCell.team == Team::first) && (nextPosition.y == 0)) || 
		((movedCheckerCell.team == Team::second) && (nextPosition.y == board.dimension - 1))) {
		movedCheckerCell.species = Species::queen;
	}

	auto& enemyTeamCheckers = movedCheckerCell.team == Team::first ? board.secondPlayerCheckers : board.firstPlayerCheckers;
	for (const BoardCords& pathCords : move) {
		CellInfo* cellOnPath = &board.cells[pathCords.y * board.dimension + pathCords.x];
		if (cellOnPath->team == (movedCheckerCell.team == Team::first ? Team::second : Team::first)) {
			memset(cellOnPath, 0, sizeof(CellInfo));
			auto it = std::find(enemyTeamCheckers.begin(), enemyTeamCheckers.end(), pathCords);
			enemyTeamCheckers.erase(it);
			removedCheckers.push_back(pathCords);
		}
	}
}

void GameAlgorithms::ApplyMoveWithHistory(BoardInfo& board, const std::vector<BoardCords>& move, std::vector<CellInfoWithCords>& changedCells, std::vector<BoardCords>& removedCheckers)
{
	CellInfoWithCords cellForChange;

	const BoardCords& currentPosition = move[0];
	const BoardCords& nextPosition = move[move.size() - 1];

	cellForChange.cords = currentPosition;
	cellForChange.cellInfo = board.cells[currentPosition.y * board.dimension + currentPosition.x];
	changedCells.push_back(cellForChange);

	cellForChange.cords = nextPosition;
	cellForChange.cellInfo = board.cells[nextPosition.y * board.dimension + nextPosition.x];
	changedCells.push_back(cellForChange);

	if (!(currentPosition == nextPosition)) {
		memcpy(&board.cells[nextPosition.y * board.dimension + nextPosition.x], &board.cells[currentPosition.y * board.dimension + currentPosition.x], sizeof(CellInfo));
		memset(&board.cells[currentPosition.y * board.dimension + currentPosition.x], 0, sizeof(CellInfo));
	}
	
	CellInfo& movedCheckerCell = board.cells[nextPosition.y * board.dimension + nextPosition.x];

	auto& teamCheckers = movedCheckerCell.team == Team::first ? board.firstPlayerCheckers : board.secondPlayerCheckers;
	auto it = std::find(teamCheckers.begin(), teamCheckers.end(), currentPosition);
	teamCheckers[it - teamCheckers.begin()] = nextPosition;

	if (((movedCheckerCell.team == Team::first) && (nextPosition.y == 0)) || 
		((movedCheckerCell.team == Team::second) && (nextPosition.y == board.dimension - 1))) {
		movedCheckerCell.species = Species::queen;
	}

	auto& enemyTeamCheckers = movedCheckerCell.team == Team::first ? board.secondPlayerCheckers : board.firstPlayerCheckers;
	for (const BoardCords& pathCords : move) {

		CellInfo* cellOnPath = &board.cells[pathCords.y * board.dimension + pathCords.x];
		if (cellOnPath->team == (movedCheckerCell.team == Team::first ? Team::second : Team::first)) {

			cellForChange.cords = pathCords;
			cellForChange.cellInfo = board.cells[pathCords.y * board.dimension + pathCords.x];
			changedCells.push_back(cellForChange);

			memset(cellOnPath, 0, sizeof(CellInfo));
			auto it = std::find(enemyTeamCheckers.begin(), enemyTeamCheckers.end(), pathCords);
			enemyTeamCheckers.erase(it);
			removedCheckers.push_back(pathCords);
		}
	}
}

void GameAlgorithms::RollBack(BoardInfo& board, const std::vector<CellInfoWithCords>& changedCells, const std::vector<BoardCords>& removedCheckers,
	BoardCords startCords, BoardCords endCords, Team turnOf)
{
	for (int i = changedCells.size() - 1; i >= 0; i--) {
		const CellInfoWithCords& change = changedCells[i];
		memcpy(&board.cells[change.cords.y * board.dimension + change.cords.x], &change.cellInfo, sizeof(CellInfo));
	}

	auto& checkers = turnOf == Team::first ? board.firstPlayerCheckers : board.secondPlayerCheckers;
	auto it = std::find(checkers.begin(), checkers.end(), endCords);
	checkers[it - checkers.begin()] = startCords;

	auto& eCheckers = turnOf == Team::first ? board.secondPlayerCheckers : board.firstPlayerCheckers;
	for (const BoardCords& checker : removedCheckers) {
		eCheckers.push_back(checker);
	}
}
