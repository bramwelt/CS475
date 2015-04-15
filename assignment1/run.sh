#! /bin/bash
sections=(1000 2000 4000 8000 16000 32000 46340)
threads=(1 2 4 8 16 32 64 128)

echo -e "NUMS\tNUMT\tMFLOPS\t(VOLUME)"
for T in ${threads[@]}
do
    for N in ${sections[@]}
    do
        make -s NUMS=$N NUMT=$T
        ./assign1
    done
done
