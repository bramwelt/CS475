CC=g++
CFLAGS=-I/usr/local/cuda-7.0/include
LINKS=-lOpenCL -lm -fopenmp
LOCAL_SIZE=32
NUM_ELEMENTS=65536

default:
	$(CC) $(CFLAGS) -DLOCAL_SIZE=${LOCAL_SIZE} -DNUM_ELEMENTS=${NUM_ELEMENTS} src/first.cpp -o first $(LINKS)
