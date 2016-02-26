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
    vector<vector<double>> weights;
    vector<double> inputs;
	vector<double> outputs;
    
    Layer(int numberOfNeurons, int numberOfInputs) {
        int numberOfWeightsPerNeuron = numberOfInputs + 1;
        for (int i = 0; i < numberOfNeurons; i++) {
            weights.push_back(vector<double>(numberOfWeightsPerNeuron));
        }
		outputs = vector<double>(numberOfNeurons);
    }
    
    size_t size() {
        return weights.size();
    }
};

#endif