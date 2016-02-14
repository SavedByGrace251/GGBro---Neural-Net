//
//  DataSet.h
//  GGBro
//
//  Created by Jay Byam on 2/13/16.
//

#ifndef DataSet_h
#define DataSet_h

#include <vector>
using std::vector;

class DataSet {
public:
    vector<vector<double>> inputs;
    vector<vector<double>> expectedOutputs;
    
    void Add(vector<double> inputs, vector<double> expectedOutputs) {
        this->inputs.push_back(inputs);
        this->expectedOutputs.push_back(expectedOutputs);
    }
    
    int numberOfOutputs() {
        if (expectedOutputs.size() > 0) return (int)expectedOutputs[0].size();
        return 0;
    }
};

#endif /* DataSet_h */
