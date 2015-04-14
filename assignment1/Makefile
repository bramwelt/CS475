CC=g++
CPP_FLAGS=-fopenmp -lm

NUMS=8
NUMT=8

default:
	$(CC) $(CPP_FLAGS) -O3 -DNUMS=$(NUMS) -DNUMT=$(NUMT) src/height.cc src/main.cc -o assign1

# for t (1 2 4 8)
#   for s ( 2 10 50 100 )
#     g++ -o pl pl.cpp -DNUMS=$s
#         -DNUMT=$t
