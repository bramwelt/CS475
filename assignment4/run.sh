#! /bin/bash
[[ -d data ]] || mkdir data

make -s 
./function-decomposition > data/graindeer.tmp
column -t data/graindeer.tmp > data/graindeer.dat
rm data/graindeer.tmp
less data/graindeer.dat
