//  Layer.h
//  GGBro
//
//  Created by Jay Byam on 2/4/16.
//

#ifndef Layer_h
#define Layer_h

#include "Neuron.h"
#include <cmath>

class Layer {
public:
    vector<Neuron> neurons;
    vector<double> inputs;
	vector<double> outputs;
    
    Layer(int numberOfNeurons, int numberOfInputs) {
        this->inputs = vector<double>(numberOfInputs);
        int numberOfWeightsPerNeuron = numberOfInputs + 1;
        for (int i = 0; i < numberOfNeurons; i++) {
            this->neurons.push_back(Neuron(numberOfWeightsPerNeuron));
        }
		outputs = vector<double>(neurons.size());
    }
    
    vector<double> Activate() {
		int idx = 0;
        for (auto & neuron : neurons) {
            double inputSum = neuron.sumInputs(inputs);
            outputs[idx++] = ActivationFunction(inputSum);
        }
        return outputs;
    }
    
    double ActivationFunction(double inputSum) {
        // Flatened Sigmoid Function
        return 1.0 / (1.0 + exp(-0.25 * inputSum));
    }
};

#endif