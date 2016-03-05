//  NeuralNetwork.h
//  GGBro
//
//  Created by Jay Byam on 2/5/16.
//

#ifndef NeuralNetwork_h
#define NeuralNetwork_h

#include <iostream>
#include <vector>
using std::vector;
#include <cmath>

struct Neuron {
    vector<double> weights;
    double output;
};

class NeuralNetwork {
public:
    vector<vector<Neuron>> layers;
	vector<double> outputs;
    
	// default ctor
	NeuralNetwork() {}

	// secondary ctor:
	//	takes a vector of ints as a layer map
    NeuralNetwork(vector<int> newLayers) {
		initialize(newLayers);
    }

	// secondary ctor:
	//	takes a genome and applys it to this network
	NeuralNetwork(vector<vector<Neuron>> genome) {
		this->layers = genome;
	}
    
	// initialize:
	//	takes a vector of ints as a layer map
	void initialize(vector<int> newLayers) {
		// clear network
		layers.clear();
		// start building network
		layers.push_back(vector<Neuron>(newLayers[0]));
		// count number of layers
		for (int i = 1; i<newLayers.size(); ++i) {
			// count number of nuerons in layer
			layers.push_back(vector<Neuron>(newLayers[i]));
			for (Neuron & neuron : this->layers.back()) {
				// count number of weights in neuron
				neuron.weights = vector<double>(newLayers[i - 1]);
			}
		}
	}

	// Set Weights:
	//	Applys the weights to the given layer
    void setWeights(int layer, vector<Neuron> & weights) {
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
		// validate
		if (layers.size() < 1) {
			throw std::invalid_argument("You must initialize the network before setting the imputs.");
		}
		// set inputs
        layers[0] = vector<Neuron>(input.size());
        for (int i = 0; i < input.size(); ++i) {
            layers[0][i].output = input[i];
        }
    }
    
	// Activiate
	//	Calculates the activation value of the network
    void Activate() {
		// for each layer in the network
        for (unsigned int i = 1; i<layers.size(); ++i){
			// for each neuron in the layer
            for (unsigned int j = 0; j<layers[i].size(); ++j) {
				// start summation
                double temp = 0.0;
				// for each neuron in the previous layer
                for (unsigned k = 0; k<layers[i-1].size(); ++k) {
					// sum the weights
                    temp += layers[i-1][k].output * layers[i][j].weights[k];
                }
				// calculate the output for this layer
                layers[i][j].output = 1.0 / (1.0 + exp(-0.5 * temp));
            }
        }
		// set new network outputs
		outputs.clear();
        for (Neuron & neuron : layers.back()) {
            outputs.push_back(neuron.output);
        }
    }

	// Get Genome
	//	return the network's genome
	vector<vector<Neuron>> getGenome() {
		return layers;
	}
};


#endif /* NeuralNetwork_h */
