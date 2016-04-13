//  NeuralNetwork.h
//  GGBro
//
//  Created by Jay Byam on 2/5/16.
//

#ifndef NeuralNetwork_h
#define NeuralNetwork_h

#include <iostream>
using std::ostream;
using std::istream;
#include <vector>
using std::vector;
#include <cmath>

//struct Neuron {
//	vector<double> weights;
//	double output;
//};

class NeuralNetwork {
public:
	vector<int> structure;
	vector<vector<vector<double>>> layers;
	vector<vector<double>> outputs;
	
	// default ctor
	NeuralNetwork() {}

	// secondary ctor
	//	takes a vector of ints as a layer map
	NeuralNetwork(vector<int> newLayers) {
		initialize(newLayers);
	}

	// secondary ctor
	//	takes a genome and applys it to this network
	NeuralNetwork(vector<vector<vector<double>>> genome) {
		layers = genome;
		for (vector<vector<double>> & layer : genome) {
			structure.push_back(layer.size());
		}
		int structureLength = structure.size();
		// build outputs vector
		outputs.clear();
		for (int i = 0; i < structureLength; i++) {
			outputs.push_back(vector<double>(structure[i]));
		}
	}
	
	// initialize
	//	takes a vector of ints as a layer map
	void initialize(vector<int> newLayers) {
		structure = newLayers;
		int structureLength = structure.size();
		// clear network
		layers.clear();
		// start building network
		layers.push_back(vector<vector<double>>(newLayers[0]));
		// count number of layers
		for (int i = 1; i < structureLength; ++i) {
			// count number of nuerons in layer
			layers.push_back(vector<vector<double>>(newLayers[i]));
			for (vector<double> & neuron : this->layers.back()) {
				// count number of weights in neuron
				neuron = vector<double>(newLayers[i - 1]);
			}
		}
		// build outputs vector
		outputs.clear();
		for (int i = 0; i < structureLength; i++) {
			outputs.push_back(vector<double>(newLayers[i]));
		}
	}

	// Set Weights
	//	Applys the weights to the given layer
	void setWeights(int layer, vector<vector<double>> & weights) {
		// validate
		if (layer > layers.size()) {
			throw std::invalid_argument( "The layer given is greater than the number of layers in the network.");
		} else if (layer < 0) {
			throw std::invalid_argument( "received negative value for layer" );
		} else if (layer == 0) {
			throw std::invalid_argument( "Cannot set first layer weights. Use \"setInput()\"" );
		}
		// set weights to given layer
		layers[layer] = weights;
	}
	
	// Set Input
	//	Sets the inputs for the network
	void setInput(vector<double> input) {
		if (input.size() != outputs[0].size()) {
			throw std::invalid_argument("The input given has a different size than the input size of the network.");
		}
		for (int i = 0; i < input.size(); ++i) {
			outputs[0][i] = input[i];
		}
	}
	
	// Activiate
	//	Calculates the activation value of the network
	vector<double> Activate() {
		int netSize = layers.size();
		// for each layer in the network
		for (unsigned int i = 1; i<netSize; ++i){
			int layerSize = layers[i].size();
			int preLayerSize = layers[i - 1].size();
			// for each neuron in the layer
			for (unsigned int j = 0; j<layerSize; ++j) {
				// start summation
				double temp = 0.0;
				// for each neuron in the previous layer
				for (unsigned k = 0; k<preLayerSize; ++k) {
					// sum the weights
					temp += outputs[i-1][k] * layers[i][j][k];
				}
				// calculate the output for this layer
				outputs[i][j] = (2.0 / (1.0 + exp(-0.5 * temp))) - 1.0;
			}
		}
		return outputs.back();
	}

	void print() {
		bool first = true;
		cout << "[";
		for (vector<vector<double>> layer : layers) {
			for (vector<double>& neuron : layer) {
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
		cout << "]";
	}

	// Get Genome
	//	return the network's genome
	vector<vector<vector<double>>> getGenome() {
		return layers;
	}
};

// Print Genome
//	prints the genome of the current network
ostream& operator<<(ostream& os, NeuralNetwork& net) {
	for (vector<vector<double>>& layer : net.layers) {
		for (vector<double>& neuron : layer) {
			for (double& weight : neuron) {
				os << weight << " ";
			}
		}
	}
	return os;
}

istream& operator>>(istream& is, NeuralNetwork& net) {
	for (vector<vector<double>>& layer : net.layers) {
		for (vector<double>& neuron : layer) {
			for (double& weight : neuron) {
				is >> weight;
			}
		}
	}
	return is;
}

#endif /* NeuralNetwork_h */
