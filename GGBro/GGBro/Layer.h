//  Layer.h
//  GGBro
//
//  Created by Jay Byam on 2/4/16.
//

#ifndef Layer_h
#define Layer_h

#include "Neuron.h"
#include <vector>
using std::vector;
#include <cmath>

class Layer {
public:
    vector<Neuron> neurons;
    vector<double> inputs;
    
    Layer(int numberOfNeurons, int numberOfInputs) {
        this->neurons = * new vector<Neuron>(numberOfNeurons);
        this->inputs = * new vector<double>(numberOfInputs);
        int numberOfWeightsPerNeuron = numberOfInputs + 1;
        for (int i = 0; i < numberOfNeurons; i++) {
            Neuron * newNeuron = new Neuron(numberOfWeightsPerNeuron);
            this->neurons[i] = *newNeuron;
        }
    }
    
    double ActivationFunction(double inputSum) {
        // Steepened Sigmoid Function
        return 1.0 / (1.0 + exp(-3 * inputSum));
    }
};

#endif