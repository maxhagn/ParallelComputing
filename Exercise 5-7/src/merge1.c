/*
 * parmerge.c
 *
 *  Created on: Mar 12, 2019
 *      Author: sascha
 */

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


void merge(double a[], long n, double b[], long m, double c[]) {

    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        c[i + rank(a[i],b,m)]=a[i];
    }

    #pragma omp parallel for
    for (int i = 0; i < m; i++) {
        c[i + rank(b[i],a,n)]=b[i];
    }

}


