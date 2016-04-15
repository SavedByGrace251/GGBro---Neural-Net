//	Authors: Jay Byam, Jonathan Newell
//
//  main.cpp
//  GGBro
//

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
	Training t(100);
	t.setMaxTime(0, 0, 95, 45, 0);
	t.train();
	cout << "Training Ended" << endl;
	return 0;
}