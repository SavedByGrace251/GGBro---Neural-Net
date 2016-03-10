//
//  main.cpp
//  GGBro
//
//  Created by Jay Byam on 2/6/16.
//

#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <random>
#include <thread>
#include "Board.h"
#include "Piece.h"
#include "NeuralNetwork.h"
#include "EvolveNetwork.h"
using namespace std;

// generate boards to a given depth
int generateBoards(std::chrono::high_resolution_clock::time_point start, double maxtime, vector<Board> & boards, moveMap & moves, NeuralNetwork & net, int & depthReached) {
	++depthReached;
	int n = boards.size();
	cout << "depth: " << depthReached << " " << "Number of boards: " << n << endl;
	vector<Board> nextLevel;
	for (int i = 0; i < boards.size(); i++) {
		std::chrono::high_resolution_clock::time_point current = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> timeSpan = std::chrono::duration<double>(current - start);
		if (timeSpan.count() < maxtime) {
			vector<Board> newBoards = boards[i].generateLegalMoves(moves);
			for (int i = 0; i < newBoards.size(); i++) {
				net.Activate();
			}
			nextLevel.insert(nextLevel.end(), newBoards.begin(), newBoards.end());
		}
	}
	if (nextLevel.size() > 0) n += generateBoards(start, maxtime, nextLevel, moves, net, depthReached);
	return n;
}

NeuralNetwork makeNetwork(vector<int> layers) {
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
	for (int i = 1; i < layers.size(); ++i) {
		vector<vector<double>> layer(layers[i]);
		for (int j = 0; j < layer.size(); ++j) {
			vector<double> weights(layers[i - 1]);
			for (int k = 0; k < weights.size(); ++k) {
				weights[k] = uniform(engine);
			}
			layer[j] = weights;
		}
		// set layer's weights
		net.setWeights(i, layer);
	}

	// set network inputs
	net.setInput(inputs);
	return net;
}

void printGenome(NeuralNetwork& net) {
	bool first = true;
	cout << "[";
	for (vector<vector<double>> & layer : net.getGenome()) {
		for (vector<double> & neuron : layer) {
			for (double & weight : neuron) {
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

void testEvolver(vector<int> layers, bool debug) {
	NeuralNetwork net1 = makeNetwork(layers);
	NeuralNetwork net2 = makeNetwork(layers);
	NeuralNetwork child = spliceNetwork(net1, net2);
	NeuralNetwork evolved = evolveNetwork(net1);

	cout << "network 1 genome: ";
	printGenome(net1);
	cout << endl << "network 2 genome: ";
	printGenome(net2);
	cout << endl << "child genome:     ";
	printGenome(child);
	cout << endl << "evolved genome:   ";
	printGenome(evolved);
}

void timeNetwork(NeuralNetwork& net) {
	std::chrono::high_resolution_clock::time_point t1;
	std::chrono::high_resolution_clock::time_point t2;
	std::chrono::duration<double> timeSpan;

	int count = 0;
	t1 = std::chrono::high_resolution_clock::now();
	while (count < 250000) {
		net.Activate();
		++count;
	}
	t2 = std::chrono::high_resolution_clock::now();
	timeSpan = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

	cout << "Net evaluations per second: " << count / timeSpan.count() << endl;
}

void timeBoardGenerator(NeuralNetwork& net) {
	std::chrono::high_resolution_clock::time_point t1;
	std::chrono::high_resolution_clock::time_point t2;
	std::chrono::duration<double> timeSpan;

	moveMap moves;
	t1 = std::chrono::high_resolution_clock::now();
	Board initboard;
	t2 = std::chrono::high_resolution_clock::now();
	timeSpan = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
	cout << "board creation time: " << timeSpan.count() << endl << initboard.toString() << endl;

	vector<Board> newboards = { initboard };
	double computetime = 14.6;
	int depthreached = -1;
	t1 = std::chrono::high_resolution_clock::now();
	int n = generateBoards(t1, computetime, newboards, moves, net, depthreached);
	t2 = std::chrono::high_resolution_clock::now();
	timeSpan = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

	cout << "number of boards generated: " << n << endl;
	cout << "depth of boards reached: " << depthreached << endl;
	cout << "board generation time: " << timeSpan.count() << endl;
}

int main() {
	vector<int> layers{32, 40, 10, 1};
	NeuralNetwork net1 = makeNetwork(layers);
	cout << "Board evaluation = ";
	net1.Activate();
	for (double output : net1.outputs.back()) {
		cout << output << endl;
	}
	
	//testEvolver();

	//timeBoardGenerator(net1);

	//timeNetwork(net1);
	
    Board doubleJump("______________r__bb_______b_____", true);
    moveMap moves;
    vector<Board> jumps = doubleJump.generateLegalMoves(moves);
    for (Board jump : jumps) {
        cout << jump.toString() << endl;
    }
    

	return 0;
}