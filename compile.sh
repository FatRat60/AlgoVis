#!/bin/bash

if ["$OSTYPE" == "msys"]; then
    cmake -S . -B build
    cmake --build build --config Release
else 
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
    cmake --build build
fi