#include "kernel.h"

void kernel1_optimized(int *A, int size, int offset) {
    int i;
    for (i = 0; i < size - offset; i += 4) {
        A[i] += A[i + offset];
        A[i + 1] += A[i + 1 + offset];
        A[i + 2] += A[i + 2 + offset];
        A[i + 3] += A[i + 3 + offset];
    }
}


void kernel2_optimized(int *A, int size) {
    int i;
    for (i = 3; i < size; i++) {
        int tmp1 = A[i - 1];
        int tmp2 = A[i - 2];
        int tmp3 = A[i - 3];
        A[i] = tmp1 + tmp2 * tmp3;
    }
}


void kernel3_optimized(float *h, float *w, int *idx, int size) {
    for (int i = 0; i < size; i++) {
        int index = idx[i];
        h[index] = h[index] + w[i];
    }
}


float kernel4_optimized(float *A, float *B, int size) {
    float sum = 0;
    for (int i = 0; i < size; i++) {
        float diff = A[i] - B[i];
        sum += (diff > 0) ? diff : 0;
    }
    return sum;
}
