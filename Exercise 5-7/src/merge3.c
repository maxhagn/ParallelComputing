#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

#include "merge.h"

int rank(double x, double X[], long n) {

    int start = 0;
    int end = n - 1;
    int count = 0;

    while (start <= end) {
        int middle = (end + start) / 2;

        if (X[middle] <= x) {
            count = middle + 1;
            start = middle + 1;
        } else {
            end = middle - 1;
        }
    }

    return count;
}


void merge(double A[], long n, double B[], long m, double C[]) {

    int CUTOFF = (m+n)/(long)omp_get_max_threads();
    int i;

    if (n == 0) {

        #pragma omp taskloop
        for (i = 0; i < m; i++) {
            C[i] = B[i];
        }

    } else if (m == 0) {

        #pragma omp taskloop
        for (i = 0; i < n; i++) {
            C[i] = A[i];
        }

    } else if (n + m < CUTOFF) {

        seq_merge1(A, n, B, m, C);

    } else {

        int r = n / 2;
        int s = rank(A[r], B, m);
        C[r + s] = A[r];

        #pragma omp task shared (A ,B , C )
        merge(A, r, B, s, C);

        #pragma omp task shared (A ,B , C )
        merge(&A[r + 1], n - r - 1, &B[s], m - s, &C[r + s + 1]);

        #pragma omp taskwait

    }
}

