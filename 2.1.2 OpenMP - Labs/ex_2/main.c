#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

// Matrix-vector multiplication: y = A * x
static void matvec(const double *A, const double *x, double *y, int rows, int cols) {
	double sum;
	#pragma omp parallel for default(none) \
              shared(rows,cols,A,x,y) private(sum)
	for (int i = 0; i < rows; ++i) {
		sum = 0.0;
		for (int j = 0; j < cols; ++j) {
			sum += A[i * cols + j] * x[j];
		}
		y[i] = sum;
	}
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

	// Allocate matrix A (n x n) and vectors x, y
	double *A = (double *)malloc(n * n * sizeof(double));
	double *x = (double *)malloc(n * sizeof(double));
	double *y = (double *)malloc(n * sizeof(double));

	if (!A || !x || !y) {
		fprintf(stderr, "Memory allocation failed\n");
		free(A);
		free(x);
		free(y);
		return EXIT_FAILURE;
	}

	// Initialize data
	init_matrix(A, n, n);
	init_vector(x, n);

	// Time the matrix-vector multiplication
	struct timespec t0, t1;
	clock_gettime(CLOCK_MONOTONIC, &t0);
	matvec(A, x, y, n, n);
	clock_gettime(CLOCK_MONOTONIC, &t1);

	// Print results
	printf("Matrix size:  %d x %d\n", n, n);
	printf("First y[0]:   %.6f\n", y[0]);
	printf("Last y[%d]:  %.6f\n", n - 1, y[n - 1]);
	printf("elapsed (s):  %.6f\n", elapsed_seconds(&t0, &t1));

	// Cleanup
	free(A);
	free(x);
	free(y);

	return EXIT_SUCCESS;
}
