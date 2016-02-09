//
//  Piece.h
//  GGBro
//
//  Created by Jay Byam on 2/6/16.
//  Copyright © 2016 Jay Byam. All rights reserved.
//

#ifndef Piece_h
#define Piece_h

#include <vector>
using std::vector;

class Piece {
public:
    int position;
    bool isRed;
    bool isKing = false;
    
    
    
    // Secondary ctor
    Piece(int position, bool isRed, bool isKing) {
        this->position = position;
        this->isRed = isRed;
        this->isKing = isKing;
    }
    // Return possible moves depending on position and type
    vector<int> getPossibleMoves() {
        vector<vector<int>> redMoves { { 4, 5 }, { 5, 6 }, { 6, 7 }, { 7 }, // Top row legal moves
            { 8 }, { 8, 9 }, { 9, 10 }, { 10, 11 }, // 2nd row legal moves
            { 12, 13 }, { 13, 14 }, { 14, 15 }, { 15 }, // 3rd row legal moves
            { 16 }, { 16, 17 }, { 17, 18 }, { 18, 19 }, // 4th row legal moves
            { 20, 21 }, { 21, 22 }, { 23, 24 }, { 24 }, // 5th row legal moves
            { 25 }, { 25, 26 }, { 26, 27 }, { 27, 28 }, // 6th row legal moves
            { 28, 29 }, { 29, 30 }, { 30, 31 }, { 31 }, // 7th row legal moves
            {}, {}, {}, {} }; // Bottom row legal moves
        vector<vector<int>> blackMoves { {}, {}, {}, {}, // Top row legal moves
            { 0 }, { 0, 1 }, { 1, 2 }, { 2, 3 }, // And so on...
            { 4, 5 }, { 5, 6 }, { 6, 7 }, { 7 },
            { 8 }, { 8, 9 }, { 9, 10 }, { 10, 11 },
            { 12, 13 }, { 13, 14 }, { 14, 15 }, { 15 },
            { 16 }, { 16, 17 }, { 17, 18 }, { 18, 19 },
            { 20, 21 }, { 21, 22 }, { 22, 23 }, { 23 },
            { 24 }, { 24, 25 }, { 25, 26 }, { 26, 27 } };
        vector<vector<int>> kingMoves { { 4, 5 }, { 5, 6 }, { 6, 7 }, { 7 },
            { 0, 8 }, { 0, 1, 8, 9 }, { 1, 2, 9, 10 }, { 2, 3, 10, 11 },
            { 4, 5, 12, 13 }, { 5, 6, 13, 14 }, { 6, 7, 14, 15 }, { 7, 15 },
            { 8, 16 }, { 8, 9, 16, 17 }, { 9, 10, 17, 18 }, { 10, 11, 18, 19 },
            { 12, 13, 20, 21 }, { 13, 14, 21, 22 }, { 14, 15, 22, 23 }, { 15, 24 },
            { 16, 25 }, { 16, 17, 25, 26 }, { 17, 18, 26, 27 }, { 18, 19, 27, 28 },
            { 20, 21, 28, 29 }, { 21, 22, 29, 30 }, { 22, 23, 30, 31 }, { 23, 31 },
            { 24 }, { 24, 25 }, { 25, 26 }, { 26, 27 } };
        if (isKing) return kingMoves[position];
        if (isRed) return redMoves[position];
        return blackMoves[position];
    }
};

#endif /* Piece_h */
