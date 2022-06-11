#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#include "merge.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

void corank(int i, double a[], long n, int *j, double b[], long m, int *k) {
    *j = MIN(i, n);
    *k = i - *j;
    long jlow = MAX(0, i - m);
    long klow = 0;
    int done = 0;
    do {
        if (((*j > 0) && (*k < m)) && a[*j - 1] > b[*k]) {
            long d = (1 + *j - jlow) / 2;
            klow = *k;
            *j = *j - d;
            *k = *k + d;
        } else if (((*k > 0) && (*j < n)) && b[*k - 1] >= a[*j]) {
            long d = (1 + *k - klow) / 2;
            jlow = *j;
            *j = *j + d;
            *k = *k - d;
        } else {
            done = 1;
        }
    } while (!done);
}

void merge(double a[], long n, double b[], long m, double c[]) {

    int t = omp_get_max_threads();
    int i;

    int *coj = malloc((t + 1) * sizeof(int));
    int *cok = malloc((t + 1) * sizeof(int));

    #pragma omp parallel for
    for (i = 0; i <= t; i++) {
        corank(i * (n + m) / t, a, n, &coj[i], b, m, &cok[i]);
    }

    #pragma omp parallel for
    for (i = 0; i <= t; i++) {
        seq_merge1(&a[coj[i]], coj[i + 1] - coj[i],
                   &b[cok[i]], cok[i + 1] - cok[i],
                   &c[i * (n + m) / t]);
    }
}
