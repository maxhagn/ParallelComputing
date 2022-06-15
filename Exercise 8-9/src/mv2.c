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

    int size ;
    MPI_Comm_size ( MPI_COMM_WORLD , & size );
    base_t partialSum [ nrows ]; // partial sum array for all columns of this process
    int counts [ size ]; // number of elements each process has

    // get number of columns each process has
    MPI_Allgather (& ncols_a_loc ,1 , MPI_INT , counts ,1 , MPI_INT , MPI_COMM_WORLD );
    for ( int i = 0; i < nrows ; i ++) // initialze array with 0
    {
        partialSum [ i ] = 0;
    }

    // calc partial sum for each column into one array
    for ( int i = 0; i < ncols_a_loc ; i ++)
    {
        for ( int j = 0; j < nrows_a_loc ; j ++)
        {
            partialSum [ j ] += A [ j ][ i ] * x [ i ];
        }
    }

    // share and reduce result with other processes
    MPI_Reduce_scatter (& partialSum [0] , b , counts , MPI_DOUBLE , MPI_SUM , MPI_COMM_WORLD );
}
