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
	Training training(50);
	// set train time: weeks, days, hours, minutes, seconds
	training.setMaxTime(0, 0, 5, 45, 0);
	training.train();
	cout << "Training Ended" << endl;

	return 0;
}