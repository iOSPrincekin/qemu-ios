#!/bin/bash

op=$1

if [ "$op" = "build" ]; then
    mkdir -p build
    cd build
    ../configure --enable-sdl --disable-cocoa --target-list=arm-softmmu --disable-capstone --disable-pie --disable-slirp --extra-cflags=-I/opt/homebrew/Cellar/openssl@3/3.1.0/include --extra-ldflags='-L/opt/homebrew/Cellar/openssl@3/3.1.0/lib -lcrypto'
    make
elif [ "$op" = "run" ]; then
    echo "run"
else
    echo "else"
fi
