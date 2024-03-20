#!/bin/bash

if [["$OSTYPE" == "msys"]]; then
    cmake -S . -B build
    cmake --build build --config Release
    ./build/AlgoVis.exe
else 
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
    cmake --build build
    ./build/AlgoVis
fi