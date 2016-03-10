//
//  Piece.h
//  GGBro
//
//  Created by Jay Byam on 2/6/16.
//

#ifndef Piece_h
#define Piece_h

#include <vector>
using std::vector;
#include <map>
using std::map;

class Piece {
public:
    int position;
    bool isRed;
    bool isKing = false;
    
    // default ctor
    Piece(int position, bool isRed, bool isKing) {
        this->position = position;
        this->isRed = isRed;
        this->isKing = isKing;
    }
};

#endif /* Piece_h */
