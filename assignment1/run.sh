#! /bin/bash
sections=(1024 2048 4096 8192 16384 32768)
threads=(2 4 8 16 32 64)

echo "VOLUME NUMS NUMT WTIME"
for N in ${sections[@]}
do
    for T in ${threads[@]}
    do
        make -s NUMS=$N NUMT=$T
        ./assign1
    done
done
