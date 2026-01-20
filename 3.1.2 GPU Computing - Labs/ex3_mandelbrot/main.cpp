#include "mandel.h"
#include "mandel_offload.h"
#include "writepng.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static double elapsed_seconds(const struct timespec *start,
                              const struct timespec *end) {
  return (double)(end->tv_sec - start->tv_sec) +
         (double)(end->tv_nsec - start->tv_nsec) / 1e9;
}

int main(int argc, char *argv[]) {

  int width, height;
  int max_iter;
  int *image;

  width = 4601;
  height = 4601;
  max_iter = 400;

  // command line argument sets the dimensions of the image
  if (argc == 2)
    width = height = atoi(argv[1]);

  image = (int *)malloc(width * height * sizeof(int));
  if (image == NULL) {
    fprintf(stderr, "memory allocation failed!\n");
    return (1);
  }
  struct timespec t0, t1, t2, t3;
  clock_gettime(CLOCK_MONOTONIC, &t0);

  // First parallel version
  mandel(width, height, image, max_iter);

  clock_gettime(CLOCK_MONOTONIC, &t1);
  mandel_gpu_loop(width, height, image, max_iter);
  clock_gettime(CLOCK_MONOTONIC, &t2);

  mandel_gpu_parallel(width, height, image, max_iter);
  clock_gettime(CLOCK_MONOTONIC, &t3);

  double cpu_time = elapsed_seconds(&t0, &t1);
  double gpu_loop_time = elapsed_seconds(&t1, &t2);
  double gpu_parallel_time = elapsed_seconds(&t2, &t3);
  printf("CPU time:           %.6f s\n", cpu_time);
  printf("GPU loop time:     %.6f s\n", gpu_loop_time);
  printf("GPU parallel time: %.6f s\n", gpu_parallel_time);

  writepng("mandelbrot.png", image, width, height);

  return (0);
}
// OMP_NUM_THREADS=4 ./mandelbrot
