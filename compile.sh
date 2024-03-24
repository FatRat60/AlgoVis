#!/bin/bash

if [["$OSTYPE" == "msys"]]; then
    cmake -S . -B build
    cmake --build build --config Release
    if [ $? -eq 0 ]; then
        # only run exe if build is succesfful
        ./build/AlgoVis.exe
    fi
else 
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
    cmake --build build
    ./build/AlgoVis 800 0
fi