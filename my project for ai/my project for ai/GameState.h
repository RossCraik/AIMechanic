
#pragma once

#include "GameBoard.h"
#include <vector>

class GameState
{
public:
	GameBoard gameBoard;
	GameAction gameAction;

	GameState();

	void setAndApplyAction(GameAction newAction);
	std::vector<std::pair<int, int>> getPossibleMoves();
	void printBoard();
	int getLowestOfRow(int x);
	BOARD_SQUARE_STATE checkWin();

	bool checkForPlayerWin(int x, int y);

};

