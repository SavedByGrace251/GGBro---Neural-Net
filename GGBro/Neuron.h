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
    double output;
    
    Neuron() {}
    
    Neuron(int numberOfWeights) {
        weights = vector<double>(numberOfWeights);
    }
};

#endif