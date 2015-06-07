CC=g++
CPP_FLAGS=-fopenmp -lm

NUMS=8
NUMT=8

default:
	$(CC) $(CPP_FLAGS) -O3 -DNUMS=$(NUMS) -DNUMT=$(NUMT) src/main.cc -o vectorized
#	$(CC) $(CPP_FLAGS) -O3 -DNUMS=$(NUMS) -DNUMT=$(NUMT) src/spmd.cc -o spmd
