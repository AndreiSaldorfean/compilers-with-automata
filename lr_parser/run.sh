#!/bin/bash

inp=$1

if [ -z "$inp" ]; then
    inp="NULL"
fi

if [ "c" == $inp ];
then
    rm -rf build
    cmake -S . -B build -G "Unix Makefiles"
    cmake --build build

elif [ "b" == $inp ];
then
    cmake --build build
else
    cd build/bin && ./main "$inp"
fi
