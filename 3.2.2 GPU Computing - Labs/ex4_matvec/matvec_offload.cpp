#include "matvec_offload.h"

// Matrix-vector multiplication using GPU offload with OpenMP
// (includes data transfer)
void matvec_gpu(const double *A, const double *x, double *y, int rows, int cols) {
    // TODO: Add proper OpenMP target offload pragmas here
    // For now, this is a placeholder that will run on CPU
    #pragma omp parallel for
    for (int i = 0; i < rows; ++i) {
        double sum = 0.0;
        for (int j = 0; j < cols; ++j) {
            sum += A[i * cols + j] * x[j];
        }
        y[i] = sum;
    }
}

// Matrix-vector multiplication using GPU offload with data already on device
// (excludes data transfer)
void matvec_gpu_no_transfer(const double *A, const double *x, double *y, int rows, int cols) {
    // TODO: Add proper OpenMP target data map pragmas here
    // This version should measure only computation time without transfers
    
    // TODO: Add proper OpenMP target offload pragmas here
    // For now, this is a placeholder that will run on CPU
    #pragma omp parallel for
    for (int i = 0; i < rows; ++i) {
        double sum = 0.0;
        for (int j = 0; j < cols; ++j) {
            sum += A[i * cols + j] * x[j];
        }
        y[i] = sum;
    }
}
