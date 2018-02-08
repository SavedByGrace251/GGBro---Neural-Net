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
	ike.AIType = "test";
	mike.AIType = "test";
	ifstream inf("players.data");
	inf >> ike >> mike;
	if (ike.AIType.compare("test") == 0) {
		cout << "Ike is using a random brain" << endl;
	}
	if (mike.AIType.compare("test") == 0) {
		cout << "Mike is using a random brain" << endl;
	}
	Game game1(ike, mike);
	Game game2(mike, ike);
	game1.playGame();
	game2.playGame();
	cout << game1 << endl << game2 << endl;
	return 0;
}