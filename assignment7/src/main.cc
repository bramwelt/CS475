//
// Trevor Bramwell
// CS475 - Assignment 1
//
// File: main.cc
//

#include <iostream>
#include <stdio.h>

#include "omp.h"

#ifndef NUMS
#define NUMS 8
#endif

#ifndef NUMT
#define NUMT omp_get_num_procs()
#endif

using std::cout;

int main( int argc, char *argv[ ] )
{
    // Begin/End Time
    double begin = 0.0;
    double end = 0.0;

    omp_set_num_threads(NUMT);

    int A[NUMS];
    int B[NUMS];
    int C[NUMS];

    begin = omp_get_wtime();

    //#pragma omp parallel for default(none),shared(A,B),private(C)
    #pragma omp simd parallel for
    for( int i = 0; i < NUMS; i++ )
    {
        C[i] = A[i]*B[i];
    }

    end = omp_get_wtime();

    double time = 1000000.0*(double)(end-begin);

    cout << NUMS << "\t";
    cout << NUMT << "\t";
    cout << ((float)NUMS*(float)NUMS)/time << "\t";
    cout << "\n";

    return 0;
}
