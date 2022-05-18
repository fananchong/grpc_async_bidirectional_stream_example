#!/bin/bash

set -ex

mkdir -p build
pushd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make -j 8
make install
popd
