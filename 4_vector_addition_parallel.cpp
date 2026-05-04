#include <iostream>
#include <omp.h>
using namespace std;

#define N 10

int main() {
    int A[N], B[N], C[N];

    // Initialize vectors
    cout << "Vector A: ";
    for(int i = 0; i < N; i++) {
        A[i] = i;
        cout << A[i] << " ";
    }

    cout << "\nVector B: ";
    for(int i = 0; i < N; i++) {
        B[i] = i * 2;
        cout << B[i] << " ";
    }

    // Parallel Vector Addition
    #pragma omp parallel for
    for(int i = 0; i < N; i++) {
        C[i] = A[i] + B[i];
    }

    // Print Result
    cout << "\nResult Vector C: ";
    for(int i = 0; i < N; i++) {
        cout << C[i] << " ";
    }

    return 0;
}