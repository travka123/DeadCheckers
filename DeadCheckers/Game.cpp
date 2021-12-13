#include "Game.h"

#include <string>
#include <exception>

#include "PlayerChecker.h"

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
	_firstPlayerCheckers = new std::vector<CellCords>;
	_secondPlayerCheckers = new std::vector<CellCords>;
	/*for (int i = 0; i < (rowCount - 1) / 2; i++) {
		for (int j = 0; j < rowCount; j += 2) {

			CellCords cords = { j + swap ^ 1, i };
			_boardInfo[cords.y * rowCount + cords.x].checker = new PlayerChecker(Texture::black_checker, cords.y, cords.x);
			_boardInfo[cords.y * rowCount + cords.x].team = Team::black;
			_secondPlayerCheckers->push_back(cords);

			cords = { j + swap, rowCount - 1 - i };
			_boardInfo[cords.y * rowCount + cords.x].checker = new PlayerChecker(Texture::white_checker, cords.y, cords.x);
			_boardInfo[cords.y * rowCount + cords.x].team = Team::first;
			_firstPlayerCheckers->push_back(cords);
		}
		swap ^= 1;
	}*/

	CellCords cords = { 4, 4 };
	_boardInfo[cords.y * rowCount + cords.x].checker = new PlayerChecker(Texture::white_checker, 4, 4);
	_boardInfo[cords.y * rowCount + cords.x].team = Team::first;
	_boardInfo[cords.y * rowCount + cords.x].notEmpty = true;
	_firstPlayerCheckers->push_back(cords);

	cords = { 3, 3 };
	_boardInfo[cords.y * rowCount + cords.x].checker = new PlayerChecker(Texture::black_checker, 3, 3);
	_boardInfo[cords.y * rowCount + cords.x].team = Team::black;
	_boardInfo[cords.y * rowCount + cords.x].notEmpty = true;
	_secondPlayerCheckers->push_back(cords);

	_turnOf = Team::first;

	_attackHighlight = new CellHighlight();

	Prepare();
}

bool Game::IsMyTurn(int x, int y)
{
	return (x >= 0) && (x < _rowCount) && (y >= 0) && (y < _rowCount) &&
		(_boardInfo[y * _rowCount + x].team == _turnOf);
}

void Game::Prepare()
{
	CollectAttackCheckers();
	HighlightIfAttack();
}

void Game::HighlightIfAttack()
{
	for (CellCords& cords : _attackCheckers) {
		HighlightInfo info = { Color::red, cords.x, cords.y };
		_attackHighlight->Add(info);
	}
	_attackHighlight->Show();
}

void Game::CollectAttackCheckers()
{
	_attackCheckers.clear();
	auto* vec = _turnOf == Team::first ? _firstPlayerCheckers : _secondPlayerCheckers;
	for (CellCords cords : *vec) {
		if ((cords.x - 2 >= 0) && (cords.y - 2 >= 0) && 
			(_boardInfo[(cords.y - 1) * _rowCount + cords.x - 1].notEmpty) &&
			(_boardInfo[(cords.y - 1) * _rowCount + cords.x - 1].team != _turnOf) && 
			(!_boardInfo[(cords.y - 2) * _rowCount + cords.x - 2].notEmpty)) {
			_attackCheckers.push_back(cords);
		}
	}
}
