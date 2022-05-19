#!/bin/bash

set -e
set -x

rm -rf build
mkdir build
pushd build

conan install .. --build=missing -o boost:without_fiber=True -o boost:without_stacktrace=True
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
