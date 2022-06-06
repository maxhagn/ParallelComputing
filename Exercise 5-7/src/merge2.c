#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#include "merge.h"

void merge(double a[], long n, double b[], long m, double c[]) {
  int t = omp_get_max_threads();
  fprintf(stderr, "hallo welt\n%i\n",t);
  seq_merge1(a, n, b, m, c);
}


