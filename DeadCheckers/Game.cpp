#include "Game.h"

#include <string>
#include <exception>

#include "PlayerChecker.h"

Game::Game(int rowCount) {

	if (rowCount % 2 == 1) {
		throw std::exception();
	}

	_rowCellCount = rowCount;
	_boardCellCount = rowCount * rowCount;

	_board = new int[_boardCellCount];
	memset(_board, 0, sizeof(int) * _boardCellCount);

	int checkersInRow = rowCount / 2;
	int verticalTeamRowCount = (rowCount - 1) / 2;
	int teamCheckersCount = verticalTeamRowCount * checkersInRow;
	
	_blackCheckers = new Checker * [teamCheckersCount];
	_whiteCheckers = new Checker * [teamCheckersCount];

	int swap = 1;
	int pos = 0;
	
	for (int i = 0; i < verticalTeamRowCount; i++) {
		for (int j = 0; j < checkersInRow; j++) {
			_blackCheckers[pos] = new PlayerChecker(Texture::black_checker, i, j * 2 + swap);
			_whiteCheckers[pos] = new Checker(Texture::white_checker, rowCount - 1 - i, j * 2 + (swap ^ 1));
			pos++;
		}
		swap ^= 1;
	}
}