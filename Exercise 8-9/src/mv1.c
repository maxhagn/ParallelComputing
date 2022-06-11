

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

    //assert(nrows%size==0);
    //assert(ncols%size==0);

    base_t *fullvector = (double*)malloc(nrows*sizeof(double));

    MPI_Allgather(x,ncols/size,MPI_DOUBLE,fullvector,ncols/size,MPI_DOUBLE,MPI_COMM_WORLD);

    for (int i=0; i<nrows/size; i++) {
        b[i] = A[i][0]*fullvector[0];
        for (int j=0; j<ncols/size; j++) {
            b[i] += A[i][j]*fullvector[j];
        }
    }

    free(fullvector);

}
