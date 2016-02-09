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
using namespace std;

int main() {
    Board init;
    Piece temp(1, false, false);
    cout << init.toString() << endl;
    cout << sizeof(init) << endl;
    cout << sizeof(temp) << endl;
    cout << sizeof(init.toString()) << endl;
    cout << sizeof(char) << endl;
    return 0;
}