//
//  Individual.h
//  GGBro
//
//  Created by Jay Byam on 2/13/16.
//  Copyright © 2016 Jay Byam. All rights reserved.
//

#ifndef Individual_h
#define Individual_h

#include <vector>
using std::vector;

class Individual {
public:
    double fitness;
    vector<double> genome;
};

#endif /* Individual_h */
