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

    if (rank==0) {
        int total_n = 0;
        int[] local_n = new int[size];
        int[] displs = new int[size];

        MPI_Gather(1,MPI_INT, local)

    }



    base_t *partial = (double*)malloc(nrows*sizeof(double));

    for (int i=0; i<nrows; i++) {
        for (int j=0; j<ncols/size; j++) {
            partial[i] += A[i][j]*x[j];
        }
    }

    MPI_Reduce_scatter_block(partial,b,nrows/size,MPI_DOUBLE,MPI_SUM,MPI_COMM_WORLD);

    free(partial);
}
