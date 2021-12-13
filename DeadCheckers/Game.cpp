#include "Game.h"

#include <string>
#include <exception>

#include "PlayerChecker.h"

Game::Game() : _firstPlayerCheckers(), _secondPlayerCheckers()
{
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

	int swap = 0;
	for (int i = 0; i < (rowCount - 1) / 2; i++) {
		for (int j = 0; j < rowCount; j += 2) {

			CellCords cords = { j + swap ^ 1, i };
			_boardInfo[cords.y * rowCount + cords.x].checker = new PlayerChecker(Texture::black_checker, cords.y, cords.x);
			_boardInfo[cords.y * rowCount + cords.x].team = Team::black;
			_boardInfo[cords.y * rowCount + cords.x].notEmpty = true;
			_secondPlayerCheckers.push_back(cords);

			cords = { j + swap, rowCount - 1 - i };
			_boardInfo[cords.y * rowCount + cords.x].checker = new PlayerChecker(Texture::white_checker, cords.y, cords.x);
			_boardInfo[cords.y * rowCount + cords.x].team = Team::first;
			_boardInfo[cords.y * rowCount + cords.x].notEmpty = true;
			_firstPlayerCheckers.push_back(cords);
		}
		swap ^= 1;
	}

	/*CellCords cords = { 4, 4 };
	_boardInfo[cords.y * rowCount + cords.x].checker = new PlayerChecker(Texture::white_checker, 4, 4);
	_boardInfo[cords.y * rowCount + cords.x].team = Team::first;
	_boardInfo[cords.y * rowCount + cords.x].notEmpty = true;
	_firstPlayerCheckers->push_back(cords);

	cords = { 3, 3 };
	_boardInfo[cords.y * rowCount + cords.x].checker = new PlayerChecker(Texture::black_checker, 3, 3);
	_boardInfo[cords.y * rowCount + cords.x].team = Team::black;
	_boardInfo[cords.y * rowCount + cords.x].notEmpty = true;
	_secondPlayerCheckers->push_back(cords);*/

	_turnOf = Team::first;

	_attackHighlight = new CellHighlight();
	_possibleMovesHighlight = new CellHighlight();

	Prepare();
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
		_possibleMovesHighlight->Add(Color::green, x, y);
		for (auto& move : moves) {
			int endIndex = move.size() - 1;
			for (int i = 0; i < endIndex; i++) {
				CellCords cords = move[i];
				_possibleMovesHighlight->Add(Color::green, cords.x, cords.y);
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
		}
	}
}

void Game::Prepare()
{
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
		if ((cords.x - 2 >= 0) && (cords.y - 2 >= 0) &&
			(_boardInfo[(cords.y - 1) * _rowCount + cords.x - 1].notEmpty) &&
			(_boardInfo[(cords.y - 1) * _rowCount + cords.x - 1].team != _turnOf) &&
			(!_boardInfo[(cords.y - 2) * _rowCount + cords.x - 2].notEmpty)) {
			_attackCheckers.push_back(cords);
		}
		else if ((cords.x + 2 < _rowCount) && (cords.y - 2 >= 0) &&
			(_boardInfo[(cords.y - 1) * _rowCount + cords.x + 1].notEmpty) &&
			(_boardInfo[(cords.y - 1) * _rowCount + cords.x + 1].team != _turnOf) &&
			(!_boardInfo[(cords.y - 2) * _rowCount + cords.x + 2].notEmpty)) {
			_attackCheckers.push_back(cords);
		}
		else if ((cords.x - 2 >= 0) && (cords.y + 2 < _rowCount) &&
			(_boardInfo[(cords.y + 1) * _rowCount + cords.x - 1].notEmpty) &&
			(_boardInfo[(cords.y + 1) * _rowCount + cords.x - 1].team != _turnOf) &&
			(!_boardInfo[(cords.y + 2) * _rowCount + cords.x - 2].notEmpty)) {
			_attackCheckers.push_back(cords);
		}
		else if ((cords.x + 2 < _rowCount) && (cords.y + 2 < _rowCount) &&
			(_boardInfo[(cords.y + 1) * _rowCount + cords.x + 1].notEmpty) &&
			(_boardInfo[(cords.y + 1) * _rowCount + cords.x + 1].team != _turnOf) &&
			(!_boardInfo[(cords.y + 2) * _rowCount + cords.x + 2].notEmpty)) {
			_attackCheckers.push_back(cords);
		}
	}
}

void Game::GetPossibleMoves(std::vector<std::vector<CellCords>>& moves, int x, int y)
{
	int direction = _turnOf == Team::first ? -1 : 1;

	if (_attackCheckers.size() == 0) {
		if ((y + direction < _rowCount) && (y + direction >= 0) && (x - 1 >= 0) && (!_boardInfo[(y + direction) * _rowCount + (x - 1)].notEmpty)) {
			CellCords cords = { x - 1, y + direction };
			std::vector<CellCords> move;
			move.push_back(cords);
			moves.push_back(move);
		}
		if ((y + direction < _rowCount) && (y + direction >= 0) && (x + 1 < _rowCount) && (!_boardInfo[(y + direction) * _rowCount + (x + 1)].notEmpty)) {
			CellCords cords = { x + 1, y + direction };
			std::vector<CellCords> move;
			move.push_back(cords);
			moves.push_back(move);
		}
	}
}
