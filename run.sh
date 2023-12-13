#!/bin/bash
cd build 
wait 
cmake .. 
wait
make 
wait
cd ..
./build/main