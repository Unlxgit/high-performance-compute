#include "alloc2d.h"
#include <stdlib.h>

// Allocate a 2D array as a contiguous 1D block for better memory locality
double* alloc2d(int rows, int cols) {
    return (double*)malloc(rows * cols * sizeof(double));
}

// Free a 2D array allocated with alloc2d
void free2d(double* ptr) {
    free(ptr);
}
