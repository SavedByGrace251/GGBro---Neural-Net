//
//  main.cpp
//  GGBro
//
//  Created by Jay Byam on 2/6/16.
//

#include <stdio.h>
#include "Board.h"
#include "NeuralNetwork.h"
#include "EvolveNetwork.h"
#include "Individual.h"
#include "DataSet.h"
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
    cout << "Board contruction took " << time_span1.count() << " seconds." << endl;
    
	init.redTurn = true;
    t1 = high_resolution_clock::now();
    int count = 0;
    
    while (time_span1.count() < 10) {
        vector<Board> newBoards = init.generateLegalMoves();
        t2 = high_resolution_clock::now();
        time_span1 = duration_cast<duration<double>>(t2 - t1);
        count++;
    }
    
    cout << "Board generations: " << count << "." << endl;
    return 0;
}