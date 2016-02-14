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
    
    Layer(int numberOfNeurons, int numberOfInputs) {
        this->neurons = vector<Neuron>(numberOfNeurons);
        this->inputs = vector<double>(numberOfInputs);
        int numberOfWeightsPerNeuron = numberOfInputs + 1;
        for (int i = 0; i < numberOfNeurons; i++) {
            Neuron newNeuron = Neuron(numberOfWeightsPerNeuron);
            this->neurons[i] = newNeuron;
        }
    }
    
    vector<double> Activate() {
        vector<double> output(neurons.size());
        for (auto & neuron : neurons) {
            double inputSum = neuron.sumInputs(inputs);
            output.push_back(ActivationFunction(inputSum));
        }
        return output;
    }
    
    double ActivationFunction(double inputSum) {
        // Steepened Sigmoid Function
        return 1.0 / (1.0 + exp(-3 * inputSum));
    }
};

#endif