#!/bin/bash

if [[ ! -d "txts" ]]; then
  mkdir txts
fi

mkdir build
cd build 
wait 
cmake .. 
wait
make 
wait
./main
