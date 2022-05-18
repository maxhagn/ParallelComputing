#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[]) {

    int num_threads;
    if (argc >= 2) {
        num_threads = atoi(argv[1]);
        omp_set_num_threads(num_threads);
    }

    #pragma omp parallel
    {
        printf("thread %d is here \n", omp_get_thread_num());
    }

    return 0;
}

void mv(int m, int n, double M[m][n], double V[n], double W[m]) {
    int i, j;
    for (i = 0; i < m; i++) {
        W[i] = 0.0;
        for (j = 0; j < n; j++) {
            W[i] += M[i][j] * V[j];
        }
    }
}