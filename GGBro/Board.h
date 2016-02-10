//
//  Board.h
//  GGBro
//
//  Created by Jay Byam on 2/6/16.
//

#ifndef Board_h
#define Board_h

#include "Piece.h"
#include <algorithm>
using std::find;
#include <vector>
using std::vector;
#include <string>
using std::string;

class Board {
public:

	vector<Piece> pieces;
	bool redTurn = true;
	vector<int> freeSpaces{};
    
    // Default ctor
    Board() {
        for (int i = 0; i < 12; i++) {
            // First 12 indices are red pieces (not kings)
            pieces.push_back(Piece(i, true, false));
        }
        for (int i = 20; i < 32; i++) {
            // Last 12 indices are black pieces (not kings)
            pieces.push_back(Piece(i, false, false));
        }
        freeSpaces = { 12, 13, 14, 15, 16, 17, 18, 19 };
    }
    
    // Secondary ctor that takes a string for the state
    Board(string state, bool redTurn) {
        for (int i = 0; i < state.length(); i++) {
            if (state[i] != '_') {
                this->pieces.push_back(Piece(i, state[i] == 'r' || state[i] == 'R',  // is it a red piece
                                        state[i] == 'R' || state[i] == 'B')); // is it a king
            } else {
                freeSpaces.push_back(i);
            }
        }
        this->redTurn = redTurn;
    }
    
    // Secondary ctor that takes a vector of Piece's
    Board(vector<Piece> pieces, bool redTurn) {
        this->pieces = pieces;
        this->redTurn = redTurn;
    }
    
    // Return state
    vector<Piece> getPieces() {
        return pieces;
    }
    
    // Whether or not this board has no legal moves
    bool hasNoMoves() {
        return true;
    }
    
    vector<Board> generateLegalMoves() {
        vector<Board> possibleBoards;

        vector<vector<int>> blackMoves { {}, {}, {}, {}, // Top row legal moves
            {}, {}, {}, {}, // And so on...
            { {5,1} }, { {5,0}, {6,2} }, { {6,1}, {7,3} }, { {7,2} },
            { {8} }, { {8}, {9} }, { {9}, {10} }, { {10}, {11} },
            { {12}, {13} }, { {13}, {14} }, { {14}, {15} }, { {15} },
            { {16} }, { {16}, {17} }, { {17}, {18} }, { {18}, {19} },
            { {20}, {21} }, { {21}, {22} }, { {22}, {23} }, { {23} },
            { {24} }, { {24}, {25} }, { {25}, {26} }, { {26}, {27} } };
        vector<vector<int>> kingMoves { { {4}, {5} }, { {5}, {6} }, { {6}, {7} }, { {7} },
            { {0}, {8} }, { {0}, {1}, {8}, {9} }, { {1}, {2}, {9}, {10} }, { {2}, {3}, {10}, {11} },
            { {4}, {5}, {12}, {13} }, { {5}, {6}, {13}, {14} }, { {6}, {7}, {14}, {15} }, { {7}, {15} },
            { {8}, {16} }, { {8}, {9}, {16}, {17} }, { {9}, {10}, {17}, {18} }, { {10}, {11}, {18}, {19} },
            { {12}, {13}, {20}, {21} }, { {13}, {14}, {21}, {22} }, { {14}, {15}, {22}, {23} }, { {15}, {24} },
            { {16}, {25} }, { {16}, {17}, {25}, {26} }, { {17}, {18}, {26}, {27} }, { {18}, {19}, {27}, {28} },
            { {20}, {21}, {28}, {29} }, { {21}, {22}, {29}, {30} }, { {22}, {23}, {30}, {31} }, { {23}, {31} },
            { {24} }, { {24}, {25} }, { {25}, {26} }, { {26}, {27} } };

        vector<vector<vector<int>>> redJumps { { {5, 9} }, { {5,8}, {6,10} }, {{6,9}, {7,11} }, { {7,10} }, // Top row legal jumps
                                        { {8,13} }, { {8,12}, {9,14} }, { {9,13}, {10,15} }, { {10,14} }, // 2nd row legal jumps
                                        { {13,17} }, { {13,16}, {14,18} }, { {14,17}, {15,19} }, { {15,18} }, // 3rd row legal jumps
                                        { {16,21} }, { {16,20}, {17,22} }, { {17,21}, {18,23} }, { {18,22} }, // 4th row legal jumps
                                        { {21,25} }, { {21,24}, {22,26} }, { {22,25}, {23,27} }, { {23,26} }, // 5th row legal jumps
                                        { {24,29} }, { {24,28}, {25,30} }, { {25,29}, {26,31} }, { {26,30} }, // 6th row legal jumps
                                        {}, {}, {}, {}, // 7th row legal jumps
                                        {}, {}, {}, {} }; // Bottom row legal jumps
        vector<vector<int>> blackJumps { {}, {}, {}, {}, // Top row legal jumps
                                        {}, {}, {}, {}, // And so on...
                                        { {5,1} }, { {5,0}, {6,2} }, { {6,1}, {7,3} }, { {7,2} },
                                        { {5} }, { 4, 6 }, { 5, 7 }, { 6 },
                                        { {9} }, { 8, 10 }, { 9, 11 }, { 10 },
                                        { {13} }, { 12, 14 }, { 13, 15 }, { 14 },
                                        { {17} }, { 16, 18 }, { 17, 19 }, { 18 },
                                        { {21} }, { 20, 22 }, { 21, 23 }, { 22 } };
        vector<vector<int>> kingJumps { { {5, 9} }, { {5,8}, {6,10} }, {{6,9}, {7,11} }, { {7,10} },
                                        { 13 },{ 12, 14 },{ 13, 15 },{ 14 },
                                        { 1, 17 }, { 0, 2, 16, 18 }, { 1, 3, 17, 19 }, { 2, 18 },
                                        { 5, 21 }, { 4, 6, 20, 22 }, { 5, 7, 21, 23 }, { 6, 22 },
                                        { 9, 25 }, { 8, 10, 24, 26 }, { 9, 11, 25, 27 }, { 10, 26 },
                                        { 13, 29 }, { 12, 14, 28, 30 }, { 13, 15, 29, 31 }, { 14, 30 },
                                        { 17 },{ 16, 18 },{ 17, 19 },{ 18 },
                                        { 21 },{ 20, 22 },{ 21, 23 },{ 22 } };
    
		// For each piece in pieces
        for (auto piece = pieces.begin(); piece != pieces.end(); ++piece) {
			vector<Piece> tempPieces;
			// get possible moves from piece
			vector<int> moves = piece->getPossibleMoves();
            // check if space available on board
            for (auto space = moves.begin(); space != moves.end(); ++space) {
                if ((redTurn && piece->isRed) || (!redTurn && !piece->isRed)) {
                    auto foundItem = find(freeSpaces.begin(), freeSpaces.end(), *space);
                    // if there is an available free space
                    if (foundItem != freeSpaces.end()) {
                        // save current board
                        tempPieces = pieces;
                        // change piece's position
                        piece->position = *space;
                        // add changed board
                        possibleBoards.push_back(Board(pieces, !this->redTurn));
                        // replace pieces
                        pieces = tempPieces;
                    }
                }
            }
        }
        
        return possibleBoards;
    }

    string toString() {
        vector<char> boardStr (32, '_');
        for (auto itor = pieces.begin(); itor != pieces.end(); ++itor) {
            if (itor->isKing){
                if (itor->isRed) {
                    boardStr[itor->position] = 'R';
                } else {
                    boardStr[itor->position] = 'B';
                }
            } else {
                if (itor->isRed) {
                    boardStr[itor->position] = 'r';
                } else {
                    boardStr[itor->position] = 'b';
                }
            }
        }
        string strOut(boardStr.begin(), boardStr.end());
        return strOut;
    }
};

#endif /* Board_h */
