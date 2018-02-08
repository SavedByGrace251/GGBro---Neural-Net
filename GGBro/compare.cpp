//	Authors: Jay Byam, Jonathan Newell
//
//  compare.cpp
//  GGBro
//

#include "Board.h"
#include "Piece.h"
#include "AI.h"
#include "Checkers.h"
#include "Tournament.h"
#include "Training.h"
#include <fstream>
#include <iterator>
using namespace std;

int main(int nArgs, char* args[]) {

	if (nArgs < 3) {
		return 666;
	}

	string newAI = args[2];
	string oldAI = args[1];

	ifstream newAIF("generation_" + newAI + ".data");
	ifstream oldAIF("generation_" + oldAI + ".data");
	AI player1;
	AI player2;
	newAIF >> player1;
	oldAIF >> player2;
	player1.AIType = "NEW_PLAYER";
	player2.AIType = "OLD_PLAYER";
	vector<AI> players = { player1, player2 };

	Tournament t(players);
	t.commence();
	t.printStats(cout);
}