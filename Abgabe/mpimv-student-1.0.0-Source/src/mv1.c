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
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int xRowsCount[size];
    int relativeOffset[size];
    double receiveVector[ncols];

    MPI_Allgather(&nrows_x_loc, 1, MPI_INT, xRowsCount, 1, MPI_INT, MPI_COMM_WORLD);

    relativeOffset[0] = 0;
    for (int i = 1; i < size; i++)
    {
        relativeOffset[i] = relativeOffset[i - 1] + xRowsCount[i - 1];
    }

    MPI_Allgatherv(&x[0], nrows_x_loc, MPI_DOUBLE, &receiveVector, xRowsCount, relativeOffset, MPI_DOUBLE, MPI_COMM_WORLD);
    for (int i = 0; i < nrows_a_loc; i++) {
        b[i] = 0;
        for (int j = 0; j < ncols_a_loc; j++) {
            b[i] += A[i][j] * receiveVector[j];
        }
    }
}