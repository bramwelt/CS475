#! /bin/bash
[[ -d data ]] || mkdir data

global_size=(1 2 4 8 16 32 64 128)
local_size=(1 2 4 8 32 64 128 256 512 1024)

for G in ${global_size[@]}; do
    for L in ${local_size[@]}; do
        make -s  LOCAL_SIZE=${L} NUM_ELEMENTS=$((${G}*1024*1024))
        ./first | tee data/vector-mult-${L}.tmp
    done
    column -t data/vector-mult-${L}.tmp > data/vector-mult-${L}.dat
    rm data/vector-mult-${L}.tmp
done

echo "Vector Multiplication Done."