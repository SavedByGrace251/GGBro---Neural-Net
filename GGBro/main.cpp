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

	Training training(96);
	// set train time:  weeks days hours minutes seconds
	training.setMaxTime(0,    0,   95,   45,     0);
	training.train();

	return 0;
}