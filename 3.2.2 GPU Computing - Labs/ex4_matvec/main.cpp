#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matvec.h"
#include "matvec_offload.h"
#include "alloc2d.h"

static double elapsed_seconds(const struct timespec *start,
                              const struct timespec *end) {
  return (double)(end->tv_sec - start->tv_sec) +
         (double)(end->tv_nsec - start->tv_nsec) / 1e9;
}

// Initialize matrix A with simple values
static void init_matrix(double *A, int rows, int cols) {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			A[i * cols + j] = (double)(i + j);
		}
	}
}


// Initialize vector x with simple values
static void init_vector(double *x, int n) {
	for (int i = 0; i < n; ++i) {
		x[i] = (double)i;
	}
}

// Verify results between CPU and GPU versions
static int verify_results(const double *y_cpu, const double *y_gpu, int n, double tolerance) {
	for (int i = 0; i < n; ++i) {
		double diff = y_cpu[i] - y_gpu[i];
		if (diff < 0) diff = -diff;
		if (diff > tolerance) {
			printf("Mismatch at index %d: CPU=%.6f, GPU=%.6f\n", i, y_cpu[i], y_gpu[i]);
			return 0;
		}
	}
	return 1;
}


int main(int argc, char **argv) {
	int n = 5000;  // default matrix/vector size
	if (argc > 1) {
		n = atoi(argv[1]);
		if (n <= 0) {
			fprintf(stderr, "N must be positive\n");
			return EXIT_FAILURE;
		}
	}

	printf("Matrix-Vector Multiplication Baseline\n");
	printf("Matrix size: %d x %d\n\n", n, n);

	// Allocate matrix A (n x n) and vectors x, y
	double *A = alloc2d(n, n);
	double *x = alloc2d(n, 1);
	double *y_cpu = alloc2d(n, 1);
	double *y_gpu = alloc2d(n, 1);
	double *y_gpu_notransfer = alloc2d(n, 1);

	if (!A || !x || !y_cpu || !y_gpu || !y_gpu_notransfer) {
		fprintf(stderr, "Memory allocation failed\n");
		free2d(A);
		free2d(x);
		free2d(y_cpu);
		free2d(y_gpu);
		free2d(y_gpu_notransfer);
		return EXIT_FAILURE;
	}

	// Initialize data
	init_matrix(A, n, n);
	init_vector(x, n);

	// Time all versions with external timing
	struct timespec t0, t1, t2, t3;
	clock_gettime(CLOCK_MONOTONIC, &t0);

	// Run CPU version with OpenMP
	matvec_cpu(A, x, y_cpu, n, n);

	clock_gettime(CLOCK_MONOTONIC, &t1);

	// Run GPU version with data transfer
	matvec_gpu(A, x, y_gpu, n, n);

	clock_gettime(CLOCK_MONOTONIC, &t2);

	// Run GPU version without data transfer
	matvec_gpu_no_transfer(A, x, y_gpu_notransfer, n, n);

	clock_gettime(CLOCK_MONOTONIC, &t3);

	// Calculate elapsed times
	double time_cpu = elapsed_seconds(&t0, &t1);
	double time_gpu = elapsed_seconds(&t1, &t2);
	double time_gpu_notransfer = elapsed_seconds(&t2, &t3);

	// Print results
	printf("CPU time:                    %.6f s\n", time_cpu);
	printf("GPU time (with transfer):    %.6f s\n", time_gpu);
	printf("GPU time (no transfer):      %.6f s\n", time_gpu_notransfer);
	printf("\nSpeedup (with transfer):     %.2fx\n", time_cpu / time_gpu);
	printf("Speedup (no transfer):       %.2fx\n", time_cpu / time_gpu_notransfer);
	printf("Data transfer overhead:      %.6f s\n", time_gpu - time_gpu_notransfer);

	// Cleanup
	free2d(A);
	free2d(x);
	free2d(y_cpu);
	free2d(y_gpu);
	free2d(y_gpu_notransfer);

	return EXIT_SUCCESS;
}
