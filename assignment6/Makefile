CC=g++
CFLAGS=-I/usr/local/cuda-7.0/include
LINKS=-lOpenCL -lm -fopenmp -lGLEW -lglut -lGL

default:
	$(CC) $(CFLAGS) src/particles.cpp -o bramwelt-particles $(LINKS)
