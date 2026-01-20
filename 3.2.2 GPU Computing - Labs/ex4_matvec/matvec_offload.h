#ifndef MATVEC_OFFLOAD_H
#define MATVEC_OFFLOAD_H

// Matrix-vector multiplication using GPU offload with OpenMP
// (includes data transfer)
void matvec_gpu(const double *A, const double *x, double *y, int rows, int cols);

// Matrix-vector multiplication using GPU offload with data already on device
// (excludes data transfer)
void matvec_gpu_no_transfer(const double *A, const double *x, double *y, int rows, int cols);

#endif // MATVEC_OFFLOAD_H
