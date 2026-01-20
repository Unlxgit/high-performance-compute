#include "matvec.h"

// Matrix-vector multiplication using CPU with OpenMP parallelization
void matvec_cpu(const double *A, const double *x, double *y, int rows, int cols) {
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
