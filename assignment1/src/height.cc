//
// Trevor Bramwell
// CS475 - Assignment 1
//
// File: height.cc
//

#include "height.h"

float
Height( int iu, int iv )    // iu,iv = 0 .. NUMS-1
{
    float u = (float)iu / (float)(NUMS-1);
    float v = (float)iv / (float)(NUMS-1);

    // the basis functions:

    float bu0 = (1.-u) * (1.-u) * (1.-u);
    float bu1 = 3. * u * (1.-u) * (1.-u);
    float bu2 = 3. * u * u * (1.-u);
    float bu3 = u * u * u;

    float bv0 = (1.-v) * (1.-v) * (1.-v);
    float bv1 = 3. * v * (1.-v) * (1.-v);
    float bv2 = 3. * v * v * (1.-v);
    float bv3 = v * v * v;

    // finally, we get to compute something:

    float height =    bu0 * ( bv0*Z00 + bv1*Z01 + bv2*Z02 + bv3*Z03 )
            + bu1 * ( bv0*Z10 + bv1*Z11 + bv2*Z12 + bv3*Z13 )
            + bu2 * ( bv0*Z20 + bv1*Z21 + bv2*Z22 + bv3*Z23 )
            + bu3 * ( bv0*Z30 + bv1*Z31 + bv2*Z32 + bv3*Z33 );

    return height;
}
