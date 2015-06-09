#! /bin/bash
sections=(1 2 4 8 16 32 64 128 512)
threads=(1 2 4 8 16)

mkdir -p data

for T in ${threads[@]}
do
    echo "$T:"
    echo -e "NUMS\tNUMT\tMMPS" >> data/vec_"$T".dat
    echo -e "NUMS\tNUMT\tMMPS" >> data/spmd_"$T".dat
    for N in ${sections[@]}
    do
        echo -e "\t$((N*1024))"
        make -s NUMS=$((N*1024)) NUMT=$T
        ./vectorized >> data/vec_"$T".dat
        ./spmd >> data/spmd_"$T".dat
    done
done
