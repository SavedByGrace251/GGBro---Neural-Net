//
//  main.cpp
//  GGBro
//
//  Created by Jay Byam on 2/6/16.
//

#include "Board.h"
#include "NeuralNetwork.h"
#include "EvolveNetwork.h"
#include "Piece.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <random>
#include <thread>
using namespace std;

// generate boards to a given depth
int generateBoards(int depth, int maxDepth, vector<Board> & boards, moveMap & moves, NeuralNetwork & net) {
	int n = boards.size();
	if (depth < maxDepth) {
		for (int i = 0; i < boards.size(); i++) {
			vector<Board> newBoards = boards[i].generateLegalMoves(moves);
			for (int i = 0; i < newBoards.size(); i++) {
				net.Activate();
			}
			n += generateBoards(depth + 1, maxDepth, newBoards, moves, net);
		}
	}
	return n;
}

NeuralNetwork makeNetwork(vector<int> layers, bool debug) {
	uniform_real_distribution<double> uniform(-1.0, 1.0);
	default_random_engine engine(std::chrono::high_resolution_clock::now().time_since_epoch().count());

	NeuralNetwork net(layers);
	// initialize inputs
	vector<double> inputs(layers[0]);
	bool first = true;
	for (double & input : inputs) {
		input = uniform(engine);
	}


	// initialize weights
	first = true;
	bool firstG = true;
	for (int i = 1; i < layers.size(); ++i) {
		vector<Neuron> layer(layers[i]);
		for (int j = 0; j < layer.size(); ++j) {
			first = true;
			vector<double> weights(layers[i - 1]);
			for (int k = 0; k < weights.size(); ++k) {
				weights[k] = uniform(engine);
			}
			layer[j].weights = weights;
		}
		// set layer's weights
		net.setWeights(i, layer);
	}

	// set network inputs
	net.setInput(inputs);
	return net;
}

void printGenome(NeuralNetwork net) {
	bool first = true;
	cout << "[";
	for (vector<Neuron> & layer : net.getGenome()) {
		for (Neuron & neuron : layer) {
			for (double & weight : neuron.weights) {
				if (first) {
					cout << weight;
					first = !first;
				} else {
					cout << "," << weight;
				}
			}
		}
	}
	cout << "]" << endl;
}

int main() {

	bool debug = false;
	

	moveMap moves;

	// Time stuff
	std::chrono::high_resolution_clock::time_point t1;
	std::chrono::high_resolution_clock::time_point t2;
	std::chrono::duration<double> timeSpan;

	// random stuff
	uniform_real_distribution<double> uniform(-1.0, 1.0);
	uniform_int_distribution<int> intUniform(0, 19);
	normal_distribution<double> normal(0.0,0.4);
	default_random_engine engine(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	
	
	vector<int> layers{32, 40, 10, 1};
	NeuralNetwork net1 = makeNetwork(layers, debug);
	NeuralNetwork net2 = makeNetwork(layers, debug);
	NeuralNetwork child = spliceNetwork(net1, net2);
	NeuralNetwork evolved = evolveNetwork(net1);

	cout << "network 1: ";
	printGenome(net1);
	cout << "network 2: ";
	printGenome(net2);
	cout << "child: ";
	printGenome(child);
	cout << "evolved: ";
	printGenome(evolved);

	cout << "Board evaluation = ";
	net1.Activate();
	for (double output : net1.outputs) {
		cout << output << endl;
	}

	t1 = std::chrono::high_resolution_clock::now();
	Board initBoard;
	t2 = std::chrono::high_resolution_clock::now();
	timeSpan = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
	cout << "Board creation time: " << timeSpan.count() << endl << initBoard.toString() << endl;

	vector<Board> newBoards = { initBoard };
	int numberOfGens = 8;
	t1 = std::chrono::high_resolution_clock::now();
	int n = generateBoards(0, numberOfGens, newBoards, moves, net);
	t2 = std::chrono::high_resolution_clock::now();
	timeSpan = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

	cout << "Number of boards generated: " << n << endl;
	cout << "Board " <<  numberOfGens << " generations: " << timeSpan.count() << endl;

	int count = 0;
	t1 = std::chrono::high_resolution_clock::now();
	while (count < 1000000) {
		net.Activate();
		++count;
	}
	t2 = std::chrono::high_resolution_clock::now();
	timeSpan = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
	
	cout << "Net evaluations per second: " << count/timeSpan.count() << endl;
	return 0;
}