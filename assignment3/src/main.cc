//
// Trevor Bramwell
// CS475 - Assignment 3
//
// File: main.cc
//

// False Sharing

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

using std::cout;

#ifndef NUM
#define NUM       0
#endif

#ifndef NUMT
#define NUMT      4
#endif

#ifndef PRIVATE
#define PRIVATE   0
#endif


struct s
{
    float value;
    int pad[NUM];
} Array[4];


int
main(int argc, char* argv[])
{
    unsigned int someBigNumber = 1000000000;    // if > 4B, use "long unsigned int"

    omp_set_num_threads(NUMT);

    double time0 = omp_get_wtime();

    #pragma omp parallel for
    for( int i = 0; i < 4; i++ )
    {
#if PRIVATE>=1
        float tmp = Array[i].value;
        for( unsigned int j = 0; j < someBigNumber; j++ )
        {
            tmp = tmp + 2.0;
        }
        Array[i].value = tmp;
#else
        for( unsigned int j = 0; j < someBigNumber; j++ )
        {
            Array[i].value = Array[i].value + 2.0;
        }
#endif
    }

    double time1 = omp_get_wtime();
    double timedelta = (time1-time0);

    // Performance

#if NUM == 0
    cout << "NUM\tNUMT\tPERF\tTIME" << "\n";
#endif
    cout << NUM << "\t";
    cout << NUMT << "\t";
    cout << ((float)someBigNumber*4.0)/timedelta/10000000.0 << "\t";
    cout << timedelta << "s";
    cout << "\n";

    return 0;
}
