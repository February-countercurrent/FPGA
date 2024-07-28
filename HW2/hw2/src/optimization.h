#ifndef KERNEL_H
#define KERNEL_H

#ifdef __cplusplus
extern "C" {
#endif

void kernel1_optimized(int *A, int size, int offset);
void kernel2_optimized(int *A, int size);
void kernel3_optimized(float *h, float *w, int *idx, int size);
float kernel4_optimized(float *A, float *B, int size);

#ifdef __cplusplus
}
#endif

#endif // KERNEL_H
