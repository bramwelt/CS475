//
// Trevor Bramwell
// CS475 - Assignment 4
//
// File: main.cc
//

// Functional Decomposition
//
// A simulation in which each element of the simulation executes in its
// own thread where it looks at the state of the world around it and
// react to it. 

// Simulation Description
//
// You are creating a simulation of a grain-growing operation. The
// amount the grain grows is affected by the temperature, amount of
// precipitation, and the number of "graindeer" around to eat it. The
// number of graindeer depends on the amount of grain available to eat. 

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

using std::cout;


//
// System Global Constants
//

const float GRAIN_GROWS_PER_MONTH = 8.0; // Inches
const float ONE_DEER_EATS_PER_MONTH = 0.5;

const float AVG_PRECIP_PER_MONTH = 6.0; // Inches
const float AMP_PRECIP_PER_MONTH = 6.0; // Inches
const float RANDOM_PRECIP = 2.0;

const float AVG_TEMP = 50.0; // Fahrenheit
const float AMP_TEMP = 20.0; // Fahrenheit
const float RANDOM_TEMP = 10.0; // Fahrenheit

const float MIDTEMP = 40.0; // Fahrenheit
const float MIDPRECIP = 10.0; // Inches


//
// System Global State
//

// starting date and time:
int NowMonth = 0;
int NowYear  = 2015;

// starting state (feel free to change this if you want):
int NowNumDeer = 1;
float NowHeight = 1.0;

float NowTemp;
float NowPrecip;


//
// Function Prototypes
//
void GrainDeer();
void Grain();
void Watcher(); 

void incMonth();
void printState();
void calcTempPrecip();

float Ranf(float, float);
int Ranf(int, int);

//
// Function Definitions
//

int
main(int argc, char* argv[])
{

    // Calculate Temperature and Precipitation
    calcTempPrecip();

    // Spawn 3 Threads
    omp_set_num_threads(3);


    #pragma omp parallel sections
    {
        #pragma omp section
        {
            GrainDeer();
        }
    
        #pragma omp section
        {
            Grain();
        }
    
        #pragma omp section
        {
            Watcher();
        }
    }  // implied barrier

    cout << "Simulation Complete\n";
    return 0;
}


void
Watcher()
{
    while( NowYear <= 2020 )
    {
        // DoneComputing barrier:
        #pragma omp barrier

        // DoneAssigning barrier:
        #pragma omp barrier

        // Print results
        printState();

        // Increment month
        incMonth();

        // Calculate new Temperature and Precipitation
        calcTempPrecip();

        // DonePrinting barrier:
        #pragma omp barrier
    }
}


void
GrainDeer()
{
    while( NowYear <= 2020 )
    {
        // Compute into tmp variables

        // DoneComputing barrier:
        #pragma omp barrier

        // Copy into global variables

        // DoneAssigning barrier:
        #pragma omp barrier


        // DonePrinting barrier:
        #pragma omp barrier
    }
}


void
Grain()
{
    while( NowYear <= 2020 )
    {
        // Compute into tmp variables

        // DoneComputing barrier:
        #pragma omp barrier

        // Copy into global variables

        // DoneAssigning barrier:
        #pragma omp barrier

        // DonePrinting barrier:
        #pragma omp barrier
    }
}

void
printState()
{
    if (NowYear == 2015 && NowMonth == 0) {
        cout << "MON\tYEAR" << "\n";
    }
    cout << NowMonth << ", " << NowYear << "\n";
    // cout << "NUM\tNUMT\tPERF\tTIME" << "\n";
    // cout << NUM << "\t";
    // cout << NUMT << "\t";
    // cout << ((float)someBigNumber*4.0)/timedelta/10000000.0 << "\t";
    // cout << timedelta << "s";
    // cout << "\n";
}

void
incMonth()
{
    if (NowMonth == 11) {
        NowMonth = 0;
        ++NowYear;
    } else {
        ++NowMonth;
    }
}

void
calcTempPrecip()
{
    float ang = (  30.0*(float)NowMonth + 15.0  ) * ( M_PI / 180.0 );

    float temp = AVG_TEMP - AMP_TEMP * cos( ang );
    NowTemp = temp + Ranf( -RANDOM_TEMP, RANDOM_TEMP );

    float precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin( ang );
    NowPrecip = precip + Ranf( -RANDOM_PRECIP, RANDOM_PRECIP );

    if( NowPrecip < 0.0 ) NowPrecip = 0.0;
}

float
Ranf(float low, float high)
{
    float r = (float) rand(); // 0 - RAND_MAX

    return(low  +  r * (high - low) / (float)RAND_MAX);
}


int
Ranf(int ilow, int ihigh)
{
    float low = (float)ilow;
    float high = (float)ihigh + 0.9999f;

    return (int)(  Ranf(low,high) );
}
