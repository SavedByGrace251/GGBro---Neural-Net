//	Authors: Jay Byam, Jonathan Newell
//
//  makeMove.cpp
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
	
	if (nArgs < 2) {
		return 666;
	}
	
	string board = args[1];
	string team = args[2];
	string fileLoc = "player"+team+".data";
	bool isRed = (team.compare("red") == 0);
	
	ifstream playerFile("fileLoc");
	
	Board b(board);
	b.redTurn = isRed;
	AI player;
	playerFile >> player;
	player.playAsRed = isRed;
	player.thinker.maxtime = 5.0;

	cout << player.makeMove(b).toString();
	
}