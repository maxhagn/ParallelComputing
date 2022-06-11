#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

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


void merge(double a[], long n, double b[], long m, double c[]) {

    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        c[i + rank(a[i], b, m)] = a[i];
    }

    #pragma omp parallel for
    for (int i = 0; i < m; i++) {
        c[i + rank(b[i], a, n)] = b[i];
    }

}


