#!/bin/bash

inp=$1

if [ -z "$inp" ]; then
    inp="NULL"
fi

if [ "c" == $inp ];
then
    rm -rf tests/build
    cmake -S tests/. -B tests/build -G "Unix Makefiles"
    cmake --build build

elif [ "b" == $inp ];
then
    cd tests && cmake --build build
else
    cd tests/build && ./main.exe
fi
