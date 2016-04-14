//	Authors: Jay Byam, Jonathan Newell
//
//  main.cpp
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

	cout << "Training Started" << endl;
	AI player1;
	AI player2;
	ifstream AIFile("TestingPlayers.data");
	AIFile >> player1 >> player2;
	cout << player1.AIType << endl << player2.AIType << endl;
	Game game1;
	game1.setPlayers(player2, player1);
	game1.playGame();
	cout << endl << game1 << endl;
	Game game2;
	game2.setPlayers(player1, player2);
	game2.playGame();
	cout << endl << game2 << endl;
	cout << "Training Ended" << endl;

	return 0;
}