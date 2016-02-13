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
#include <chrono>
using namespace std;

int main() {

    using namespace chrono;
    
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    
	Board init("_____________bb__R___bb_________", false);
    
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    
    duration<double> time_span1 = duration_cast<duration<double>>(t2 - t1);
    cout << "board contrustion took " << time_span1.count() << " seconds." << endl;
    
	init.redTurn = true;
    t1 = high_resolution_clock::now();
	vector<Board> newBoards = init.generateLegalMoves();
    t2 = high_resolution_clock::now();
    
    cout << "board generation took " << time_span1.count() << " seconds." << endl;
    
	for (auto board : newBoards) {
		cout << board.toString() << endl;
	}
    return 0;
}