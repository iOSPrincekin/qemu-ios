#!/bin/bash

op=$1

if [ "$op" = "build" ]; then
    cd build
    make
elif [ "$op" = "run" ]; then
    echo "run"
else
    echo "else"
fi
