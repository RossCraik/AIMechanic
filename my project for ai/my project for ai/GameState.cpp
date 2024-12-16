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

	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			if (gameBoard.board[i][j] == BOARD_SQUARE_STATE::NONE)
			{
				// if currently empty,add to possible moves
				possibleMoves.push_back(std::make_pair(i, j));
			}
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
	for (int j = 0; j < 6; j++)
	{
		for (int i = 0; i < 7; i++)
		{
			std::cout << " " << getCharForState(gameBoard.board[j][i]);
		}
		std::cout << std::endl;
	}

}



/**
* checkWin will check if the stored board state is a winning one for either marker
*/

BOARD_SQUARE_STATE GameState::checkWin()
{


	//checking row
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (
				gameBoard.board[i][j] != BOARD_SQUARE_STATE::NONE &&
				gameBoard.board[i][j] == gameBoard.board[i][j + 1] &&
				gameBoard.board[i][j] == gameBoard.board[i][j + 2] &&
				gameBoard.board[i][j] == gameBoard.board[i][j + 3]
				)
			{
				return gameBoard.board[i][j];
			}
		}
	}

	//checking column
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (
				gameBoard.board[i][j] != BOARD_SQUARE_STATE::NONE &&
				gameBoard.board[i][j] == gameBoard.board[i + 1][j] &&
				gameBoard.board[i][j] == gameBoard.board[i + 2][j] &&
				gameBoard.board[i][j] == gameBoard.board[i + 3][j]
				)
			{
				return gameBoard.board[i][j];
			}
		}
	}


	// Check first diagonal
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (
				gameBoard.board[i][j] != BOARD_SQUARE_STATE::NONE &&
				gameBoard.board[i][j] == gameBoard.board[i + 1][j + 1] &&
				gameBoard.board[i][j] == gameBoard.board[i + 2][j + 2] &&
				gameBoard.board[i][j] == gameBoard.board[i + 3][j + 3]
				)
			{
				return gameBoard.board[i][j];
			}
		}
	}

	// Check second diagonal
	for (int i = 3; i < 6; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (
				gameBoard.board[i][j] != BOARD_SQUARE_STATE::NONE &&
				gameBoard.board[i][j] == gameBoard.board[i - 1][j + 1] &&
				gameBoard.board[i][j] == gameBoard.board[i - 2][j + 2] &&
				gameBoard.board[i][j] == gameBoard.board[i - 3][j + 3]
				)
			{
				return gameBoard.board[i][j];
			}
		}
	}

	





	// If no-one wins return the default state
	return BOARD_SQUARE_STATE::NONE;
}