#include <stdio.h>
#include <stdlib.h>

#include <assert.h>
#include <math.h>

#include <mpi.h>

#include "utils.h"
#include "mv.h"

void mv(base_t **A, int nrows, int ncols, int nrows_a_loc, int ncols_a_loc,
        base_t *x, int nrows_x_loc,
        base_t *b, int ncols_b_loc)
{

    int rank, size;

    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    assert(nrows%size==0);
    assert(ncols%size==0);

    base_t *partial = (double*)malloc(nrows*sizeof(double));

    for (int i=0; i<nrows; i++) {
        partial[i] = A[i][0]*x[0];
        for (int j=0; j<ncols/size; j++) {
            partial[i] += A[i][j]*x[j];
        }
    }

    MPI_Reduce_scatter_block(partial,b,nrows/size,MPI_DOUBLE,MPI_SUM,MPI_COMM_WORLD);

    free(partial);
}
