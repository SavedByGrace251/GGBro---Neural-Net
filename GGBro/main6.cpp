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

#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <cmath>
using namespace std;

int main() {

	cout << "Training Started" << endl;
	Training t(100);
	t.setMaxTime(0, 0, 5, 57, 0);
	t.train();
	cout << "Training Ended" << endl;

	return 0;
}