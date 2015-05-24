#! /bin/bash
[[ -d data ]] || mkdir data
#[[ -d data ]] && rm data/*

global_size=(1 2 3 4 5 6 7 8 9 10 11 12 13 14)
# Forgot 16 ... oh well
local_size=(1 2 4 8 32 64 128 256 512 1024)

for G in ${global_size[@]}; do
    for L in ${local_size[@]}; do
        make -s  LOCAL_SIZE=${L} NUM_ELEMENTS=$((2**${G}*512))
        ./first | tee -a data/vector-mult-add-${G}.tmp
    done
    column -t data/vector-mult-add-${G}.tmp > data/vector-mult-add-${G}.dat
    rm data/vector-mult-add-${G}.tmp
done

for L in ${local_size[@]}; do
    for G in ${global_size[@]}; do
        make -s  USE_GROUP=1 LOCAL_SIZE=${L} NUM_ELEMENTS=$((2**${G}*512))
        ./first | tee -a data/vector-mult-add-group-${L}.tmp
    done
    column -t data/vector-mult-add-group-${L}.tmp > data/vector-mult-add-group-${L}.dat
    rm data/vector-mult-add-group-${L}.tmp
done

echo "Vector Multiplication Done."
