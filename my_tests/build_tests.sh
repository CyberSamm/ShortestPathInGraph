#!/bin/bash

./clean.sh
if [[ ! -e build ]] || [[ ! -d build ]]; then
    mkdir build;
fi
cd build
cmake ..
make
