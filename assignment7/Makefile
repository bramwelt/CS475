CC=icpc
CPP_FLAGS=-openmp -lm -align -qopt-report=3 -qopt-report-phase=vec

NUMS=8
NUMT=8

default:
	$(CC) $(CPP_FLAGS) -O3 -no-vec -DNUMS=$(NUMS) -DNUMT=$(NUMT) src/main.cc -o vectorized
	$(CC) $(CPP_FLAGS) -O3 -DNUMS=$(NUMS) -DNUMT=$(NUMT) src/spmd.cc -o spmd
