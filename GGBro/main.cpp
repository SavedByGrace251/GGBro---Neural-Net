//
//  main.cpp
//  GGBro
//
//  Created by Jay Byam on 2/6/16.
//

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
#include <random>
using namespace std;

int main() {

    using namespace chrono;
    // Time stuff
    high_resolution_clock::time_point t1;
    high_resolution_clock::time_point t2;
	duration<double> timeSpan;
    
	// random stuff
	uniform_real_distribution<double> uniform(0, 1);
	typedef std::chrono::high_resolution_clock myclock;
	myclock::time_point beginning = myclock::now();
	myclock::duration d = myclock::now() - beginning;
	unsigned seed = d.count();
	default_random_engine engine(seed);
	engine.seed;

	int count = 0;
	vector<int> layers{ 50, 75, 40, 10, 1 };
	NeuralNetwork net(layers);
	vector<double> weights(net.numberOfWeights);
	for (auto & weight : weights) {
		weight = uniform(engine);
	}
	vector<double> inputs(layers[0]);
	for (auto & input : inputs) {
		input = uniform(engine);
	}

	net.setWeights(weights);
	net.setInput(inputs);

	cout << "Board evaluation";
    for (auto thing : net.Activate()) {
        cout << thing << endl;
    }

	count = 0;
	t1 = high_resolution_clock::now();
	while (timeSpan.count() <= 1) {
		net.Activate();
		t2 = high_resolution_clock::now();
		timeSpan = duration_cast<duration<double>>(t2 - t1);
		++count;
	}
    
    cout << "Net evaluations per second: " << count << endl;
	return 0;
}