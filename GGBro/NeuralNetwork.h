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

//struct Neuron {
//    vector<double> weights;
//	double output;
//};

class NeuralNetwork {
public:
    vector<vector<vector<double>>> layers;
	vector<vector<double>> outputs;
    
	// default ctor
	NeuralNetwork() {}

	// secondary ctor:
	//	takes a vector of ints as a layer map
    NeuralNetwork(vector<int> newLayers) {
		initialize(newLayers);
    }

	// secondary ctor:
	//	takes a genome and applys it to this network
	NeuralNetwork(vector<vector<vector<double>>> genome) {
		this->layers = genome;
	}
    
	// initialize:
	//	takes a vector of ints as a layer map
	void initialize(vector<int> newLayers) {
		// clear network
		layers.clear();
		// start building network
		layers.push_back(vector<vector<double>>(newLayers[0]));
		// count number of layers
		for (int i = 1; i<newLayers.size(); ++i) {
			// count number of nuerons in layer
			layers.push_back(vector<vector<double>>(newLayers[i]));
			for (vector<double> & neuron : this->layers.back()) {
				// count number of weights in neuron
				neuron = vector<double>(newLayers[i - 1]);
			}
		}
		// build outputs vector
		outputs.clear();
		for (int i = 0; i < newLayers.size(); i++) {
			outputs.push_back(vector<double>(newLayers[i]));
		}
	}

	// Set Weights:
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
                outputs[i][j] = 1.0 / (1.0 + exp(-0.5 * temp));
            }
        }
		return outputs.back();
    }

	// Get Genome
	//	return the network's genome
	vector<vector<vector<double>>> getGenome() {
		return layers;
	}
};


#endif /* NeuralNetwork_h */
