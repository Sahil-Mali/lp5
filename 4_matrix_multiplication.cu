#include <stdio.h>
#include <cuda_runtime.h>

#define N 4

__global__ void matrixMul(int *A, int *B, int *C, int n) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < n && col < n) {
        int sum = 0;
        for (int k = 0; k < n; k++) {
            sum += A[row * n + k] * B[k * n + col];
        }
        C[row * n + col] = sum;
    }
}

int main() {
    int A[N][N], B[N][N], C[N][N];

    // Initialize matrices
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = i + j;
            B[i][j] = i * j;
        }
    }

    int *d_A, *d_B, *d_C;

    cudaMalloc((void**)&d_A, sizeof(int) * N * N);
    cudaMalloc((void**)&d_B, sizeof(int) * N * N);
    cudaMalloc((void**)&d_C, sizeof(int) * N * N);

    cudaMemcpy(d_A, A, sizeof(int) * N * N, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B, sizeof(int) * N * N, cudaMemcpyHostToDevice);

    dim3 threadsPerBlock(16, 16);
    dim3 blocksPerGrid((N + 15) / 16, (N + 15) / 16);

    matrixMul<<<blocksPerGrid, threadsPerBlock>>>(d_A, d_B, d_C, N);

    cudaDeviceSynchronize();

    cudaMemcpy(C, d_C, sizeof(int) * N * N, cudaMemcpyDeviceToHost);

    printf("Result Matrix:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    return 0;
}