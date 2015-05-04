CC=g++
CFLAGS=-fopenmp -lm

NUM=0
NUMT=1
PRIVATE=0

default:
	$(CC) $(CFLAGS) -DPRIVATE=$(PRIVATE) -DNUM=$(NUM) -DNUMT=$(NUMT) src/main.cc -o false-sharing
