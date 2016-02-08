//
//  Board.h
//  GGBro
//
//  Created by Jay Byam on 2/6/16.
//

#ifndef Board_h
#define Board_h

#include "Piece.h"
#include <vector>
using std::vector;
#include <string>
using std::string;

class Board {
private:
    vector<int> freeSpaces {};
    vector<vector<int>> redJumps { { 9 }, { 8, 10 }, {9, 11 }, { 10 }, // Top row legal jumps
                                   { 13 }, { 12, 14 }, { 13, 15 }, { 14 }, // 2nd row legal jumps
                                   { 17 }, { 16, 18 }, { 17, 19 }, { 18 }, // 3rd row legal jumps
                                   { 21 }, { 20, 22 }, { 21, 23 }, { 22 }, // 4th row legal jumps
                                   { 25 }, { 24, 26 }, { 25, 27 }, { 26 }, // 5th row legal jumps
                                   { 29 }, { 28, 30 }, { 29, 31 }, { 30 }, // 6th row legal jumps
                                   {}, {}, {}, {}, // 7th row legal jumps
                                   {}, {}, {}, {} }; // Bottom row legal jumps
    vector<vector<int>> blackJumps { {}, {}, {}, {}, // Top row legal jumps
                                     {}, {}, {}, {}, // And so on...
                                     { 1 }, { 0, 2 }, { 6, 7 }, { 2 },
                                     { 5 }, { 4, 6 }, { 5, 7 }, { 6 },
                                     { 9 }, { 8, 10 }, { 9, 11 }, { 10 },
                                     { 13 }, { 12, 14 }, { 13, 15 }, { 14 },
                                     { 17 }, { 16, 18 }, { 17, 19 }, { 18 },
                                     { 21 }, { 20, 22 }, { 21, 23 }, { 22 } };
    vector<vector<int>> kingJumps { { 9 },{ 8, 10 },{ 9, 11 },{ 10 },
									{ 13 },{ 12, 14 },{ 13, 15 },{ 14 },
                                    { 4, 5, 12, 13 }, { 5, 6, 13, 14 }, { 6, 7, 14, 15 }, { 7, 15 },
                                    { 8, 16 }, { 8, 9, 16, 17 }, { 9, 10, 17, 18 }, { 10, 11, 18, 19 },
                                    { 12, 13, 20, 21 }, { 13, 14, 21, 22 }, { 14, 15, 22, 23 }, { 15, 24 },
                                    { 16, 25 }, { 16, 17, 25, 26 }, { 17, 18, 26, 27 }, { 18, 19, 27, 28 },
									{ 17 },{ 16, 18 },{ 17, 19 },{ 18 },
									{ 21 },{ 20, 22 },{ 21, 23 },{ 22 } };
    
public:
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
    }
    // Secondary ctor that takes a string for the state
    Board(string state, bool redTurn) {
        for (int i = 0; i < state.length(); i++) {
            if (state[i] != '_') {
                this->pieces[i] = Piece(i,
                                        state[i] == 'r' || state[i] == 'R',  // is it a red piece
                                        state[i] == 'R' || state[i] == 'B'); // is it a king
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
    
//    vector<Board> generateLegalMoves() {
//        for (auto filler : state) {
//            if (filler != '_') {
//                if (redTurn && (filler == 'r' || filler == 'R')) {
//                    
//                }
//            }
//        }
//        
//    }

    vector<Piece> pieces;
    bool redTurn = true;
};

#endif /* Board_h */
