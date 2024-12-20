#pragma once

#include <vector>
#include <stack>
#include "GameBoard.h"
#include "GameState.h"

class Connect4Node
{
public:
	Connect4Node();
	~Connect4Node();


	//gets and sets
	void setGameState(GameState newState);
	GameState getGameState() { return worldState; }

	bool getIsEndState() { return isEndState; }
	std::vector<Connect4Node*> getBranches() { return branches; }
	int getRanking() { return ranking; }

	void setActivePlayer(BOARD_SQUARE_STATE active) { activePlayer = active; }
	BOARD_SQUARE_STATE getActivePlayer() { return activePlayer; }

	void setParent(Connect4Node* newParent) { parent = newParent; }


	// MCTS steps
	Connect4Node* Select();
	Connect4Node* Expand();
	void Simulate(BOARD_SQUARE_STATE playerTurn);
	void Backpropagate(int reward);

	int getX();

	// tree functions
	Connect4Node* FindHighestRankingChild(bool report);
	void resetNode();
	void CalcResult(BOARD_SQUARE_STATE winner);
	


private:
	int ranking; // ranking is updated via back propagation
	std::vector<Connect4Node*> branches; // child nodes
	Connect4Node* parent; // parent node
	GameState worldState; // game state at this node
	bool isEndState; // if eitehr game is won or no moves possible
	std::vector<std::pair<int, int>> availableMoves; // unexplored branches
	BOARD_SQUARE_STATE activePlayer; // the player who moved to create this state - child nodes should use opposite marker
	int visits = 0;

	void generatePossibleMoves();
};

