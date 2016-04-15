//	Authors: Jay Byam, Jonathan Newell
//
//  Board.h
//  GGBro
//

#ifndef Board_h
#define Board_h

#include "Piece.h"
#include <algorithm>
using std::find;
#include <map>
using std::map;
#include <vector>
using std::vector;
#include <string>
using std::string;
using std::pair;
using std::make_pair;
#include <iostream>
using std::ostream;
using std::cout;
using std::endl;

class Board {
public:
	string boardString;
	vector<Piece> redPieces;
	vector<Piece> blackPieces;
	bool redTurn = true;
	vector<bool> freeSpaces = vector<bool>(32, true);
	vector<double> state;
	double rank;
	double childRank = -1;
	double blackVal;
	double redVal;
	double kingVal;
	bool redEliminated = false;
	bool blackEliminated = false;
	bool endState = false;
	Board* parentBoard = nullptr;
	
	// Default ctor
	Board() {
		for (int i = 0; i < 12; i++) {
			// First 12 indices are red pieces (not kings)
			redPieces.push_back(Piece(i, true, false));
		}
		for (int i = 12; i < 20; i++) {
			freeSpaces[i] = true;
		}
		for (int i = 20; i < 32; i++) {
			// Last 12 indices are black pieces (not kings)
			blackPieces.push_back(Piece(i, false, false));
		}
		setupBoard();
	}
	
	// Secondary ctor that takes a string for the state and a bool for the turn
	Board(string state, bool redTurn = true) {
		if (state.length() != 32) {
			throw std::invalid_argument("Board state must be 32 characters");
		}
		for (int i = 0; i < state.length(); i++) {
			if (state[i] != '_') {
				bool redCheck = state[i] == 'r' || state[i] == 'R';
				bool kingCheck = state[i] == 'R' || state[i] == 'B';
				if (redCheck) {
					this->redPieces.push_back(Piece(i, redCheck, kingCheck));
				} else {
					this->blackPieces.push_back(Piece(i, redCheck, kingCheck));
				}
			}
		}
		this->redTurn = redTurn;
		setupBoard();
	}
	
	// Secondary ctor that takes a vector of Pieces, freespaces, and a bool for the turn
	Board(Board& parentBoard_, vector<Piece> redPieces_, vector<Piece> blackPieces_, bool redTurn_, double redVal_, double blackVal_, double kingVal_) {
		parentBoard = &parentBoard_;
		redPieces = redPieces_;
		blackPieces = blackPieces_;
		redTurn = redTurn_;
		redVal = redVal_;
		blackVal = blackVal_;
		kingVal = kingVal_;
		setupBoard();
	}
	
	// setup board
	//	calculate the board state
	void setupBoard() {
		// blank state
		for (int i = 0; i < 32; ++i) {
			freeSpaces[i] = true;
		}
		state = vector<double>(32, 0);
		// for each red piece
		for (int i = 0; i < redPieces.size(); ++i) {
			if (redPieces[i].position >= 28) {
				redPieces[i].isKing = true;
			}
			// if its position = -1 it has been jumped and needs to be removed
			if (redPieces[i].position == -1) {
				redPieces.erase(redPieces.begin() + i);
				--i;
			// else add the piece score to its position
			} else {
				freeSpaces[redPieces[i].position] = false;
				if (redPieces[i].isKing) {
					state[redPieces[i].position] = redVal * kingVal;
				} else {
					state[redPieces[i].position] = redVal;
				}
			}
		}
		// for each black piece
		for (int i = 0; i < blackPieces.size(); ++i) {
			if (blackPieces[i].position <= 3) {
				blackPieces[i].isKing = true;
			}
			// if its position = -1 it has been jumped and needs to be removed
			if (blackPieces[i].position == -1) {
				blackPieces.erase(blackPieces.begin() + i);
				--i;
			// else add the piece score to its position
			} else {
				freeSpaces[blackPieces[i].position] = false;
				if (blackPieces[i].isKing) {
					state[blackPieces[i].position] = blackVal * kingVal;
				} else {
					state[blackPieces[i].position] = blackVal;
				}
			}
		}
		// if there are no black pieces
		if (blackPieces.size() == 0) {
			blackEliminated = true;
			endState = true;
		}
		// if there are no red pieces
		if (redPieces.size() == 0) {
			redEliminated = true;
			endState = true;
		}
		boardString = toString();
	}

	// rank parent
	//	ranks the parent according to this boards rank
	void rateParent(double r, bool isMax) {
		if (childRank == -1) {
			childRank = r;
		} else if (isMax) {
			if (childRank < r) {
				childRank = r;
			}
		} else {
			if (childRank > r) {
				childRank = r;
			}
		}
		if (parentBoard == nullptr) {
			rank = childRank;
		} else {
			(*parentBoard).rateParent(childRank, !isMax);
		}
	}

	void setRank(double r, bool isMax) {
		rank = r;
		if (parentBoard != nullptr)
			(*parentBoard).rateParent(r, !isMax);
	}

	// checks if more jumps are available (ex. double jumps)
	bool checkJumps(Piece& piece, vector<Piece>& ownerPieces, vector<Piece>& enemyPieces, vector<Board>& possibleBoards) {
		bool foundJump = false;
		vector<Piece> tempOPieces;
		vector<Piece> tempEPieces;
		// check if jump available
		vector<vector<int>> *possibleJumps = &kingJumps[piece.position];
		if (!piece.isKing) {
			if (piece.isRed) {
				possibleJumps = &redJumps[piece.position];
			} else {
				possibleJumps = &blackJumps[piece.position];
			}
		}
		// using pointer for "erase" function
		int numEnemies = enemyPieces.size();
		bool validRedJumps = (piece.isRed && piece.position < 24);
		bool validBlackJumps = (!piece.isRed && piece.position > 7);
		if (piece.isKing || validRedJumps || validBlackJumps) {
			for (int j = 0; j < numEnemies; ++j) {
				int numJumps = (*possibleJumps).size();
				for (int k = 0; k < numJumps; ++k) {
					if (enemyPieces[j].position == (*possibleJumps)[k][0]) {
						// if there is an available free space
						if (freeSpaces[(*possibleJumps)[k][1]]) {
							// save current board
							tempOPieces = ownerPieces;
							tempEPieces = enemyPieces;
							// move piece
							piece.position = (*possibleJumps)[k][1];
							// "remove" piece
							enemyPieces[j].position = -1;
							// check for more jumps
							foundJump = checkJumps(piece, ownerPieces, enemyPieces, possibleBoards);
							// add changed board
							if (!foundJump) possibleBoards.push_back(Board(*this, this->redPieces, this->blackPieces, !this->redTurn, redVal, blackVal, kingVal));
							// put pieces
							ownerPieces = tempOPieces;
							enemyPieces = tempEPieces;
							// notify jump is found
							foundJump = true;
						}
					}
				}
			}
		}
		return foundJump;
	}
	
	// Generate all legal boards
	void generateLegalMoves(vector<Board>& possibleBoards, double redVal_ = 1, double blackVal_ = -1, double kingVal_ = 1.4) {

		if (endState) {
			return;
		}

		redVal = redVal_;
		blackVal = blackVal_;
		kingVal = kingVal_;

		bool foundJump = false;
		
		possibleBoards.clear();
		vector<Piece> tempOPieces;
		vector<Piece> tempEPieces;
		
		vector<Piece> * enemyPieces;
		vector<Piece> * ownerPieces;
		
		// red's turn
		if (redTurn) {
			enemyPieces = &blackPieces;
			ownerPieces = &redPieces;
			// if black's turn
		} else {
			enemyPieces = &redPieces;
			ownerPieces = &blackPieces;
		}
		
		int numPieces = (*ownerPieces).size();
		for (int i = 0; i < numPieces; ++i) {
			// check if jump available
			bool pieceHasJump = checkJumps((*ownerPieces)[i], *ownerPieces, *enemyPieces, possibleBoards);
			if (pieceHasJump) foundJump = true;
		}
		if (!foundJump) {
			for (int i = 0; i < numPieces; ++i) {
				// check possible moves
				vector<int> *possibleMoves = &kingMoves[(*ownerPieces)[i].position];
				if (!(*ownerPieces)[i].isKing) {
					if ((*ownerPieces)[i].isRed) {
						possibleMoves = &redMoves[(*ownerPieces)[i].position];
					} else {
						possibleMoves = &blackMoves[(*ownerPieces)[i].position];
					}
				}
				// check if space available on board
				for (int & space : *possibleMoves) {
					// if there is an available free space
					if (freeSpaces[space]) {
						// save current board
						tempOPieces = *ownerPieces;
						// change piece's position
						(*ownerPieces)[i].position = space;
						// add changed board
						possibleBoards.push_back(Board(*this, this->redPieces, this->blackPieces, !this->redTurn, redVal, blackVal, kingVal));
						// put pieces
						*ownerPieces = tempOPieces;
					}
				}
			}
		}
	}
	
	// convert current board to string
	string toString() {
		vector<char> boardStr(32, '_');
		for (auto piece : redPieces) {
			if (piece.isKing) {
				boardStr[piece.position] = 'R';
			} else {
				boardStr[piece.position] = 'r';
			}
		}
		for (auto piece : blackPieces) {
			if (piece.isKing) {
				boardStr[piece.position] = 'B';
			} else {
				boardStr[piece.position] = 'b';
			}
		}
		return string(boardStr.begin(), boardStr.end());
	}

	string printFreeSpaces() {
		vector<char> sFreeSpaces(32, ' ');
		for (int i = 0; i < 32; ++i) if (freeSpaces[i]) sFreeSpaces[i] = 'x';
		return string(sFreeSpaces.begin(), sFreeSpaces.end());
	}

	bool operator<(const Board& b) const {
		return (this->rank < b.rank);
	}
};

// Print Board
//	prints the board to the given ostream
ostream& operator<<(ostream& os, Board& b) {
	os << b.toString();
	return os;
}

#endif /* Board_h */