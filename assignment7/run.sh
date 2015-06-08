#! /bin/bash
sections=(1 2 4 8 16 32 64 128 512 1024 2048 4096 8192 16384)
threads=(1 2 4 8 16)

echo -e "NUMS\tNUMT\tMMPS"
for T in ${threads[@]}
do
    for N in ${sections[@]}
    do
        make -s NUMS=$N NUMT=$((T*1000))
        ./vectorized
    done
done
