//	Author: Jonathan Newell
//	Class: CS 441
//  Main.cpp
//  GPU NN Testing
//

//#include "NeuralNetwork.h"
//#include "ThreadPool.h"
//#include "matrixMulCUBLAS.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
using namespace std;
using std::chrono::high_resolution_clock;
using std::chrono::duration;
using std::chrono::duration_cast;

int main() {
	unsigned int width = 4;
	unsigned int height = 5;
	vector<float> testMat(width * height);

	uniform_real_distribution<float> uniform(5, 10);
	default_random_engine engine(std::chrono::high_resolution_clock::now().time_since_epoch().count());

	// initialize Matrix values
	for (int j = 0; j < height; ++j) {
		for (int k = 0; k < width; ++k) {
			testMat[j * width + k] = uniform(engine);
			cout << testMat[j * width + k] << ", ";
		}
		cout << endl;
	}
	cout << endl;
	float *clayer = &testMat[0];
	unsigned int check = width * height;
	for (int i = 0; i < width * height; ++i) {
		cout << "idx: " << i << " - " << clayer[i] << endl;
	}

	return 0;
}