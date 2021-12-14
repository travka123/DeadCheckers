#include "Game.h"

#include <string>
#include <exception>

#include "GameAlgorithms.h"
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

	_boardInfo.dimension = rowCount;
	_useAI = useAI;
	_turnCount = -1;
	_attackHighlight = new CellHighlight();
	_possibleMovesHighlight = new CellHighlight();

	int cellCount = _boardInfo.dimension * _boardInfo.dimension;
	_boardInfo.cells = new CellInfo[cellCount];
	memset(_boardInfo.cells, 0, sizeof(CellInfo) * cellCount);

	int swap = 0;
	for (int i = 0; i < (rowCount - 1) / 2; i++) {
		for (int j = 0; j < rowCount; j += 2) {

			BoardCords cords = { j + swap ^ 1, i };
			_boardInfo.cells[cords.y * rowCount + cords.x].notEmpty = true;
			_boardInfo.cells[cords.y * rowCount + cords.x].team = Team::second;
			_boardInfo.cells[cords.y * rowCount + cords.x].species = Species::common;
			_secondPlayerCheckers.push_back(cords);
			_checkersEntities[cords] = new PlayerChecker(Texture::black_checker, cords.y, cords.x);

			cords = { j + swap, rowCount - 1 - i };
			_boardInfo.cells[cords.y * rowCount + cords.x].notEmpty = true;
			_boardInfo.cells[cords.y * rowCount + cords.x].team = Team::first;
			_boardInfo.cells[cords.y * rowCount + cords.x].species = Species::common;
			_firstPlayerCheckers.push_back(cords);
			_checkersEntities[cords] = new PlayerChecker(Texture::white_checker, cords.y, cords.x);
		}
		swap ^= 1;
	}

	PrepareNextTurn();
}

bool Game::IsMyTurn(int x, int y)
{
	return (x >= 0) && (x < _boardInfo.dimension) && (y >= 0) && (y < _boardInfo.dimension) &&
		(_boardInfo.cells[y * _boardInfo.dimension + x].team == _turnOf);
}

void Game::ShowPossibleMoves(int x, int y)
{
	if ((x >= 0) && (y >= 0) && (x < _boardInfo.dimension) && (y < _boardInfo.dimension)) {

		std::vector<std::vector<BoardCords>> moves;
		BoardCords checker = { x, y };
		GameAlgorithms::GetMoves(_boardInfo, checker, _attackCheckers, moves);

		for (auto& move : moves) {

			int lastPositionIndex = move.size() - 1;
			for (int i = 0; i < lastPositionIndex; i++) {

				BoardCords cords = move[i];
				if (_boardInfo.cells[cords.y * _boardInfo.dimension + cords.x].notEmpty) {

					if (_boardInfo.cells[cords.y * _boardInfo.dimension + cords.x].team != _turnOf) {

						_possibleMovesHighlight->Add(Color::dark_orange, cords.x, cords.y);
					}
					else {

						_possibleMovesHighlight->Add(Color::green, cords.x, cords.y);
					}

				}
				else {

					_possibleMovesHighlight->Add(Color::yellow, cords.x, cords.y);
				}

			}

			BoardCords cords = move[lastPositionIndex];
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
	if ((x >= 0) && (y >= 0) && (x < _boardInfo.dimension) && (y < _boardInfo.dimension) &&
		(nextX >= 0) && (nextY >= 0) && (nextX < _boardInfo.dimension) && (nextY <= _boardInfo.dimension) &&
		_boardInfo.cells[y * _boardInfo.dimension + x].team == _turnOf) {

		std::vector<std::vector<BoardCords>> moves;
		BoardCords checkerCords = { x, y };
		BoardCords destCords = { nextX, nextY };
		GameAlgorithms::GetMoves(_boardInfo, checkerCords, _attackCheckers, moves);

		std::vector<BoardCords>* chosedMove = nullptr;
		for (auto& move : moves) {
			BoardCords dest = move[move.size() - 1];
			if ((dest.x == nextX) && (dest.y == nextY)) {
				chosedMove = &move;
			}
		}

		if (chosedMove != nullptr) {
			memcpy(&_boardInfo.cells[nextY * _boardInfo.dimension + nextX], &_boardInfo.cells[y * _boardInfo.dimension + x], sizeof(CellInfo));
			memset(&_boardInfo.cells[y * _boardInfo.dimension + x], 0, sizeof(CellInfo));

			(_checkersEntities[destCords] = _checkersEntities[checkerCords])->SetCords(nextX, nextY);
			_checkersEntities.erase(checkerCords);

			if (((_turnOf == Team::first) && (nextY == 0)) || (nextY == _boardInfo.dimension - 1)) {
				_boardInfo.cells[nextY * _boardInfo.dimension + nextX].species = Species::queen;
				_checkersEntities[destCords]->Crown();
			}

			BoardCords old = { x,y };
			BoardCords next = { nextX, nextY };
			auto& vec = _turnOf == Team::first ? _firstPlayerCheckers : _secondPlayerCheckers;
			auto it = std::find(vec.begin(), vec.end(), old);
			vec[it - vec.begin()] = next;

			for (BoardCords& cords : *chosedMove) {
				Team eTeam = _turnOf == Team::first ? Team::second : Team::first;
				if (_boardInfo.cells[cords.y * _boardInfo.dimension + cords.x].team == eTeam) {
					Checker* killedChecker = _checkersEntities[cords];
					delete killedChecker;
					memset(&_boardInfo.cells[cords.y * _boardInfo.dimension + cords.x], 0, sizeof(CellInfo));
					auto& eVec = eTeam == Team::first ? _firstPlayerCheckers : _secondPlayerCheckers;
					eVec.erase(std::find(eVec.begin(), eVec.end(), cords));
				}
			}

			PrepareNextTurn();
		}
	}
}

void Game::PrepareNextTurn()
{
	_turnCount++;
	_turnOf = (_turnCount % 2 == 0) ? Team::first : Team::second;

	auto& checkers = _turnOf == Team::first ? _firstPlayerCheckers : _secondPlayerCheckers;
	_attackCheckers.clear();
	GameAlgorithms::GetAttackCheckers(_boardInfo, checkers, _attackCheckers);

	HighlightAttackCheckers();
}

void Game::HighlightAttackCheckers()
{
	_attackHighlight->Clear();
	for (const BoardCords& cords : _attackCheckers) {
		_attackHighlight->Add(Color::red, cords.x, cords.y);
	}
	_attackHighlight->Show();
}


