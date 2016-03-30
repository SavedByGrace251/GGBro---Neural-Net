//
//  Checkers.h
//  GGBro
//
//  Created by Jonathan Newell and Jay Byam.
//

#ifndef Checkers_h
#define Checkers_h

#include "Board.h"
#include "AI.h"
using namespace std;

class Game {
public:
	Board currentBoard;
	stringstream gameLog;
	AI *playerRed;
	AI *playerBlack;
	bool redsTurn = true;
	int numMoves = 0;
	bool gameFinished = false;
	bool redWin = false;
	bool draw = false;
	
	Game() {
		currentBoard = Board();
		playerRed = nullptr;
		playerBlack = nullptr;
	}

	Game(AI& playerRed_, AI& playerBlack_) {
		playerBlack = &playerBlack_;
		playerRed = &playerRed_;
		currentBoard = Board();
		
		(*playerBlack).playAsRed = false;
		(*playerRed).playAsRed = true;
	}
	
	Game(AI& playerRed_, AI& playerBlack_, Board initial) {
		playerBlack = &playerBlack_;
		playerRed = &playerRed_;
		currentBoard = initial;

		(*playerBlack).playAsRed = false;
		(*playerRed).playAsRed = true;
	}

	void setPlayers(AI& playerRed_, AI& playerBlack_) {
		playerBlack = &playerBlack_;
		playerRed = &playerRed_;
		(*playerBlack).playAsRed = false;
		(*playerRed).playAsRed = true;
	}
	
	void score() {
		if (gameFinished && !draw) {
			if (redWin) {
				(*playerRed).addWin();
				(*playerBlack).addLoss();
			} else {
				(*playerRed).addLoss();
				(*playerBlack).addWin();
			}
		}
	}
	
	void takeTurn() {
		if (numMoves >= 100) {
			draw = true;
			gameFinished = true;
			return;
		}
		++numMoves;
		gameLog << currentBoard << endl;
		if (currentBoard.redEliminated) {
			gameFinished = true;
			redWin = false;
		} else if (currentBoard.blackEliminated) {
			gameFinished = true;
			redWin = true;
		}
		if (redsTurn) {
			currentBoard = (*playerRed).makeMove(currentBoard);
			redsTurn = !redsTurn;
		} else {
			currentBoard = (*playerBlack).makeMove(currentBoard);
			redsTurn = !redsTurn;
		}
	}
};

// Print Checkers Game
//	prints the board to the given ostream
ostream& operator<<(ostream& os, Game& g) {
	os << g.gameLog.str();
	return os;
}

#endif /* Checkers_h */
