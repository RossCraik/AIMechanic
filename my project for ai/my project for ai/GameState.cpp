#include "GameState.h"
#include <cstddef>
#include <iostream>


GameState::GameState()
{

}

/**
* setAndApplyAction will update the game state with the provided action and update the game board
*/
void GameState::setAndApplyAction(GameAction newAction)
{
	gameAction = newAction;

	// update the board
	gameBoard.board[newAction.x][newAction.y] = newAction.playerMove;

}


/**
* setAndApplyAction will return all possible moves from the stored board state
*/
std::vector<std::pair<int, int>> GameState::getPossibleMoves()
{
	std::vector<std::pair<int, int>> possibleMoves;
	int y;
	
	for (int x = 0; x < 7; x++)
	{
		y = getLowestOfRow(x);

		if (gameBoard.board[x][y] == BOARD_SQUARE_STATE::NONE)
		{
			// if currently empty,add to possible moves
			possibleMoves.push_back(std::make_pair(x, y));
		}
	}
	

	return possibleMoves;
}

/**
* getCharForState will return a character to represent each BOARD_SQUARE_STATE
*/
char getCharForState(BOARD_SQUARE_STATE printState)
{
	// Print characters for specific states
	switch (printState)
	{
	case BOARD_SQUARE_STATE::NONE:
		return '.';
	case BOARD_SQUARE_STATE::CROSS:
		return 'X';
	case BOARD_SQUARE_STATE::CIRCLE:
		return 'O';
	}

	return ' ';
}




/**
* printBoard will output the current game state to the command line
*/
void GameState::printBoard() {
	for (int y = 0; y < 6; y++)
	{
		for (int x = 0; x < 7; x++)
		{
			std::cout << " " << getCharForState(gameBoard.board[x][y]);
		}
		std::cout << std::endl;
	}

}


int GameState::getLowestOfRow(int x)
{
	int y = 5;

	for (int i = 0; i < 6; i++)
	{
		if (gameBoard.board[x][y] != BOARD_SQUARE_STATE::NONE)
		{
			y--;
		}
	}
	
	return y;
}



/**
* checkWin will check if the stored board state is a winning one for either marker
*/

BOARD_SQUARE_STATE GameState::checkWin()
{


	//checking row
	for (int y = 0; y < 6; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (
				gameBoard.board[x][y] != BOARD_SQUARE_STATE::NONE &&
				gameBoard.board[x][y] == gameBoard.board[x + 1][y] &&
				gameBoard.board[x][y] == gameBoard.board[x + 2][y] &&
				gameBoard.board[x][y] == gameBoard.board[x + 3][y]
				)
			{
				return gameBoard.board[x][y];
			}
		}
	}

	//checking column
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 7; x++)
		{
			if (
				gameBoard.board[x][y] != BOARD_SQUARE_STATE::NONE &&
				gameBoard.board[x][y] == gameBoard.board[x][y + 1] &&
				gameBoard.board[x][y] == gameBoard.board[x][y + 2] &&
				gameBoard.board[x][y] == gameBoard.board[x][y + 3]
				)
			{
				return gameBoard.board[x][y];
			}
		}
	}


	// Check first diagonal
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (
				gameBoard.board[x][y] != BOARD_SQUARE_STATE::NONE &&
				gameBoard.board[x][y] == gameBoard.board[x + 1][y + 1] &&
				gameBoard.board[x][y] == gameBoard.board[x + 2][y + 2] &&
				gameBoard.board[x][y] == gameBoard.board[x + 3][y + 3]
				)
			{
				return gameBoard.board[x][y];
			}
		}
	}

	// Check second diagonal
	for (int y = 3; y < 6; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (
				gameBoard.board[x][y] != BOARD_SQUARE_STATE::NONE &&
				gameBoard.board[x][y] == gameBoard.board[x + 1][y - 1] &&
				gameBoard.board[x][y] == gameBoard.board[x + 2][y - 2] &&
				gameBoard.board[x][y] == gameBoard.board[x + 3][y - 3]
				)
			{
				return gameBoard.board[x][y];
			}
		}
	}

	





	// If no-one wins return the default state
	return BOARD_SQUARE_STATE::NONE;
}


bool GameState::checkForPlayerWin(int x, int y)
{

	
	//checking row
	if (
		x < 4 &&
		gameBoard.board[x + 1][y] == BOARD_SQUARE_STATE::CIRCLE &&
		gameBoard.board[x + 2][y] == BOARD_SQUARE_STATE::CIRCLE &&
		gameBoard.board[x + 3][y] == BOARD_SQUARE_STATE::CIRCLE &&
		gameBoard.board[x][y + 1] != BOARD_SQUARE_STATE::NONE
		
		)
	{
		return true;
	}

	if (
		x < 5 &&
		gameBoard.board[x - 1][y] == BOARD_SQUARE_STATE::CIRCLE &&
		gameBoard.board[x + 1][y] == BOARD_SQUARE_STATE::CIRCLE &&
		gameBoard.board[x + 2][y] == BOARD_SQUARE_STATE::CIRCLE &&
		gameBoard.board[x][y + 1] != BOARD_SQUARE_STATE::NONE

		)
	{
		return true;
	}

	if (
		x > 1 &&
		gameBoard.board[x - 1][y] == BOARD_SQUARE_STATE::CIRCLE &&
		gameBoard.board[x - 2][y] == BOARD_SQUARE_STATE::CIRCLE &&
		gameBoard.board[x + 1][y] == BOARD_SQUARE_STATE::CIRCLE &&
		gameBoard.board[x][y + 1] != BOARD_SQUARE_STATE::NONE

		)
	{
		return true;
	}
	
	if (
		x > 2 &&
		gameBoard.board[x - 1][y] == BOARD_SQUARE_STATE::CIRCLE &&
		gameBoard.board[x - 2][y] == BOARD_SQUARE_STATE::CIRCLE &&
		gameBoard.board[x - 3][y] == BOARD_SQUARE_STATE::CIRCLE &&
		gameBoard.board[x][y + 1] != BOARD_SQUARE_STATE::NONE

		)
	{
		return true;
	}


	//checking column
	
	if (
		y < 3 &&
		gameBoard.board[x][y + 1] == BOARD_SQUARE_STATE::CIRCLE &&
		gameBoard.board[x][y + 2] == BOARD_SQUARE_STATE::CIRCLE &&
		gameBoard.board[x][y + 3] == BOARD_SQUARE_STATE::CIRCLE
		)
	{
		return true;
	}
		
	if (
		y > 2 &&
		gameBoard.board[x][y - 1] == BOARD_SQUARE_STATE::CIRCLE &&
		gameBoard.board[x][y - 2] == BOARD_SQUARE_STATE::CIRCLE &&
		gameBoard.board[x][y - 3] == BOARD_SQUARE_STATE::CIRCLE
		)
	{
		return true;
	}



	// Check first diagonal
	
	if (
		x < 4 && y < 3 && 
		gameBoard.board[x + 1][y + 1] == BOARD_SQUARE_STATE::CIRCLE &&
		gameBoard.board[x + 2][y + 2] == BOARD_SQUARE_STATE::CIRCLE &&
		gameBoard.board[x + 3][y + 3] == BOARD_SQUARE_STATE::CIRCLE &&
		gameBoard.board[x][y + 1] != BOARD_SQUARE_STATE::NONE
		)
	{
		return true;
	}

	if (
		x > 2 && y > 2 &&
		gameBoard.board[x - 1][y - 1] == BOARD_SQUARE_STATE::CIRCLE &&
		gameBoard.board[x - 2][y - 2] == BOARD_SQUARE_STATE::CIRCLE &&
		gameBoard.board[x - 3][y - 3] == BOARD_SQUARE_STATE::CIRCLE &&
		gameBoard.board[x][y + 1] != BOARD_SQUARE_STATE::NONE
		)
	{
		return true;
	}


	if (
		x < 5 && y < 4 &&
		gameBoard.board[x - 1][y - 1] == BOARD_SQUARE_STATE::CIRCLE &&
		gameBoard.board[x + 1][y + 1] == BOARD_SQUARE_STATE::CIRCLE &&
		gameBoard.board[x + 2][y + 2] == BOARD_SQUARE_STATE::CIRCLE &&
		gameBoard.board[x][y + 1] != BOARD_SQUARE_STATE::NONE
		)
	{
		return true;
	}

	if (
		x > 1 && y > 1 &&
		gameBoard.board[x + 1][y + 1] == BOARD_SQUARE_STATE::CIRCLE &&
		gameBoard.board[x - 1][y - 1] == BOARD_SQUARE_STATE::CIRCLE &&
		gameBoard.board[x - 2][y - 2] == BOARD_SQUARE_STATE::CIRCLE &&
		gameBoard.board[x][y + 1] != BOARD_SQUARE_STATE::NONE
		)
	{
		return true;
	}

	//checking second diagonal

	if (
		x < 4 && y > 2 &&
		gameBoard.board[x + 1][y - 1] == BOARD_SQUARE_STATE::CIRCLE &&
		gameBoard.board[x + 2][y - 2] == BOARD_SQUARE_STATE::CIRCLE &&
		gameBoard.board[x + 3][y - 3] == BOARD_SQUARE_STATE::CIRCLE &&
		gameBoard.board[x][y + 1] != BOARD_SQUARE_STATE::NONE
		)
	{
		return true;
	}

	if (
		x > 2 && y < 3 &&
		gameBoard.board[x - 1][y + 1] == BOARD_SQUARE_STATE::CIRCLE &&
		gameBoard.board[x - 2][y + 2] == BOARD_SQUARE_STATE::CIRCLE &&
		gameBoard.board[x - 3][y + 3] == BOARD_SQUARE_STATE::CIRCLE &&
		gameBoard.board[x][y + 1] != BOARD_SQUARE_STATE::NONE
		)
	{
		return true;
	}

	if (
		x < 5 && y > 1 &&
		gameBoard.board[x - 1][y + 1] == BOARD_SQUARE_STATE::CIRCLE &&
		gameBoard.board[x + 1][y - 1] == BOARD_SQUARE_STATE::CIRCLE &&
		gameBoard.board[x + 2][y - 2] == BOARD_SQUARE_STATE::CIRCLE &&
		gameBoard.board[x][y + 1] != BOARD_SQUARE_STATE::NONE
		)
	{
		return true;
	}

	if (
		x > 1 && y < 4 &&
		gameBoard.board[x - 1][y + 1] == BOARD_SQUARE_STATE::CIRCLE &&
		gameBoard.board[x - 2][y + 2] == BOARD_SQUARE_STATE::CIRCLE &&
		gameBoard.board[x + 1][y - 1] == BOARD_SQUARE_STATE::CIRCLE &&
		gameBoard.board[x][y + 1] != BOARD_SQUARE_STATE::NONE
		)
	{
		return true;
	}

	return false;
}
