//
//  EvolveNetwork.h
//  GGBro
//
//  Created by Jay Byam on 2/13/16.
//

#ifndef EvolveNetwork_h
#define EvolveNetwork_h

#include "NeuralNetwork.h"
#include <chrono>
#include <iostream>
using std::cout;
using std::endl;
#include <random>
using std::uniform_real_distribution;
using std::uniform_int_distribution;
using std::normal_distribution;
using std::default_random_engine;

// takes a parent network and evolves the weights to make a new child network
NeuralNetwork evolveNetwork(NeuralNetwork& parent) {
	vector<vector<Neuron>> genome = parent.getGenome();
	normal_distribution<double> normal(0.0, 0.4);
	default_random_engine generator(std::chrono::high_resolution_clock::now().time_since_epoch().count());

	for (vector<Neuron> & layer : genome) {
		for (Neuron & neuron : layer) {
			for (double & weight : neuron.weights) {
				weight += normal(generator);
			}
		}
	}
	return NeuralNetwork(genome);
}

// takes two parent networks and splices them together to make a new child network
NeuralNetwork spliceNetwork(NeuralNetwork& momNet, NeuralNetwork& dadNet) {
	vector<vector<Neuron>> momGenome = momNet.getGenome();
	vector<vector<Neuron>> dadGenome = dadNet.getGenome();
	// validation
	if (momGenome.size() != dadGenome.size()) throw std::invalid_argument("The two networks given are different and connot produce a child.");
	for (int i = 0; i < momGenome.size(); i++) {
		if (momGenome[i].size() != dadGenome[i].size()) throw std::invalid_argument("The two networks given are different and connot produce a child.");
	}
	// set random engines
	uniform_int_distribution<int> flipFlop(0, 1);
	default_random_engine generator(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	vector<vector<Neuron>> child;
	// set layer 0 gene to child
	child.push_back(momGenome[0]);
	// start gene splicing
	for (int i = 1; i < momGenome.size(); ++i) {
		vector<Neuron> gene(momGenome[i].size());
		// determin splice spot
		uniform_int_distribution<int> splice(0, momGenome[i].size() - 1);
		int spliceSpot = splice(generator);
		// decide dad splice or mom splice
		if (flipFlop(generator) == 1) {
			// do dad splice
			for (int j = 0; j < gene.size(); j++) {
				if (j < spliceSpot) {
					gene[j] = dadGenome[i][j];
				} else {
					gene[j] = momGenome[i][j];
				}
			}
		} else {
			// do mom splice
			for (int j = 0; j < gene.size(); j++) {
				if (j > spliceSpot) {
					gene[j] = dadGenome[i][j];
				} else {
					gene[j] = momGenome[i][j];
				}
			}
		}
		// add gene to child
		child.push_back(gene);
	}
	
	return NeuralNetwork(child);
}

#endif /* EvolveNetwork_h */
