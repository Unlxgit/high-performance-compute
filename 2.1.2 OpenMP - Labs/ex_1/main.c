// Compute pi via midpoint integration of 4 / (1 + x^2)
// Build serial:   gcc -O3 main.c -o pi_serial
// Auto-parallel:  gcc -O3 -ffast-math -ftree-parallelize-loops=4 main.c -o pi_auto

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static double integrand(double x) {
	return 4.0 / (1.0 + x * x);
}

static double compute_pi(long n) {
	const double step = 1.0 / (double)n;
	double sum = 0.0;

	for (long i = 0; i < n; ++i) {
		const double x = (i + 0.5) * step;
		sum += integrand(x);
	}

	return step * sum;
}

static double elapsed_seconds(const struct timespec *start,
							  const struct timespec *end) {
	return (double)(end->tv_sec - start->tv_sec) +
		   (double)(end->tv_nsec - start->tv_nsec) / 1e9;
}

int main(int argc, char **argv) {
	long n = 10000000;  // default number of intervals
	if (argc > 1) {
		n = strtol(argv[1], NULL, 10);
		if (n <= 0) {
			fprintf(stderr, "N must be positive\n");
			return EXIT_FAILURE;
		}
	}

	struct timespec t0, t1;
	clock_gettime(CLOCK_MONOTONIC, &t0);
	const double pi_est = compute_pi(n);
	clock_gettime(CLOCK_MONOTONIC, &t1);

	printf("N = %ld\n", n);
	printf("pi estimate   = %.15f\n", pi_est);
	printf("abs error     = %.3e\n", fabs(pi_est - M_PI));
	printf("elapsed (s)   = %.6f\n", elapsed_seconds(&t0, &t1));

	return EXIT_SUCCESS;
}
