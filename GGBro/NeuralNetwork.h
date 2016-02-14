//  NeuralNetwork.h
//  GGBro
//
//  Created by Jay Byam on 2/5/16.
//

#ifndef NeuralNetwork_h
#define NeuralNetwork_h

#include "Layer.h"

class NeuralNetwork {
public:
    vector<Layer> layers;
    int numberOfWeights;
    
    NeuralNetwork() {}
    
    NeuralNetwork(vector<int> layers) {
        int numberOfWeights = 0;
        for (int i = 1; i < layers.size(); ++i) {
            this->layers.push_back(Layer(layers[i], layers[i - 1]));
            numberOfWeights += layers[i] * (layers[i - 1] + 1); // For the bias
        }
        this->numberOfWeights = numberOfWeights;
    }
    
    void setWeights(vector<double> genome) {
        int genomeIdx = 0;
        for (auto & layer : layers) {
            for (auto & neuron : layer.neurons) {
                for (auto & weight : neuron.weights) {
                    weight = genome[genomeIdx];
                    ++genomeIdx;
                }
            }
        }
    }
    
    void setInput(vector<double> input) {
        layers[0].inputs = input;
    }
    
    vector<double> Activate() {
        for (int i = 0; i < layers.size(); ++i) {
            layers[i].inputs = layers[i - 1].Activate();
        }
        return layers[layers.size() - 1].Activate();
    }
};


#endif /* NeuralNetwork_h */
