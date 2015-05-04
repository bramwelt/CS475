#! /bin/bash
threads=(1 2 4 8 16)
padding=(0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16)

[[ -d data ]] || mkdir data

for T in ${threads[@]}
do
    for N in ${padding[@]}
    do
        make -s NUMT=${T} NUM=${N}
        ./false-sharing >> data/padding${T}.dat
        make -s NUMT=${T} NUM=${N} PRIVATE=1
        ./false-sharing >> data/padding${T}-private.dat
    done
done
