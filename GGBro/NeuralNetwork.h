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
    int numberOfWeights;
    
    NeuralNetwork(vector<int> newLayers) {
        this->layers.push_back(vector<Neuron> (newLayers[0]));
        for (int i = 1; i<newLayers.size(); ++i) {
            this->layers.push_back(vector<Neuron>(newLayers[i]));
            for (auto & neuron : this->layers.back()){
                neuron.weights = vector<double>(newLayers[i-1]);
            }
        }
    }
    
    void setWeights(int layer, vector<Neuron> & weights) {
        if (layer > layers.size()) {
            throw std::invalid_argument( "The layer given is greater than the number of layers in the network.");
        } else if (layer < 0) {
            throw std::invalid_argument( "received negative value" );
        } else if (layer == 0) {
            throw std::invalid_argument( "Cannot set first layer weights. Use \"setInput()\"" );
        }
        layers[layer] = weights;
    }
    
    void setInput(vector<double> input) {
        layers[0] = vector<Neuron>(input.size());
        for (int i = 0; i < input.size(); ++i) {
            layers[0][i].output = input[i];
        }
    }
    
    vector<double> Activate() {
        for (unsigned int i = 1; i<layers.size(); ++i){
            for (unsigned int j = 0; j<layers[i].size(); ++j) {
                double temp = 0.0;
                for (unsigned k = 0; k<layers[i-1].size(); ++k) {
                    temp += layers[i-1][k].output * layers[i][j].weights[k];
                }
                layers[i][j].output = ActivationFunction(temp);
            }
        }
        vector<double> outputs;
        for (auto & neuron : layers.back()) {
            outputs.push_back(neuron.output);
        }
        return outputs;
    }
    
    
    
    double ActivationFunction(double inputSum) {
        // Flatened Sigmoid Function
        return 1.0 / (1.0 + exp(-0.25 * inputSum));
    }
};


#endif /* NeuralNetwork_h */
