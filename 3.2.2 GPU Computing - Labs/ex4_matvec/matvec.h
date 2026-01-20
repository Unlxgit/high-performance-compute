#ifndef MATVEC_H
#define MATVEC_H

// Matrix-vector multiplication using CPU with OpenMP parallelization
void matvec_cpu(const double *A, const double *x, double *y, int rows, int cols);

#endif // MATVEC_H
