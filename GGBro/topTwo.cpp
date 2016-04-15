//	Authors: Jay Byam, Jonathan Newell
//
//  topTwo.cpp
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

int main() {

	AI ike;
	AI mike;
	ifstream inf("players.data");
	inf >> ike >> mike;
	Game game1(ike, mike);
	Game game2(mike, ike);
	game1.playGame();
	game2.playGame();
	cout << game1 << endl << game2 << endl;

	return 0;
}