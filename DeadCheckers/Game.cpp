#include "Game.h"

#include <string>
#include <exception>

#include "GameAlgorithms.h"
#include "PlayerChecker.h"

int counter = 0;

Game::Game() : _boardInfo()
{
	_turnCount = 0;
}

void Test1() {

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
			_boardInfo.secondPlayerCheckers.push_back(cords);
			_checkersEntities[cords] = new PlayerChecker(Texture::black_checker, cords.y, cords.x);

			cords = { j + swap, rowCount - 1 - i };
			_boardInfo.cells[cords.y * rowCount + cords.x].notEmpty = true;
			_boardInfo.cells[cords.y * rowCount + cords.x].team = Team::first;
			_boardInfo.cells[cords.y * rowCount + cords.x].species = Species::common;
			_boardInfo.firstPlayerCheckers.push_back(cords);
			_checkersEntities[cords] = new PlayerChecker(Texture::white_checker, cords.y, cords.x);
		}
		swap ^= 1;
	}

	////Test 1
	//BoardCords cords = { 6, 0 };
	//_boardInfo.cells[cords.y * rowCount + cords.x].notEmpty = true;
	//_boardInfo.cells[cords.y * rowCount + cords.x].team = Team::first;
	//_boardInfo.cells[cords.y * rowCount + cords.x].species = Species::queen;
	//_boardInfo.firstPlayerCheckers.push_back(cords);
	//_checkersEntities[cords] = new PlayerChecker(Texture::white_checker, cords.y, cords.x);

	//cords = { 4, 2 };
	//_boardInfo.cells[cords.y * rowCount + cords.x].notEmpty = true;
	//_boardInfo.cells[cords.y * rowCount + cords.x].team = Team::second;
	//_boardInfo.cells[cords.y * rowCount + cords.x].species = Species::queen;
	//_boardInfo.secondPlayerCheckers.push_back(cords);
	//_checkersEntities[cords] = new PlayerChecker(Texture::black_checker, cords.y, cords.x);

	//cords = { 5, 5 };
	//_boardInfo.cells[cords.y * rowCount + cords.x].notEmpty = true;
	//_boardInfo.cells[cords.y * rowCount + cords.x].team = Team::second;
	//_boardInfo.cells[cords.y * rowCount + cords.x].species = Species::queen;
	//_boardInfo.secondPlayerCheckers.push_back(cords);
	//_checkersEntities[cords] = new PlayerChecker(Texture::black_checker, cords.y, cords.x);

	//cords = { 1, 1 };
	//_boardInfo.cells[cords.y * rowCount + cords.x].notEmpty = true;
	//_boardInfo.cells[cords.y * rowCount + cords.x].team = Team::second;
	//_boardInfo.cells[cords.y * rowCount + cords.x].species = Species::queen;
	//_boardInfo.secondPlayerCheckers.push_back(cords);
	//_checkersEntities[cords] = new PlayerChecker(Texture::black_checker, cords.y, cords.x);

	////Test 2
	//BoardCords cords = { 4, 4 };
	//_boardInfo.cells[cords.y * rowCount + cords.x].notEmpty = true;
	//_boardInfo.cells[cords.y * rowCount + cords.x].team = Team::first;
	//_boardInfo.cells[cords.y * rowCount + cords.x].species = Species::common;
	//_boardInfo.firstPlayerCheckers.push_back(cords);
	//_checkersEntities[cords] = new PlayerChecker(Texture::white_checker, cords.y, cords.x);

	//cords = { 5, 5 };
	//_boardInfo.cells[cords.y * rowCount + cords.x].notEmpty = true;
	//_boardInfo.cells[cords.y * rowCount + cords.x].team = Team::second;
	//_boardInfo.cells[cords.y * rowCount + cords.x].species = Species::common;
	//_boardInfo.secondPlayerCheckers.push_back(cords);
	//_checkersEntities[cords] = new PlayerChecker(Texture::black_checker, cords.y, cords.x);

	//cords = { 1, 1 };
	//_boardInfo.cells[cords.y * rowCount + cords.x].notEmpty = true;
	//_boardInfo.cells[cords.y * rowCount + cords.x].team = Team::second;
	//_boardInfo.cells[cords.y * rowCount + cords.x].species = Species::common;
	//_boardInfo.secondPlayerCheckers.push_back(cords);
	//_checkersEntities[cords] = new PlayerChecker(Texture::black_checker, cords.y, cords.x);



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
		GameAlgorithms::GetMoves(_boardInfo, checker, moves);

		for (auto& move : moves) {

			for (int i = 0; i < move.size() - 1; i++) {

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

			BoardCords cords = move[move.size() - 1];
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
		BoardCords currentCords = { x, y };
		BoardCords nextCords = { nextX, nextY };
		GameAlgorithms::GetMoves(_boardInfo, currentCords, moves);

		std::vector<BoardCords>* chosedMove = nullptr;
		for (auto& move : moves) {
			BoardCords dest = move[move.size() - 1];
			if ((dest.x == nextX) && (dest.y == nextY)) {
				chosedMove = &move;
				break;
			}
		}

		if (chosedMove != nullptr) {

			bool wasQueen = _boardInfo.cells[y * _boardInfo.dimension + x].species == Species::queen;
			std::vector<BoardCords> removedCheckers;

			GameAlgorithms::ApplyMove(_boardInfo, *chosedMove, removedCheckers);

			(_checkersEntities[nextCords] = _checkersEntities[currentCords])->SetCords(nextX, nextY);
			if (!(currentCords == nextCords)) {
				_checkersEntities.erase(currentCords);
			}

			if ((_boardInfo.cells[nextY * _boardInfo.dimension + nextX].species == Species::queen) != wasQueen) {
				_checkersEntities[nextCords]->Crown();
			}

			for (BoardCords& cords : removedCheckers) {
				delete _checkersEntities[cords];
				_checkersEntities.erase(cords);
			}

			PrepareNextTurn();
		}
	}
}

void Game::PrepareNextTurn()
{
	_turnCount++;
	_turnOf = (_turnCount % 2 == 0) ? Team::first : Team::second;

	if (_useAI && (_turnOf == Team::second)) {
		_attackHighlight->Clear();
		UseAI();
	}
	else {
		HighlightAttackCheckers();
	}

	
}

void Game::HighlightAttackCheckers()
{
	_attackHighlight->Clear();
	std::vector<BoardCords> attackCheckers;
	auto& checkers = _turnOf == Team::first ? _boardInfo.firstPlayerCheckers : _boardInfo.secondPlayerCheckers;
	GameAlgorithms::GetAttackCheckers(_boardInfo, checkers, attackCheckers);
	for (const BoardCords& cords : attackCheckers) {
		_attackHighlight->Add(Color::red, cords.x, cords.y);
	}
	_attackHighlight->Show();
}

void Game::PrepareForRestart()
{
	delete _attackHighlight;
	delete _possibleMovesHighlight;

	delete _boardInfo.cells;
	_boardInfo.firstPlayerCheckers.clear();
	_boardInfo.secondPlayerCheckers.clear();

	for (auto& kv : _checkersEntities) {
		delete kv.second;
	}
	_checkersEntities.clear();
}

void Game::UseAI()
{
	AITurn turn = UseAI(4, _turnOf, _turnOf);
	TryMakeMove(turn.start.x, turn.start.y, turn.end.x, turn.end.y);
}

void Game::Restart()
{
	PrepareForRestart();
	Start(_boardInfo.dimension, _useAI);
}

void Game::SwitchSecondPlayerMode()
{
	_useAI = !_useAI;
}

AITurn Game::UseAI(int depth, Team turnOf, Team countFor)
{
	std::vector<BoardCords> attackCheckers;
	Team eTeam = turnOf == Team::first ? Team::second : Team::first;
	auto& checkers = turnOf == Team::first ? _boardInfo.firstPlayerCheckers : _boardInfo.secondPlayerCheckers;
	auto& eCheckers = turnOf == Team::first ? _boardInfo.secondPlayerCheckers : _boardInfo.firstPlayerCheckers;

	GameAlgorithms::GetAttackCheckers(_boardInfo, checkers, attackCheckers);

	std::vector<std::vector<BoardCords>> moves;
	std::vector<CellInfoWithCords> moveHistory;
	std::vector<BoardCords> removedCheckers;

	auto searchFunc = attackCheckers.size() ? GameAlgorithms::GetAttackingMoves : GameAlgorithms::GetNonAttackingMoves;
	auto& checkersForTest = attackCheckers.size() ? attackCheckers : checkers;

	AITurn result;

	if (turnOf == countFor) {
		result.minmax = -9999999;
	}
	else {
		result.minmax = 9999999;
	}
	

	for (BoardCords& checker : checkersForTest) {

		counter++;

		if (counter >= 0x00010355) {
			counter++;
		}

		moves.clear();
		searchFunc(_boardInfo, checker, moves);

		

		for (auto& move : moves) {

			moveHistory.clear();
			removedCheckers.clear();

			AITurn current;
			current.start = move[0];
			current.end = move[move.size() - 1];

			//TestCode 
			if (move.size() == 1) {
				counter++;
			}

			//TestCode
			for (BoardCords& cellInfo : _boardInfo.firstPlayerCheckers) {
				if (_boardInfo.cells[cellInfo.y * _boardInfo.dimension + cellInfo.x].team != Team::first) {
					counter++;
				}
			}

			GameAlgorithms::ApplyMoveWithHistory(_boardInfo, move, moveHistory, removedCheckers);

			//TestCode
			for (BoardCords& cellInfo : _boardInfo.firstPlayerCheckers) {
				if (_boardInfo.cells[cellInfo.y * _boardInfo.dimension + cellInfo.x].team != Team::first) {
					counter++;
				}
			}

			if ((depth == 0) || (!(checkers.size() && eCheckers.size()))) {

				if (turnOf == countFor) {
					current.minmax = (int)(checkers.size() - eCheckers.size());
				}
				else {
					current.minmax = (int)(eCheckers.size() - checkers.size());
				}

			}
			else {
				current.minmax = UseAI(depth - 1, eTeam, countFor).minmax;
			}

			if (turnOf == countFor) {
				if (current.minmax > result.minmax) {
					result = current;
				}
			}
			else {
				if (current.minmax < result.minmax) {
					result = current;
				}
			}
			

			GameAlgorithms::RollBack(_boardInfo, moveHistory, removedCheckers, current.start, current.end, turnOf);

		}
	}

	return result;
}


