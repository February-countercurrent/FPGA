#include <xil_printf.h>
#include <xparameters.h>
#include <xio.h>
#include <stdlib.h>
#include <stdio.h>
#include "matmul.h"
#include "timer.h"
#include "kernel.h"
#include "optimization.h"

#define ROWS_A 64
#define COLS_A 64
#define ROWS_B 64
#define COLS_B 64

#define KERNEL_SIZE 1024

// Use memory BRAM to allocate data in order to make it faster
int A[KERNEL_SIZE] __attribute__((section(".bram_mem")));
int B[KERNEL_SIZE] __attribute__((section(".bram_mem")));
float C[KERNEL_SIZE] __attribute__((section(".bram_mem")));
float D[KERNEL_SIZE] __attribute__((section(".bram_mem")));
int idx[KERNEL_SIZE] __attribute__((section(".bram_mem")));

void test_kernels() {
    // Allocate the memory
	for (int i = 0; i < KERNEL_SIZE; i++) {
		A[i] = rand() % 100;
		B[i] = rand() % 100;
		C[i] = (float)(rand() % 100) / 10.0;
		D[i] = (float)(rand() % 100) / 10.0;
		idx[i] = rand() % KERNEL_SIZE;
	}

    // Test Kernel 1
    start_timer();
    kernel1(A, KERNEL_SIZE, 5);
    double t1 = stop_timer();
    xil_printf("Kernel 1 execution time: %.4fs\r\n", t1);

    // Optimize Kernel 1
    start_timer();
    kernel1_optimized(A, KERNEL_SIZE, 5);
    double t1_opt = stop_timer();
    xil_printf("Optimized Kernel 1 execution time: %.4fs\r\n", t1_opt);

    // Test Kernel 2
    start_timer();
    kernel2(A, KERNEL_SIZE);
    double t2 = stop_timer();
    xil_printf("Kernel 2 execution time: %.4fs\r\n", t2);

    // Optimize Kernel 2
    start_timer();
    kernel2_optimized(A, KERNEL_SIZE);
    double t2_opt = stop_timer();
    xil_printf("Optimized Kernel 2 execution time: %.4fs\r\n", t2_opt);

    // Test Kernel 3
    start_timer();
    kernel3(C, D, idx, KERNEL_SIZE);
    double t3 = stop_timer();
    xil_printf("Kernel 3 execution time: %.4fs\r\n", t3);

    // Optimize Kernel 3
    start_timer();
    kernel3_optimized(C, D, idx, KERNEL_SIZE);
    double t3_opt = stop_timer();
    xil_printf("Optimized Kernel 3 execution time: %.4fs\r\n", t3_opt);

    // Test Kernel 4
    start_timer();
    float sum4 = kernel4(C, D, KERNEL_SIZE);
    double t4 = stop_timer();
    xil_printf("Kernel 4 execution time: %.4fs\r\n", t4);
    xil_printf("Kernel 4 sum: %.4f\r\n", sum4);

    // Optimize Kernel 4
    start_timer();
    float sum4_opt = kernel4_optimized(C, D, KERNEL_SIZE);
    double t4_opt = stop_timer();
    xil_printf("Optimized Kernel 4 execution time: %.4fs\r\n", t4_opt);
    xil_printf("Optimized Kernel 4 sum: %.4f\r\n", sum4_opt);

    free(A);
    free(B);
    free(C);
    free(D);
    free(idx);
}

int main() {
    srand(42);

    if (COLS_A != ROWS_B) {
        xil_printf("COLS_A=%d and ROWS_B=%d do not match.\r\n", COLS_A, ROWS_B);
        return -1;
    }

    long long int *A = (long long int *)malloc(ROWS_A * COLS_A * sizeof(long long int));
    long long int *B = (long long int *)malloc(ROWS_B * COLS_B * sizeof(long long int));
    long long int *C = (long long int *)malloc(ROWS_A * COLS_B * sizeof(long long int));

    if (A == NULL || B == NULL || C == NULL) {
        print("Memory allocation failed\n");
        return 1;
    }

    fill_matrix_random(A, ROWS_A, COLS_A);
    fill_matrix_random(B, ROWS_B, COLS_B);
    fill_matrix_zeros(C, ROWS_A, COLS_B);

    start_timer();
    naive_matrix_multiply(A, B, C, ROWS_A, COLS_A, COLS_B);
    double t = stop_timer();

    char s[128] = {};
    sprintf(s, "Time: %.6fs\r\n", t);
    xil_printf("%s", s);

    test_kernels();

    while (1) naive_matrix_multiply(A, B, C, ROWS_A, COLS_A, COLS_B);

    free(A);
    free(B);
    free(C);
    return 0;
}
