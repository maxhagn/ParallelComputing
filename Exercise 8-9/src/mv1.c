#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <mpi.h>

#include "utils.h"
#include "mv.h"

void mv(base_t **A, int nrows, int ncols, int nrows_a_loc, int ncols_a_loc,
        base_t *x, int nrows_x_loc,
        base_t *b, int ncols_b_loc) {

    int rank, size;

    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int counts[size], disps[size];
    double compX[ncols];

    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
        
    MPI_Allgather(&nrows_x_loc, 1, MPI_INT, counts, 1, MPI_INT, MPI_COMM_WORLD);

    base_t *vector = (double *) malloc(nrows * sizeof(double));

    MPI_Allgather(x, ncols / size, MPI_DOUBLE, vector, (ncols / size), MPI_DOUBLE, MPI_COMM_WORLD);

    for (int i = 0; i < size; i++)
    {
        if (i != 0) {
            disps[i] = disps[i - 1] + counts[i - 1];
        }else {
            disps[i] = 0;
        }
    }

    MPI_Allgatherv(&x[0], nrows_x_loc, MPI_DOUBLE, &compX, counts, disps,
                   MPI_DOUBLE, MPI_COMM_WORLD);

    for (int i = 0; i < nrows_a_loc; i++) {
        b[i] = 0;
        for (int j = 0; j < ncols_a_loc; j++) {
            b[i] += A[i][j] * compX[j];
        }
    }

}
