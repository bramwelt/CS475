#! /bin/bash
threads=(1 2 4 8 16 31 32)

rm data/*

for T in ${threads[@]}
do
    make -s DEFS="-DNUMT=${T}"
    ./nbodies >> data/fine-static.dat
    make -s DEFS="-DDYNAMIC -DNUMT=${T}"
    ./nbodies >> data/fine-dynamic.dat
    make -s DEFS="-DCORSE -DNUMT=${T}"
    ./nbodies >> data/course-static.dat
    make -s DEFS="-DCORSE -DDYNAMIC -DNUMT=${T}"
    ./nbodies >> data/corse-dynamic.dat
done
