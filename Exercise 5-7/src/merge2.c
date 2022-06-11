#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#include "merge.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

void corank(int i, double a[], long n, int *j, double b[], long m, int *k) {
   *j = MIN(i, m);
	*k = i - *j;
	long jlow = MAX(0, i-n);
	long klow = 0;
	while (1)
	{
		if (((*j > 0) & (*k < n)) && a[*j-1] > a[*k])
		{
			long d = (*j-jlow)/2 + ((*j-jlow)/2 != 0);
			klow = *k;
			*j = *j - d;
			*k = *k + d;
		} 
		else if (((*k > 0) & (*j < m)) && b[*k-1] >= a[*j])
		{
			long d = (*k-klow)/2 + ((*k-klow)/2 != 0); 
			jlow = *j;
			*j = *j + d;
			*k = *k - d;
		}
		else
			return 1;
	}
	return 0;
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
