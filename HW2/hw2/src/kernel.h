#ifndef KERNEL_H
#define KERNEL_H

#ifdef __cplusplus
extern "C" {
#endif

void kernel1(int *A, int size, int offset);
void kernel2(int *A, int size);
void kernel3(float *h, float *w, int *idx, int size);
float kernel4(float *A, float *B, int size);

#ifdef __cplusplus
}
#endif

#endif // KERNEL_H
