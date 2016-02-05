//  Layer.h
//  GGBro
//
//  Created by Jay Byam on 2/4/16.
//

#ifndef Layer_h


#include "Neuron.h"
#include <vector>
using std::vector;

class Layer {
    vector<Neuron> neurons;
    vector<double> inputs;
    
    Layer (int numberOfNeurons, int numberOfInputs) {
        // stuff
    }
};