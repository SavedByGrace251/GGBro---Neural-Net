//	Authors: Jay Byam, Jonathan Newell
//
//  NeuralNetwork.h
//  GGBro
//

#ifndef NeuralNetwork_h
#define NeuralNetwork_h
// Utilities and system includes
#include <assert.h>
#include <helper_string.h>  // helper for shared functions common to CUDA Samples

// CUDA runtime
#include <cuda_runtime.h>
#include <cublas_v2.h>

// CUDA and CUBLAS functions
#include <helper_functions.h>
#include <helper_cuda.h>

#include <device_functions.h>
#include <device_launch_parameters.h>

#include <iostream>
using std::ostream;
using std::istream;
#include <vector>
using std::vector;
#include <cmath>

__global__ void NN_OnDevice(float *input, float *weights, float *output, int N)
{
	int idx = threadIdx.x;
	float temp = 0;
	for (int j = 0; j<N; j++) {
		temp += input[j] * weights[idx*N + j];
	}
	output[idx] = (2.0 / (1.0 + exp(-0.5 * temp))) - 1.0;
}

void CUDA_MatrixMul(float *input, float *weights, float *output, int N_input, int N_output) {
	cudaSetDevice(0);
	
	float *input_d, *weights_d, *output_d;
	size_t i_size = N_input * sizeof(float);
	size_t o_size = N_output * sizeof(float);

	// allocate array on device 
	checkCudaErrors(cudaMalloc((void **)&input_d, i_size));
	checkCudaErrors(cudaMalloc((void **)&weights_d, i_size*o_size));
	checkCudaErrors(cudaMalloc((void **)&output_d, o_size));

	checkCudaErrors(cudaMemcpy(input_d, input, i_size, cudaMemcpyHostToDevice));
	checkCudaErrors(cudaMemcpy(weights_d, weights, i_size*o_size, cudaMemcpyHostToDevice));

	NN_OnDevice <<< 1, N_output >>> (input_d, weights_d, output_d, N_input);
	// block until the device has completed
	cudaThreadSynchronize();
	// copy results back from GPU
	checkCudaErrors(cudaMemcpy(output, output_d, o_size, cudaMemcpyDeviceToHost));
	// clear GPU memory
	checkCudaErrors(cudaFree(input_d));
	checkCudaErrors(cudaFree(weights_d));
	checkCudaErrors(cudaFree(output_d));
}

class NeuralNetwork {
public:
	vector<int> structure;
	vector<vector<float>> layers;
	vector<vector<float>> outputs;
	
	// default ctor
	NeuralNetwork() {}

	// secondary ctor
	//	takes a vector of ints as a layer map
	NeuralNetwork(vector<int> newLayers) {
		initialize(newLayers);
	}

	// secondary ctor
	//	takes a genome and applys it to this network
	NeuralNetwork(vector<vector<float>> genome) {
		layers = genome;
		for (vector<float> & layer : genome) {
			structure.push_back(layer.size());
		}
		int structureLength = structure.size();
		// build outputs vector
		outputs.clear();
		for (int i = 0; i < structureLength; i++) {
			outputs.push_back(vector<float>(structure[i]));
		}
	}
	
	// initialize
	//	takes a vector of ints as a layer map
	void initialize(vector<int> newLayers) {
		structure = newLayers;
		int structureLength = structure.size();
		// clear network
		layers.clear();
		// start building network
		// count number of layers
		for (int i = 1; i < structureLength; ++i) {
			// count number of nuerons in layer
			layers.push_back(vector<float>(newLayers[i - 1]*newLayers[i]));
		}
		// build outputs vector
		outputs.clear();
		for (int i = 0; i < structureLength; i++) {
			outputs.push_back(vector<float>(newLayers[i]));
		}
	}

	// Set Weights
	//	Applys the weights to the given layer
	void setWeights(int layer, vector<float> & weights) {
		// validate
		if (layer > layers.size()) {
			throw std::invalid_argument( "The layer given is greater than the number of layers in the network.");
		} else if (layer < 0) {
			throw std::invalid_argument( "received negative value for layer" );
		} else if (layer == 0) {
			throw std::invalid_argument( "Cannot set first layer weights. Use \"setInput()\"" );
		}
		// set weights to given layer
		layers[layer] = weights;
	}
	
	// Set Input
	//	Sets the inputs for the network
	void setInput(vector<float> input) {
		if (input.size() != outputs[0].size()) {
			throw std::invalid_argument("The input given has a different size than the input size of the network.");
		}
		for (int i = 0; i < input.size(); ++i) {
			outputs[0][i] = input[i];
		}
	}
	
	// Activiate
	//	Calculates the activation value of the network
	vector<float> Activate() {
		int netSize = layers.size();
		// for each layer in the network
		for (unsigned int i = 1; i<netSize; ++i){
			int outputSize = structure[i];
			int inputSize = structure[i - 1];

			float *input = &outputs[i - 1][0];
			float *weights = &layers[i][0];
			float *output = &outputs[i][0];

			CUDA_MatrixMul(input, weights, output, inputSize, outputSize);
		}
		return outputs.back();
	}

	void print() { 
		bool first = true;
		std::cout << "[";
		for (vector<float> layer : layers) {
			for (float & weight : layer) {
				if (first) {
					std::cout << weight;
					first = !first;
				} else {
					std::cout << "," << weight;
				}
			}
		}
		std::cout << "]";
	}

	// Get Genome
	//	return the network's genome
	vector<vector<float>> getGenome() {
		return layers;
	}
};

// Print Genome
//	prints the genome of the current network
ostream& operator<<(ostream& os, NeuralNetwork& net) {
	for (vector<float>& layer : net.layers) {
		for (float& weight : layer) {
			os << weight << " ";
		}
	}
	return os;
}

istream& operator>>(istream& is, NeuralNetwork& net) {
	for (vector<float>& layer : net.layers) {
		for (float& weight : layer) {
			is >> weight;
		}
	}
	return is;
}

#endif /* NeuralNetwork_h */
