//
//  Board.h
//  GGBro
//
//  Created by Jay Byam And Jonathan Newell

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

struct moveMap {
	vector<vector<vector<int>>> redJumps{ { { 5, 9 } },{ { 5, 8 },{ 6, 10 } },{ { 6, 9 },{ 7, 11 } },{ { 7, 10 } }, // Top row legal jumps
		{ { 8, 13 } },{ { 8, 12 },{ 9, 14 } },{ { 9, 13 },{ 10, 15 } },{ { 10, 14 } }, // 2nd row legal jumps
		{ { 13, 17 } },{ { 13, 16 },{ 14, 18 } },{ { 14, 17 },{ 15, 19 } },{ { 15, 18 } }, // 3rd row legal jumps
		{ { 16, 21 } },{ { 16, 20 },{ 17, 22 } },{ { 17, 21 },{ 18, 23 } },{ { 18, 22 } }, // 4th row legal jumps
		{ { 21, 25 } },{ { 21, 24 },{ 22, 26 } },{ { 22, 25 },{ 23, 27 } },{ { 23, 26 } }, // 5th row legal jumps
		{ { 24, 29 } },{ { 24, 28 },{ 25, 30 } },{ { 25, 29 },{ 26, 31 } },{ { 26, 30 } }, // 6th row legal jumps
		{},{},{},{}, // 7th row legal jumps
		{},{},{},{} }; // Bottom row legal jumps
	vector<vector<vector<int>>> blackJumps{ {},{},{},{}, // Top row legal jumps
		{},{},{},{}, // And so on...
		{ { 5, 1 } },{ { 5, 0 },{ 6, 2 } },{ { 6, 1 },{ 7, 3 } },{ { 7, 2 } },
		{ { 8, 5 } },{ { 8, 4 },{ 9, 6 } },{ { 9, 5 },{ 10, 7 } },{ { 10, 6 } },
		{ { 13, 9 } },{ { 13, 8 },{ 14, 10 } },{ { 14, 9 },{ 15, 11 } },{ { 16, 10 } },
		{ { 16, 13 } },{ { 16, 12 },{ 17, 14 } },{ { 17, 13 },{ 18, 15 } },{ { 19, 14 } },
		{ { 21, 17 } },{ { 21, 16 },{ 22, 18 } },{ { 23, 17 },{ 24, 19 } },{ { 24, 18 } },
		{ { 24, 21 } },{ { 24, 20 },{ 25, 22 } },{ { 25, 21 },{ 26, 23 } },{ { 26, 22 } } };
	vector<vector<vector<int>>> kingJumps{ { { 5, 9 } },{ { 5, 8 },{ 6, 10 } },{ { 6, 9 },{ 7, 11 } },{ { 7, 10 } },
		{ { 8, 13 } },{ { 8, 12 },{ 9, 14 } },{ { 9, 13 },{ 10, 15 } },{ { 10, 14 } },
		{ { 5, 1 },{ 13, 17 } },{ { 5, 0 },{ 6, 2 },{ 13, 16 },{ 14, 18 } },{ { 6, 1 },{ 7, 3 },{ 14, 17 },{ 15, 19 } },{ { 7, 2 },{ 15, 18 } },
		{ { 8, 5 },{ 16, 21 } },{ { 8, 4 },{ 9, 6 },{ 16, 20 },{ 17, 22 } },{ { 9, 5 },{ 10, 7 },{ 17, 21 },{ 18, 23 } },{ { 10, 6 },{ 18, 22 } },
		{ { 13, 9 },{ 21, 25 } },{ { 13, 8 },{ 14, 10 },{ 21, 24 },{ 22, 26 } },{ { 14, 9 },{ 15, 11 },{ 22, 25 },{ 23, 27 } },{ { 15, 10 },{ 23, 26 } },
		{ { 16, 13 },{ 24, 29 } },{ { 16, 12 },{ 17, 14 },{ 24, 28 },{ 25, 30 } },{ { 17, 13 },{ 18, 15 },{ 25, 29 },{ 26, 31 } },{ { 18, 14 },{ 26, 30 } },
		{ { 21, 17 } },{ { 21, 16 },{ 22, 18 } },{ { 23, 17 },{ 24, 19 } },{ { 24, 18 } },
		{ { 24, 21 } },{ { 24, 20 },{ 25, 22 } },{ { 25, 21 },{ 26, 23 } },{ { 26, 22 } } };
	vector<vector<int>> redMoves{ { 4, 5 },{ 5, 6 },{ 6, 7 },{ 7 }, // Top row legal moves
		{ 8 },{ 8, 9 },{ 9, 10 },{ 10, 11 }, // 2nd row legal moves
		{ 12, 13 },{ 13, 14 },{ 14, 15 },{ 15 }, // 3rd row legal moves
		{ 16 },{ 16, 17 },{ 17, 18 },{ 18, 19 }, // 4th row legal moves
		{ 20, 21 },{ 21, 22 },{ 23, 24 },{ 24 }, // 5th row legal moves
		{ 25 },{ 25, 26 },{ 26, 27 },{ 27, 28 }, // 6th row legal moves
		{ 28, 29 },{ 29, 30 },{ 30, 31 },{ 31 }, // 7th row legal moves
		{},{},{},{} }; // Bottom row legal moves
	vector<vector<int>> blackMoves{ {},{},{},{}, // Top row legal moves
		{ 0 },{ 0, 1 },{ 1, 2 },{ 2, 3 }, // And so on...
		{ 4, 5 },{ 5, 6 },{ 6, 7 },{ 7 },
		{ 8 },{ 8, 9 },{ 9, 10 },{ 10, 11 },
		{ 12, 13 },{ 13, 14 },{ 14, 15 },{ 15 },
		{ 16 },{ 16, 17 },{ 17, 18 },{ 18, 19 },
		{ 20, 21 },{ 21, 22 },{ 22, 23 },{ 23 },
		{ 24 },{ 24, 25 },{ 25, 26 },{ 26, 27 } };
	vector<vector<int>> kingMoves{ { 4, 5 },{ 5, 6 },{ 6, 7 },{ 7 },
		{ 0, 8 },{ 0, 1, 8, 9 },{ 1, 2, 9, 10 },{ 2, 3, 10, 11 },
		{ 4, 5, 12, 13 },{ 5, 6, 13, 14 },{ 6, 7, 14, 15 },{ 7, 15 },
		{ 8, 16 },{ 8, 9, 16, 17 },{ 9, 10, 17, 18 },{ 10, 11, 18, 19 },
		{ 12, 13, 20, 21 },{ 13, 14, 21, 22 },{ 14, 15, 22, 23 },{ 15, 24 },
		{ 16, 25 },{ 16, 17, 25, 26 },{ 17, 18, 26, 27 },{ 18, 19, 27, 28 },
		{ 20, 21, 28, 29 },{ 21, 22, 29, 30 },{ 22, 23, 30, 31 },{ 23, 31 },
		{ 24 },{ 24, 25 },{ 25, 26 },{ 26, 27 } };
};

class Board {
public:
	vector<Piece> redPieces;
	vector<Piece> blackPieces;
	bool redTurn = true;
	vector<int> freeSpaces{};
	double rank;
	Board *parent;
	
	// Default ctor
	Board() {
		for (int i = 0; i < 12; i++) {
			// First 12 indices are red pieces (not kings)
			redPieces.push_back(Piece(i, true, false));
		}
		for (int i = 20; i < 32; i++) {
			// Last 12 indices are black pieces (not kings)
			blackPieces.push_back(Piece(i, false, false));
		}
		freeSpaces = { 12, 13, 14, 15, 16, 17, 18, 19 };
	}
	
	// Secondary ctor that takes a string for the state and a bool for the turn
	Board(string state, bool redTurn) {
		for (int i = 0; i < state.length(); i++) {
			if (state[i] != '_') {
				bool redCheck = state[i] == 'r' || state[i] == 'R';
				bool kingCheck = state[i] == 'R' || state[i] == 'B';
				if (redCheck) {
					this->redPieces.push_back(Piece(i, redCheck, kingCheck));
				} else {
					this->blackPieces.push_back(Piece(i, redCheck, kingCheck));
				}
			} else {
				freeSpaces.push_back(i);
			}
		}
		this->redTurn = redTurn;
	}
	
	// Secondary ctor that takes a vector of Pieces, freespaces, and a bool for the turn
	Board(vector<Piece> redPieces, vector<Piece> blackPieces, vector<int> freeSpaces, bool redTurn) {
		this->redPieces = redPieces;
		this->blackPieces = blackPieces;
		this->redTurn = redTurn;
		this->freeSpaces = freeSpaces;
		for (int i = 0; i < redPieces.size(); i++) {
			if (redPieces[i].position == -1) {
				redPieces.erase(redPieces.begin() + i);
			}
		}
		for (int i = 0; i < blackPieces.size(); i++) {
			if (blackPieces[i].position == -1) {
				blackPieces.erase(blackPieces.begin() + i);
			}
		}
	}
	
	// checks if more jumps are available (ex. double jumps)
	void checkJumps(Piece piece, moveMap& moves, vector<Piece>& enemyPieces) {
		
	}
	
	// Generate all legal boards
	vector<Board> generateLegalMoves(moveMap & moves) {
		bool foundJump = false;
		
		vector<Board> possibleBoards;
		vector<Piece> tempOPieces;
		vector<Piece> tempEPieces;
		vector<int> tempFreeSpaces;
		
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
		
		for (Piece & piece : *ownerPieces) {
			// check if jump available
			// using pointer for "erase" function
			for (auto & enemy  : *enemyPieces) {
				vector<vector<int>> possibleJumps = piece.getPossibleJumps(moves.redJumps, moves.blackJumps, moves.kingJumps);
				for (auto & jump : possibleJumps) {
					if (enemy .position == jump[0]) {
						auto foundFreeSpace = find(freeSpaces.begin(), freeSpaces.end(), jump[1]);
						// if there is an available free space
						if (foundFreeSpace != freeSpaces.end()) {
							// save current board
							tempOPieces = *ownerPieces;
							tempEPieces = *enemyPieces;
							// save current free spaces
							tempFreeSpaces = freeSpaces;
							// delete free space for new position
							freeSpaces.erase(foundFreeSpace);
							// add current piece position as free space
							freeSpaces.push_back(piece.position);
							// move piece
							piece.position = jump[1];
							// add enemy  piece position as free space
							freeSpaces.push_back(enemy.position);
							// "remove" piece
							enemy.position = -1;
							// check for more jumps
							checkJumps(piece, moves, *enemyPieces);
							// add changed board
							possibleBoards.push_back(Board(this->redPieces, this->blackPieces, this->freeSpaces, !this->redTurn));
							// put pieces
							*ownerPieces = tempOPieces;
							*enemyPieces = tempEPieces;
							// put free spaces back
							freeSpaces = tempFreeSpaces;
							// notify jump is found
							foundJump = true;
						}
					}
				}
			}
			
			if (!foundJump) {
				// check if space available on board
				for (int & space : piece.getPossibleMoves(moves.redMoves, moves.blackMoves, moves.kingMoves)) {
					auto foundFreeSpace = find(freeSpaces.begin(), freeSpaces.end(), space);
					// if there is an available free space
					if (foundFreeSpace != freeSpaces.end()) {
						// save current board
						tempOPieces = *ownerPieces;
						// save current free spaces
						tempFreeSpaces = freeSpaces;
						// delete free space for new position
						freeSpaces.erase(foundFreeSpace);
						// add current piece position as free space
						freeSpaces.push_back(piece.position);
						// change piece's position
						piece.position = space;
						// add changed board
						possibleBoards.push_back(Board(this->redPieces, this->blackPieces, this->freeSpaces, !this->redTurn));
						// replace pieces
						*ownerPieces = tempOPieces;
						// replace free spaces
						freeSpaces = tempFreeSpaces;
					}
				}
			}
		}
		return possibleBoards;
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
};

#endif /* Board_h */