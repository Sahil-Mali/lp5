#include <iostream>
#include <omp.h>
using namespace std;

#define N 3

int main() {
    int A[N][N], B[N][N], C[N][N];

    // Initialize matrices
    cout << "Matrix A:\n";
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            A[i][j] = i + j;
            cout << A[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nMatrix B:\n";
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            B[i][j] = i * j;
            cout << B[i][j] << " ";
        }
        cout << endl;
    }

    // Parallel Matrix Multiplication
    #pragma omp parallel for collapse(2)
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            C[i][j] = 0;
            for(int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    // Print Result
    cout << "\nResult Matrix C:\n";
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cout << C[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}