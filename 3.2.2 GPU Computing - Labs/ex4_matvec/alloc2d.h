#ifndef ALLOC2D_H
#define ALLOC2D_H

// Allocate a 2D array as a contiguous 1D block for better memory locality
double* alloc2d(int rows, int cols);

// Free a 2D array allocated with alloc2d
void free2d(double* ptr);

#endif // ALLOC2D_H
