#include "Game.h"

#include <string>
#include <exception>

#include "PlayerChecker.h"

Game::Game() : _firstPlayerCheckers(), _secondPlayerCheckers()
{
	_turnCount = 0;
}

void Game::Start(int rowCount, bool useAI)
{
	if (rowCount % 2 == 1) {
		throw std::exception();
	}
	_rowCount = rowCount;
	_cellCount = rowCount * rowCount;
	_useAI = useAI;
	_boardInfo = new CellInfo[_cellCount];
	memset(_boardInfo, 0, sizeof(CellInfo) * _cellCount);
	_turnCount = 0;

	_attackHighlight = new CellHighlight();
	_possibleMovesHighlight = new CellHighlight();

	int swap = 0;
	for (int i = 0; i < (rowCount - 1) / 2; i++) {
		for (int j = 0; j < rowCount; j += 2) {

			CellCords cords = { j + swap ^ 1, i };
			_boardInfo[cords.y * rowCount + cords.x].checker = new PlayerChecker(Texture::black_checker, cords.y, cords.x);
			_boardInfo[cords.y * rowCount + cords.x].notEmpty = true;
			_boardInfo[cords.y * rowCount + cords.x].team = Team::second;
			_boardInfo[cords.y * rowCount + cords.x].species = Species::common;
			_secondPlayerCheckers.push_back(cords);

			cords = { j + swap, rowCount - 1 - i };
			_boardInfo[cords.y * rowCount + cords.x].checker = new PlayerChecker(Texture::white_checker, cords.y, cords.x);
			_boardInfo[cords.y * rowCount + cords.x].notEmpty = true;
			_boardInfo[cords.y * rowCount + cords.x].team = Team::first;
			_boardInfo[cords.y * rowCount + cords.x].species = Species::common;
			_firstPlayerCheckers.push_back(cords);
		}
		swap ^= 1;
	}

	PrepareNextTurn();
}

bool Game::IsMyTurn(int x, int y)
{
	return (x >= 0) && (x < _rowCount) && (y >= 0) && (y < _rowCount) &&
		(_boardInfo[y * _rowCount + x].team == _turnOf);
}

void Game::ShowPossibleMoves(int x, int y)
{
	if ((x >= 0) && (y >= 0) && (x < _rowCount) && (y < _rowCount)) {
		std::vector<std::vector<CellCords>> moves;
		GetPossibleMoves(moves, x, y);
		_possibleMovesHighlight->Clear();
		//_possibleMovesHighlight->Add(Color::green, x, y);
		for (auto& move : moves) {
			int endIndex = move.size() - 1;
			for (int i = 0; i < endIndex; i++) {
				CellCords cords = move[i];
				if (_boardInfo[cords.y * _rowCount + cords.x].notEmpty) {
					if (_boardInfo[cords.y * _rowCount + cords.x].team != _turnOf) {
						_possibleMovesHighlight->Add(Color::dark_orange, cords.x, cords.y);
					}
					else {
						_possibleMovesHighlight->Add(Color::green, cords.x, cords.y);
					}
				}
				else {
					_possibleMovesHighlight->Add(Color::royal_blue, cords.x, cords.y);
				}
			}
			CellCords cords = move[endIndex];
			_possibleMovesHighlight->Add(Color::blue, cords.x, cords.y);
		}
	}
}

void Game::HidePossibleMoves()
{
	_possibleMovesHighlight->Clear();
}

void Game::TryMakeMove(int x, int y, int nextX, int nextY)
{
	if ((x >= 0) && (y >= 0) && (x < _rowCount) && (y < _rowCount) &&
		(nextX >= 0) && (nextY >= 0) && (nextX < _rowCount) && (nextY <= _rowCount)) {

		std::vector<std::vector<CellCords>> moves;
		GetPossibleMoves(moves, x, y);

		std::vector<CellCords>* chosedMove = nullptr;
		for (auto& move : moves) {
			CellCords dest = move[move.size() - 1];
			if ((dest.x == nextX) && (dest.y == nextY)) {
				chosedMove = &move;
			}
		}

		if (chosedMove != nullptr) {
			memcpy(&_boardInfo[nextY * _rowCount + nextX], &_boardInfo[y * _rowCount + x], sizeof(CellInfo));
			memset(&_boardInfo[y * _rowCount + x], 0, sizeof(CellInfo));
			_boardInfo[nextY * _rowCount + nextX].checker->SetCords(nextX, nextY);

			if (((_turnOf == Team::first) && (nextY == 0)) || (nextY == _rowCount - 1)) {
				_boardInfo[nextY * _rowCount + nextX].species = Species::queen;
				_boardInfo[nextY * _rowCount + nextX].checker->Crown();
			}

			CellCords old = { x,y };
			CellCords next = { nextX, nextY };
			auto& vec = _turnOf == Team::first ? _firstPlayerCheckers : _secondPlayerCheckers;
			auto it = std::find(vec.begin(), vec.end(), old);
			vec[it - vec.begin()] = next;

			for (CellCords& cords : *chosedMove) {
				Team eTeam = _turnOf == Team::first ? Team::second : Team::first;
				if (_boardInfo[cords.y * _rowCount + cords.x].team == eTeam) {
					Checker* killedChecker = _boardInfo[cords.y * _rowCount + cords.x].checker;
					delete killedChecker;
					memset(&_boardInfo[cords.y * _rowCount + cords.x], 0, sizeof(CellInfo));
					auto& eVec = eTeam == Team::first ? _firstPlayerCheckers : _secondPlayerCheckers;
					eVec.erase(std::find(eVec.begin(), eVec.end(), cords));
				}
			}

			_turnCount++;
			PrepareNextTurn();
		}
	}
}

void Game::PrepareNextTurn()
{
	_attackHighlight->Clear();
	_turnOf = (_turnCount % 2 == 0) ? Team::first : Team::second;
	CollectAttackCheckers();
	HighlightAttackCheckers();
}

void Game::HighlightAttackCheckers()
{
	for (const CellCords& cords : _attackCheckers) {
		_attackHighlight->Add(Color::red, cords.x, cords.y);
	}
	_attackHighlight->Show();
}

void Game::CollectAttackCheckers()
{
	_attackCheckers.clear();
	auto& vec = _turnOf == Team::first ? _firstPlayerCheckers : _secondPlayerCheckers;
	for (CellCords cords : vec) {

		CellCords incs[] = { {-1, -1}, {1, -1}, {-1, 1}, {1, 1} };

		bool added = false;
		for (int i = 0; (i < 4) && (!added); i++) {
			if (_boardInfo[cords.y * _rowCount + cords.x].species == Species::common) {
				if ((cords.x + 2 * incs[i].x >= 0) && (cords.y + 2 * incs[i].y >= 0) &&
					(cords.x + 2 * incs[i].x < _rowCount) && (cords.y + 2 * incs[i].y < _rowCount) &&
					(_boardInfo[(cords.y + incs[i].y) * _rowCount + cords.x + incs[i].x].notEmpty) &&
					(_boardInfo[(cords.y + incs[i].y) * _rowCount + cords.x + incs[i].x].team != _turnOf) &&
					(!_boardInfo[(cords.y + 2 * incs[i].y) * _rowCount + cords.x + 2 * incs[i].x].notEmpty)) {
					_attackCheckers.push_back(cords);
					added = true;
				}
			}
			else if (_boardInfo[cords.y * _rowCount + cords.x].species == Species::queen) {
				int eCellX = cords.x + incs[i].x;
				int eCellY = cords.y + incs[i].y;
				int nextX = eCellX + incs[i].x;
				int nextY = eCellY + incs[i].y;

				while ((!added) && ((nextX >= 0) && (nextY >= 0) && (nextX < _rowCount) && (nextY < _rowCount))) {
					if (_boardInfo[eCellY * _rowCount + eCellX].notEmpty) {

						if ((_boardInfo[eCellY * _rowCount + eCellX].team != _turnOf) &&
							(!_boardInfo[nextY * _rowCount + nextX].notEmpty)) {
							_attackCheckers.push_back(cords);
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

void Game::GetPossibleMoves(std::vector<std::vector<CellCords>>& moves, int x, int y)
{
	if (_boardInfo[y * _rowCount + x].team != _turnOf) {
		return;
	}

	CellCords selfCords = { x, y };

	if (_attackCheckers.size() == 0) {
		if (_boardInfo[y * _rowCount + x].species == Species::common) {

			int direction = _turnOf == Team::first ? -1 : 1;

			if ((y + direction < _rowCount) && (y + direction >= 0) && (x - 1 >= 0) && (!_boardInfo[(y + direction) * _rowCount + (x - 1)].notEmpty)) {
				
				CellCords cords = { x - 1, y + direction };
				std::vector<CellCords> move;
				move.push_back(selfCords);
				move.push_back(cords);
				moves.push_back(move);
			}
			if ((y + direction < _rowCount) && (y + direction >= 0) && (x + 1 < _rowCount) && (!_boardInfo[(y + direction) * _rowCount + (x + 1)].notEmpty)) {
				CellCords cords = { x + 1, y + direction };
				std::vector<CellCords> move;
				move.push_back(selfCords);
				move.push_back(cords);
				moves.push_back(move);
			}
		}
		else {
			CellCords incs[] = { {-1, -1}, {1, -1}, {-1, 1}, {1, 1} };
			for (int i = 0; i < 4; i++) {
				int nextX = x + incs[i].x;
				int nextY = y + incs[i].y;
				while ((nextX >= 0) && (nextY >= 0) && (nextX < _rowCount) && (nextY < _rowCount) &&
					(!_boardInfo[nextY * _rowCount + nextX].notEmpty)) {

					CellCords cords = { nextX, nextY };
					std::vector<CellCords> move;
					move.push_back(selfCords);
					move.push_back(cords);
					moves.push_back(move);

					nextX += incs[i].x;
					nextY += incs[i].y;
				}
			}
		}
	}
	else {
		CellCords curCords = { x, y };
		auto it = std::find(_attackCheckers.begin(), _attackCheckers.end(), curCords);
		if (it != _attackCheckers.end()) {

			Species species = _boardInfo[curCords.y * _rowCount + curCords.x].species;
			CellCords incs[] = { {-1, -1}, {1, -1}, {-1, 1}, {1, 1} };
			std::vector<CellCords> path;
			std::vector<int> iterations;

			CellCords cords = { x, y };
			path.push_back(cords);
			iterations.push_back(0);

			do {

				CellCords curCords = path.back();
				int i = iterations.back();
				iterations.pop_back();
				bool criticalPath = !i;

				for (; i < 4; i++) {
					int nextX = curCords.x + incs[i].x;
					int nextY = curCords.y + incs[i].y;
					bool canBite = false; 
					
					if (species == Species::common) {
						canBite = (nextX + incs[i].x >= 0) && (nextY + incs[i].y >= 0) &&
							(nextX + incs[i].x < _rowCount) && (nextY + incs[i].y < _rowCount) &&
							(_boardInfo[nextY * _rowCount + nextX].notEmpty) &&
							(_boardInfo[nextY * _rowCount + nextX].team != _turnOf) &&
							(!_boardInfo[(nextY + incs[i].y) * _rowCount + nextX + incs[i].x].notEmpty);
					}
					else {
						while ((nextX + incs[i].x >= 0) && (nextY + incs[i].y >= 0) &&
							(nextX + incs[i].x < _rowCount) && (nextY + incs[i].y < _rowCount)) {

							if (_boardInfo[nextY * _rowCount + nextX].notEmpty) {

								if ((_boardInfo[nextY * _rowCount + nextX].team != _turnOf) &&
									(!_boardInfo[(nextY + incs[i].y) * _rowCount + nextX + incs[i].x].notEmpty)) {
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
						CellCords move = { nextX, nextY };
						path.push_back(move);
						move = { nextX + incs[i].x, nextY + incs[i].y };
						path.push_back(move);

						_boardInfo[curCords.y * _rowCount + curCords.x].notEmpty = false;
						_boardInfo[nextY * _rowCount + nextX].notEmpty = false;

						break;
					}
				}

				if (i == 4) {
					if (criticalPath) {
						std::vector<CellCords> copyOfPath = path;
						moves.push_back(copyOfPath);
					}

					if (path.size() >= 2) {
						path.pop_back();
					}

					CellCords cords = path.back();
					path.pop_back();
					_boardInfo[cords.y * _rowCount + cords.x].notEmpty = true;
				}

			} while (iterations.size());
		}
	}
}
