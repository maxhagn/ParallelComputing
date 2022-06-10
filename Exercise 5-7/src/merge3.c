

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#include "merge.h"

int rank ( double x , double X [] , int n ) {
    int count = 0;
    for(int i = 0; i < n; i++) {
        if(X[i] < x) { count++; }
    }

    return count;
}

void merge(double A[], long n, double B[], long m, double C[]) {
    int CUTOFF = 10;
    int i;
    if (n == 0) { // task parallelize for large n
        for (i = 0; i < m; i++) {
            C[i] = B[i];
        }
    } else if (m == 0) { // task parallelize for large m
        for (i = 0; i < n; i++) {

        } C[i] = A[i];
    } else if (n + m < CUTOFF) {
        seq_merge1(A, n, B, m, C); // sequential merge for small problems
    } else {
        int r = n / 2;
        int s = rank(A[r], B, m);
        C[r + s] = A[r];
        merge(A, r, B, s, C);
        merge(&A[r + 1], n - r - 1, &B[s], m - s, &C[r + s + 1]);
    }

}

