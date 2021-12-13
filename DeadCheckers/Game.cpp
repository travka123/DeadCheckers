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
	int teamCheckersCount = 0;
	for (int i = 0; i < (rowCount - 1) / 2; i++) {
		for (int j = 0; j < rowCount; j += 2) {

			_boardInfo[i * rowCount + j + swap ^ 1].checker = new PlayerChecker(Texture::black_checker, i, j + swap ^ 1);
			_boardInfo[i * rowCount + j + swap ^ 1].team = Team::black;

			int k = rowCount - 1 - i;
			_boardInfo[k * rowCount + j + swap].checker = new PlayerChecker(Texture::white_checker, k, j + swap);
			_boardInfo[k * rowCount + j + swap].team = Team::white;

			teamCheckersCount++;
		}
		swap ^= 1;
	}

	_turnOf = Team::white;
}

bool Game::IsMyTurn(int x, int y)
{
	return (x >= 0) && (x < _rowCount) && (y >= 0) && (y < _rowCount) &&
		(_boardInfo[y * _rowCount + x].team == _turnOf);
}
