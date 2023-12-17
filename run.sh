#!/bin/bash
mkdir build
cd build 
wait 
cmake .. 
wait
make 
wait
cd ..
./build/main