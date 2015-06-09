CC=icpc
CPP_FLAGS=-align -qopt-report=3 -qopt-report-phase=vec
LINKS=-openmp -lm

NUMS=8
NUMT=8

default:
	$(CC) $(CPP_FLAGS) -O3 -o vectorized -no-vec -DNUMS=$(NUMS) -DNUMT=$(NUMT) src/main.cc $(LINKS) 2>/dev/null
	$(CC) $(CPP_FLAGS) -O3 -o spmd -DNUMS=$(NUMS) -DNUMT=$(NUMT) src/spmd.cc $(LINKS) 2>/dev/null
