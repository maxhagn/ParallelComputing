

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#include "merge.h"

/*void rank(int i, double a[], long n, int *j, double b[], long m, int *k){
    *j = MIN(i,n);
    *k = i - *j;
    int jlow = MAX(0,i - m);
    int d;
    int klow;
    if (*j > 0 && *k < m && a[*j-1] > b[*k]){
        d = (1 + *j - jlow)/2;
        klow = k;
        *j-= d; *k += d;
    } else if (*k > 0 && *j < n && b[*k - 1]>=a[*j]) {
        d = (1+ *k - klow)/2;
        jlow = *j;
        *k -= d; *j += d;
    }

}
*/
void merge(double A[], long n, double B[], long m, double C[]) {
/*
    int i;
    if (n == 0) { // task parallelize for large n
        for (i = 0; i < m; i++) C[i] = B[i];
    } else if (m == 0) { // task parallelize for large m
        for (i = 0; i < n; i++) C[i] = A[i];
    } else if (n + m < CUTOFF) {
        seq_merge1(A, n, B, m, C); // sequential merge for small problems
    } else {
        int r = n / 2;
        int s = rank(A[r], B, m);
        C[r + s] = A[r];
        merge(A, r, B, s, C);
        merge(&A[r + 1], n - r - 1, &B[s], m - s, &C[r + s + 1]);
    }

*/
}

