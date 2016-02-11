//
//  main.cpp
//  GGBro
//
//  Created by Jay Byam on 2/6/16.
//

#include <stdio.h>
#include "Board.h"
#include "Piece.h"
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {

	Board init("_____________bb__R___bb_________", false);
	init.redTurn = true;
	vector<Board> newBoards = init.generateLegalMoves();
	for (auto board : newBoards) {
		cout << board.toString() << endl;
	}
    return 0;
}