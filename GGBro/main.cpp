//
//  main.cpp
//  GGBro
//
//  Created by Jay Byam on 2/6/16.
//

#include <stdio.h>
#include "Board.h"
#include "NeuralNetwork.h"
#include "EvolveNetwork.h"
#include "Individual.h"
#include "DataSet.h"
#include "Piece.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
using namespace std;

int main() {

    using namespace chrono;
    
    high_resolution_clock::time_point t1;
    high_resolution_clock::time_point t2;
	duration<double> timeSpan;
    
    t1 = high_resolution_clock::now();
    int count = 0;
	vector<int> layers{ 32, 40, 10, 1 };
	NeuralNetwork net(layers);
	vector<double> weights(net.numberOfWeights);
	uniform_real_distribution<double> uniform(0, 1);
	default_random_engine engine;

	for (auto & weight : weights) {
		weight = uniform(engine);
	}
	vector<double> inputs(33);
	for (auto & input : inputs) {
		input = uniform(engine);
	}

	net.setWeights(weights);
	net.setInput(inputs);

    for (auto thing : net.Activate()) {
        cout << thing << endl;
    }

    /*while (count <= 1000000) {
		net.Activate();
        count++;
    }*/
	t2 = high_resolution_clock::now();
	timeSpan = duration_cast<duration<double>>(t2 - t1);
    
    cout << "Board generations: " << count << "." << endl;
    return 0;
}