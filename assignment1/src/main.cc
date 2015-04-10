//
// Trevor Bramwell
// CS475 - Assignment 1
//
// File: main.cc
//

#include <iostream>

#include "height.h"

int main( int argc, char *argv[ ] )
{
    //. . .

    // the area of a single full-sized tile:

    float fullTileArea = (  ( (XMAX-XMIN)/(float)(NUMS-1) )  *  ( ( YMAX - YMIN )/(float)(NUMS-1) )  );

    // sum up the weighted heights into the variable "volume"
    // using an OpenMP for loop and an addition reduction:
    // ... #pragma omp for reduction(+:volume)

    //?????

    for( int i = 0; i < NUMS*NUMS; i++ )
    {
        int iu = i % NUMS;
        int iv = i / NUMS;

        //?????
    }

    //. . .
}
