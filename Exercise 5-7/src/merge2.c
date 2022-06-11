#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#include "merge.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

void corank(int i, double a[], long n, int *j, double b[], long m, int *k) {
    *j = MIN(i, n);
    *k = i - *j;
    int jlow = MAX(0, i - m);
    int d;
    int klow;
    if (*j > 0 && *k < m && a[*j - 1] > b[*k]) {
        d = (*j-jlow)/2 + ((*j-jlow)/2 != 0);
        klow = *k;
        *j -= d;
        *k += d;
    } else if (*k > 0 && *j < n && b[*k - 1] >= a[*j]) {
        d = (*k-klow)/2 + ((*k-klow)/2 != 0);
        jlow = *j;
        *k -= d;
        *j += d;
    }
}

void merge(double a[], long n, double b[], long m, double c[]) {

    int t = omp_get_max_threads();

    int i;

    int coj[t + 1];
    int cok[t + 1];

    #pragma omp parallel for
    for (i = 0; i < t; i++) {
        corank(i * (n + m) / t, a, n, &coj[i], b, m, &cok[i]);
    }


    coj[t] = n;
    cok[t] = m;

    #pragma omp parallel for
    for (i = 0; i <= t; i++) {
        seq_merge1(&a[coj[i]], coj[i + 1] - coj[i],
                   &b[cok[i]], cok[i + 1] - cok[i],
                   &c[i * (n + m) / t]);
    }
}
