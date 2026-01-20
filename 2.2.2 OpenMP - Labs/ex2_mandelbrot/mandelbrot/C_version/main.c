#include "mandel.h"
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
  	struct timespec t0, t1, t2;
	clock_gettime(CLOCK_MONOTONIC, &t0);
#pragma omp parallel
  {
    mandel(width, height, image, max_iter);
  }
  	clock_gettime(CLOCK_MONOTONIC, &t1);
    //mandel(width, height, image, max_iter);
  	//clock_gettime(CLOCK_MONOTONIC, &t2);


    printf("First parallel mandel() call elapsed (s): %.6f\n",
           elapsed_seconds(&t0, &t1));
    //printf("Second serial mandel() call elapsed (s): %.6f\n",
    //       elapsed_seconds(&t1, &t2));


  writepng("mandelbrot.png", image, width, height);

  return (0);
}
// OMP_NUM_THREADS=4 ./mandelbrot 
