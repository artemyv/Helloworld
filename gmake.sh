#!/bin/bash
mkdir build-dir
cd build-dir 
cmake -S ../test1
make
ctest