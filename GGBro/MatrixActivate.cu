// incrementArray.cu
// Utilities and system includes
#include <assert.h>
#include <helper_string.h>  // helper for shared functions common to CUDA Samples

// CUDA runtime
#include <cuda.h>
#include <cuda_runtime.h>
#include <cuda_runtime_api.h>
#include <device_launch_parameters.h>
#include <device_functions.h>
#include <cublas_v2.h>

// CUDA and CUBLAS functions
#include <helper_functions.h>
#include <helper_cuda.h>
//-----------------------------------------------------------------------------------

void NN_OnHost(float *activity, float *weights, int N)
{
	int i, j;
	float new_activity[N];
	for (i = 0; i<N; i++) {
		new_activity[i] = 0;
		for (j = 0; j<N; j++) {
			new_activity[i] += activity[j] * weights[(j*N) + i];
		}
	}
	for (i = 0; i < N; i++) {
		activity[i] = 1 / (1 + exp(-new_activity[i]));
	}
}
//-----------------------------------------------------------------------------------

__global__ void NN_OnDevice(float *activity, float *weights, float *new_activity, int N)
{
	int j, idx = threadIdx.x;
	new_activity[idx] = 0;
	for (j = 0; j<N; j++) {
		new_activity[idx] += activity[j] * weights[(j*N) + idx];
	}
	__syncthreads();
	activity[idx] = 1 / (1 + exp(-new_activity[idx]));
}
//-----------------------------------------------------------------------------------

int main(void)
{
	cudaSetDevice(0);
	float *activity_h, *weights_h, *new_activity_h;		   // pointers to host memory
	float *activity_d, *weights_d, *new_activity_d;		   // pointer to device memory
	int i, j, N = 100;
	size_t size = N * sizeof(float);

	//timer stuff
	cudaEvent_t start, stop;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);

	// allocate arrays on host
	activity_h = (float *)malloc(size);
	new_activity_h = (float *)malloc(size);
	weights_h = (float *)malloc(size*size);

	// allocate array on device 
	cudaMalloc((void **)&activity_d, size);
	cudaMalloc((void **)&new_activity_d, size);
	cudaMalloc((void **)&weights_d, size*size);

	// initialization of host data
	for (i = 0; i<N; i++) {
		activity_h[i] = (float(rand() % 100) / 100);
		for (j = 0; j<N; j++) {
			weights_h[(j*N) + i] = (float(rand() % 200) / 100) - 1;
			//printf("%f ",weights_h[(j*N)+i]);
		}
		//printf("%f ",activity_h[i]);
	}
	//printf("\n");

	// copy data from host to device
	cudaMemcpy(activity_d, activity_h, sizeof(float)*N, cudaMemcpyHostToDevice);
	cudaMemcpy(weights_d, weights_h, sizeof(float)*N*N, cudaMemcpyHostToDevice);

	// do calculation on host
	NN_OnHost(activity_h, weights_h, N);

	for (i = 0; i<10; i++) printf("%f ", activity_h[i]);
	printf("\n");

	//start timer 
	cudaEventRecord(start, 0);

	// do calculation on device:	
	NN_OnDevice <<< 1, N >>> (activity_d, weights_d, new_activity_d, N);

	// block until the device has completed
	cudaThreadSynchronize();

	//end timer
	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);
	float elapsedTime;
	cudaEventElapsedTime(&elapsedTime, start, stop);

	// Retrieve result from device and store in b_h
	cudaMemcpy(new_activity_h, activity_d, sizeof(float)*N, cudaMemcpyDeviceToHost);

	for (i = 0; i<10; i++) printf("%f ", new_activity_h[i]);
	printf("\n");
	printf("time = %f\n\n", elapsedTime);

	// cleanup
	free(activity_h); free(weights_h); free(new_activity_h);
	cudaFree(activity_d); cudaFree(weights_d); cudaFree(new_activity_d);
	cudaEventDestroy(start);
	cudaEventDestroy(stop);
}