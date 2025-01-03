#pragma once

#include <iostream>
#include "GameBoard.h"
#include "Connect4Node.h"
using namespace std;

const int MAX_RUNS = 5000;
bool first = true;

bool validatePosition(int x, GameState gameState)
{
    if (x < 0 || x >6)
    {
        cout << "Invlid X: Enter 0-5" << endl;
        return false;
    }


    if (gameState.gameBoard.board[x][0] != BOARD_SQUARE_STATE::NONE)
    {
        cout << "Invlid Move: Select Empty Position" << endl;
        return false;
    }

    return true;
}



int main()
{

    cout << "*** Connect 4 ***" << endl;

    // define the markers used by the AI and the player
    BOARD_SQUARE_STATE aiMarker = BOARD_SQUARE_STATE::CROSS;
    BOARD_SQUARE_STATE playerMarker = BOARD_SQUARE_STATE::CIRCLE;

    // creeate the initial board and root node for the tree
    GameState mainGameState;
    Connect4Node* rootNode = new Connect4Node();



    bool gameOver = false;

    do {

        cout << "AI is thinking...." << endl;
        rootNode->setActivePlayer(playerMarker); // the AI will move first from empty state
        rootNode->setGameState(mainGameState);

        // define a cmount
        int runCount = 0;

        Connect4Node* aiBlock = NULL;

        // Apply the MCTS algorithm to determine the AI's move
        // - will run for maximum of MAX_RUNS iterations
        do {

            // Select - choose a node that will be expanded
            Connect4Node* selectedNode = rootNode->Select();

            if (mainGameState.checkForPlayerWin(selectedNode->getGameState().gameAction.x, selectedNode->getGameState().gameAction.y))
            {
                aiBlock = selectedNode;
            }

            
            
            // Expand - expand the tree from this node
            Connect4Node* expandedNode = selectedNode->Expand();

            // expandedNode will be NULL if it's a leaf node and simulation is not possible
            if (!expandedNode == NULL)
            {
                // Simulate & Backpropagate - Simulate to an end point, startin with aiMarker turn. 
                //  - then back propagate the result to the root node
                expandedNode->Simulate(aiMarker);
            }
            


            

            runCount++;

        } while (runCount < MAX_RUNS);

        GameAction bestAction;
        GameState copy = mainGameState;
        copy.setAndApplyAction(rootNode->FindHighestRankingChild(true)->getGameState().gameAction);

        if (aiBlock != NULL && !copy.checkWin())
        {
            bestAction = aiBlock->getGameState().gameAction;
            bestAction.playerMove = aiMarker;
        }
        else if (first)
        {
            bestAction = GameAction(3, 5, aiMarker);
        }
        else
        {
            // perform the action - find child node with highest ranking
            Connect4Node* highestChild = rootNode->FindHighestRankingChild(true);
            bestAction = highestChild->getGameState().gameAction;
            bestAction.playerMove = aiMarker;
        }

        

        
        
        std::cout << "The AI selected move is " << bestAction.x << " " << bestAction.y << std::endl;

        // update the main main state with the AI's move
        mainGameState.setAndApplyAction(bestAction);
        mainGameState.printBoard();


        // check to see if the AI's move won the match
        // if so, game's over
        BOARD_SQUARE_STATE winner = mainGameState.checkWin();

        if (winner == BOARD_SQUARE_STATE::CIRCLE)
        {
            gameOver = true;
            cout << "CIRCLE WINS!" << endl;
            break;
        }
        else  if (winner == BOARD_SQUARE_STATE::CROSS)
        {
            gameOver = true;
            cout << "CROSS WINS!" << endl;
            break;
        }

        if (mainGameState.getPossibleMoves().size() == 0)
        {
            gameOver = true;
            cout << "IT'S A DRAW" << endl;
            break;
        }

        cout << "Make your move...." << endl;


        // Get the user to enter their X and Y co-ords
        bool validMove = true;
        int x = -1, y = -1;
        GameAction playerAction;

        do {

            x = -1, y = -1;
            cout << "Enter your x position: ";
            cin >> x;

            // validate the numerical input 
            validMove = validatePosition(x, mainGameState);


        } while (!validMove);

        y = mainGameState.getLowestOfRow(x);

        //apply the player's move to the board
        playerAction.x = x;
        playerAction.y = y;
        playerAction.playerMove = playerMarker;

        mainGameState.setAndApplyAction(playerAction);
        mainGameState.printBoard();


        // check to see if the player's move won the match
        // if so, game's over
        winner = mainGameState.checkWin();

        if (winner == BOARD_SQUARE_STATE::CIRCLE)
        {
            gameOver = true;
            cout << "CIRCLE WINS!" << endl;
        }
        else  if (winner == BOARD_SQUARE_STATE::CROSS)
        {
            gameOver = true;
            cout << "CROSS WINS!" << endl;
        }

        // reset the root node ready for next turn
        rootNode->resetNode();
        first = false;



    } while (!gameOver);


    cout << "GAME OVER!" << endl;

}


