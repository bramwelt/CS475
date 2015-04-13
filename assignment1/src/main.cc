//
// Trevor Bramwell
// CS475 - Assignment 1
//
// File: main.cc
//

#include <iostream>
#include <stdio.h>

#include "omp.h"

#include "height.h"

#ifndef NUMT
#define NUMT omp_get_num_procs()
#endif

using std::cout;

int main( int argc, char *argv[ ] )
{
    double volume = 0.0;
    double height = 0.0;

    // Modifier for Edges
    float modif = 1.0;

    // Begin/End Time
    double begin = 0.0;
    double end = 0.0;

    omp_set_num_threads(NUMT);

    // the area of a single full-sized tile:

    float fullTileArea = (  ( (XMAX-XMIN)/(float)(NUMS-1) )  *  ( ( YMAX - YMIN )/(float)(NUMS-1) )  );

    // sum up the weighted heights into the variable "volume"
    // using an OpenMP for loop and an addition reduction:

    begin = omp_get_wtime();

    #pragma omp parallel for default(none),reduction(+:volume),private(height,modif),shared(fullTileArea)
    //#pragma omp parallel for default(none),reduction(+:volume),private(height),shared(fullTileArea)
    for( int i = 0; i < NUMS*NUMS; i++ )
    {
        int iu = i % NUMS;  // x
        int iv = i / NUMS;  // y

        height = Height(iu, iv);

        modif = 1.0;

        if (iv == 0 || iv == (NUMS-1))   // top & bottom
            modif = modif/2.0;
        if (iu == 0 || iu == (NUMS-1))  // edges
            modif = modif/2.0;
        volume += (double)(modif * fullTileArea) * height;
    }

    end = omp_get_wtime();

    //cout << "VOLUME\tNUMS\tNUMT\tWTIME\n";
    cout << volume << " ";
    cout << NUMS << " ";
    cout << NUMT << " ";
    printf("%0.2lf", 1000000. * (end-begin));
    cout << "\n";

    return 0;
}
