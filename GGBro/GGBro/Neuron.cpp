//  Neuron.cpp
//  GGBro
//
//  Created by Jay Byam on 2/4/16.

#include <iostream>
#include <list>
using std::list;


class Neuron {
public:
    list<double> weights;
    
    Neuron(int numberOfWeights) {
        this->weights = *new list<double> (numberOfWeights);
    }
    
    
};
