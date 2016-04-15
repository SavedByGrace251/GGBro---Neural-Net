//	Authors: Jay Byam, Jonathan Newell
//
//  TopCompete.cpp
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
	
	string fileLoc = "player.data";
	string board = args[1];
	string team = args[2];
	bool isRed = (team.compare("red") == 0);
	
	ifstream playerFile("fileLoc");
	
	Board b(board);
	b.redTurn = isRed;
	AI player;
	playerFile >> player;
	player.playAsRed = isRed;

	cout << player.makeMove(b).toString();
	
}