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
using namespace std;

int main() {
    Board init("_B___bb__________RrR____________", false);
    vector<Board> moves = init.generateLegalMoves();
    for (auto move = moves.begin(); move != moves.end(); ++move){
        cout << move->toString() << endl;
    }
    return 0;
}