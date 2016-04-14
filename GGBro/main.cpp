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
	Training training;
	training.setMaxTime(0, 0, 8, 0, 0);
	training.resume();
	training.train();
	cout << "Training Ended" << endl;

	return 0;
}