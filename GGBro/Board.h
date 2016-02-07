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
            this->pieces[i] = Piece(i,
                                    state[i] == 'r' || state[i] == 'R',
                                    state[i] == 'R' || state[i] == 'B');
        }
        this->redTurn = redTurn;
    }
    // Secondary ctor that takes a vector of chars for the state
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
