//
//  main.cpp
//  GGBro
//
//  Created by Jay Byam on 2/6/16.
//  Copyright © 2016 Jay Byam. All rights reserved.
//

#include <stdio.h>
#include "Board.h"
#include "Piece.h"
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    Board init;
	vector<int> test{ 1,2,3,4 };
    cout << init.toString() << endl;
	auto foundItem = find(test.begin(), test.end(), 3);
	cout << *foundItem << endl;
    return 0;
}