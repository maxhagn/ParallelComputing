#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    int a[] = {15, 2, 42, 12, 3, 123, 43, 23, 76, 1};
    int b[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ,0};
    int n = 10;
    int i;
    int j;

    // iterates from 0 to probably the array size of a
    #pragma omp parallel for
    for (i = 0; i < n; i++) {
        printf("thread %d is here \n", omp_get_thread_num());
        // is increased if integer before current index are smaller than the current
        int count = 0;

        // checks if all integers before the current array index are smaller or equal than the current
        for (j = 0; j < i; j++) {
            if (a[j] <= a[i]) {
                count++;
            }
        }

        j++;

        // checks all integers after the current index
        for (; j < n; j++) {
            if (a[j] < a[i]) count++;
        }

        // adds the current value to position count
        b[count] = a[i];
    }

    #pragma omp parallel for
    for (i = 0; i < n; i++) {
        a[i] = b[i];
    }

    // OUTCOME: Sorted Array
    for (i = 0; i < n; i++) {
        printf("Index %i: %i\n", i, a[i]);
    }

}