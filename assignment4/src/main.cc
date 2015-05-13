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

const float AVG_PRECIP_PER_MONTH = 8.0; // Inches
const float AMP_PRECIP_PER_MONTH = 2.0; // Inches
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

// Temperature and Precipitation. Initialized at start of simulation.
float NowTemp;
float NowPrecip;

// Wild fire damage
float NowFire = 0.0;


//
// Function Prototypes
//
void GrainDeer();
void Grain();
void Watcher();
void Wildfire();

void incMonth();
void printState();
void calcTempPrecip();
float calcGrainHeight();
int calcDeerGrowth(float grainHeight);
float calcWildfireDamage(float nextGrainHeight);

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
    omp_set_num_threads(4);


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
            Wildfire();
        }

        #pragma omp section
        {
            Watcher();
        }
    }  // implied barrier

    fprintf(stderr, "Simulation Complete\n");
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
        float nextGrainHeight = calcGrainHeight();
        int nextNumDeer = calcDeerGrowth(nextGrainHeight);

        // DoneComputing barrier:
        #pragma omp barrier

        // Copy into global variables
        NowNumDeer = nextNumDeer;

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
        float nextGrainHeight = calcGrainHeight();

        // DoneComputing barrier:
        #pragma omp barrier

        // Copy into global variables
        NowHeight = nextGrainHeight;

        // DoneAssigning barrier:
        #pragma omp barrier

        // DonePrinting barrier:
        #pragma omp barrier
    }
}

void
Wildfire()
{
    while( NowYear <= 2020 )
    {
        // Compute into tmp variables
        float nextGrainHeight = calcGrainHeight();
        float wildFireDamage = calcWildfireDamage(nextGrainHeight);

        // DoneComputing barrier:
        #pragma omp barrier

        // Copy into global variables
        NowFire = wildFireDamage;

        // DoneAssigning barrier:
        #pragma omp barrier

        // DonePrinting barrier:
        #pragma omp barrier
    }
}

// cm = inches * 2.54
// °C = (5.0/9.0)*(°F-32)
void
printState()
{
    if (NowYear == 2015 && NowMonth == 0) {
        cout << "STEP\tYEAR\tMON\tTEMP(C)\tPRECIP(cm)\tGRAIN(cm)\tDEER\tFIRE" << "\n";
    }
    int index = (NowYear % 2014);
    int step = index + NowMonth + (13 * (index-1));
    cout << step << " ";
    cout << NowYear << " ";
    cout << NowMonth << " ";
    cout << (5.0/9.0)*(NowTemp-32) << " ";
    cout << (NowPrecip*2.54) << " ";
    cout << (NowHeight*2.54) << " ";
    cout << NowNumDeer << " ";
    cout << NowFire;
    cout << "\n";
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

//
// Each month you will need to figure out how much the grain grows. If
// conditions are good, it will grow by GRAIN_GROWS_PER_MONTH. If
// conditions are not good, it won't.
//
// You know how good conditions are by seeing how close you are to an
// ideal temperature (°F) and precipitation (inches).
//
// tempFactor = e^-((NowTemp - MidTemp)/10)^2
// precipFactor = e^-((NowPrecip - MidPrecip)/10)^2
//
//  You then use tempFactor and precipFactor like this:
//
//   NowHeight += tempFactor * precipFactor *
//   GRAIN_GROWS_PER_MONTH;
//    NowHeight -= (float)NowNumDeer * ONE_DEER_EATS_PER_MONTH;
//
//    Be sure to clamp NowHeight to zero.
//
float
calcGrainHeight()
{
    float nextGrainHeight = NowHeight;

    float tempFactor = expf(-pow((NowTemp - MIDTEMP)/10, 2));
    float precipFactor = expf(-pow((NowPrecip - MIDPRECIP)/10, 2));

    nextGrainHeight += tempFactor * precipFactor * GRAIN_GROWS_PER_MONTH;
    nextGrainHeight -= (float)NowNumDeer * ONE_DEER_EATS_PER_MONTH;
    nextGrainHeight -= NowFire;

    if (nextGrainHeight < 0.0) nextGrainHeight = 0.0;

    return nextGrainHeight;
}

float
calcWildfireDamage(float nextGrainHeight)
{
    float wildFireDamage = 0.0;

    int randomMonth = Ranf(1, 11);
    // In a random month, have wildfire wipe out 20% of grain.
    if (abs(NowMonth - randomMonth) < 2) {
       wildFireDamage = nextGrainHeight * 0.8;
    }

    return wildFireDamage;
}

//
// The Carrying Capacity of the graindeer is the number of
// inches of height of the grain. If the number of graindeer
// exceeds this value at the end of a month, decrease the number
// of graindeer by one. If the number of graindeer is less than
// this value at the end of a month, increase the number of
// graindeer by one.
//
int
calcDeerGrowth(float NextHeight)
{
    int nextNumDeer = NowNumDeer;

    float capacity = nextNumDeer * ONE_DEER_EATS_PER_MONTH;
    if (NextHeight > capacity) {
        ++nextNumDeer;
    } else if (NextHeight < capacity) {
        --nextNumDeer;
    }

    return nextNumDeer;
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
