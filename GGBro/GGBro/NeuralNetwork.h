//  NeuralNetwork.h
//  GGBro
//
//  Created by Jay Byam on 2/5/16.
//

#ifndef NeuralNetwork_h
#define NeuralNetwork_h

#include "Layer.h"
#include <vector>
using std::vector;
#include <stdarg.h>

class NeuralNetwork {
public:
    vector<Layer> layers;
    int numberOfWeights;
    
    NeuralNetwork(vector<int> layersList, ... ) {
//        va_list vl;
//        this->layers = vl;
//        int numberOfWeights = 0;
//        for (int i = 0; i < va_list.Length; i++) {
//            
//        }
    }
    
};


#endif /* NeuralNetwork_h */
