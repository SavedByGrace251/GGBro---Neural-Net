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
    
    // Secondary ctor
    Piece(int position, bool isRed, bool isKing) {
        this->position = position;
        this->isRed = isRed;
        this->isKing = isKing;
    }

	vector<vector<int>> getPossibleJumps(vector<vector<vector<int>>> & redJumps,
                                         vector<vector<vector<int>>> & blackJumps,
                                         vector<vector<vector<int>>> & kingJumps) {
		if (isKing) return kingJumps[position];
		if (isRed) return redJumps[position];
		return blackJumps[position];
	}

    // Return possible moves depending on position and type
    vector<int> getPossibleMoves(vector<vector<int>> & redMoves,
                                 vector<vector<int>> & blackMoves,
                                 vector<vector<int>> & kingMoves) {
        if (isKing) return kingMoves[position];
        if (isRed) return redMoves[position];
        return blackMoves[position];
    }
};

#endif /* Piece_h */
