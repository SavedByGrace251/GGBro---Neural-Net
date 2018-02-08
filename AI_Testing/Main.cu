// incrementArray.cu
#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include "NeuralNetwork.cu.h"
using std::chrono::high_resolution_clock;
using std::chrono::duration;
using std::chrono::duration_cast;

int main(void)
{
	std::uniform_real_distribution<double> uniform(-5.0, 5.0);
	std::default_random_engine engine(std::chrono::high_resolution_clock::now().time_since_epoch().count());

	//Initialize Neural Net
	vector<int> structure{ 32, 40, 10, 1 };
	NeuralNetwork TestNet(structure);
	// Load data into neural net

	vector<vector<float>> genome = TestNet.getGenome();
	for (int i = 0; i < genome.size(); i++) {
		for (int j = 0; j < genome[i].size(); j++)
		{
			genome[i][j] = uniform(engine);
		}
	}
	// set inputs
	
	vector<float> input(structure[0]);
	for (int i = 0; i < structure[0]; i++) {
		input[i] = uniform(engine);
	}
	TestNet.setInput(input);
	
	high_resolution_clock::time_point t1;
	high_resolution_clock::time_point t2;
	duration<double> timeSpan;

	int count = 0;
	t1 = high_resolution_clock::now();
	float output = 0;
	while (count < 10000) {
		output = TestNet.Activate()[0];
		++count;
		if (count % 1000 == 0) {
			std::cout << count << std::endl;
		}
	}
	std::cout << output << std::endl;
	t2 = high_resolution_clock::now();
	timeSpan = duration_cast<duration<double>>(t2 - t1);

	std::cout << "Net evaluations per second: " << count / timeSpan.count() << std::endl;

	return 0;
}