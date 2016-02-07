//  Neuron.h
//  GGBro
//
//  Created by Jay Byam on 2/4/16.

#ifndef Neuron_h
#define Neuron_h

#include <iostream>
#include <vector>
using std::vector;

class Neuron {
public:
    vector<double> weights;
    
    Neuron(int numberOfWeights) {
        this->weights = *new vector<double>(numberOfWeights);
    }
    
    double sumInputs(vector<double> inputs) {
        double sumOfInputs = 0.0;
        sumOfInputs += 1 * this->weights[0]; // Add bias
        for (int i = 0; i < inputs.size(); i++) {
            sumOfInputs += inputs[i] * this->weights[i + 1];
        }
        return sumOfInputs;
    }
};

#endif