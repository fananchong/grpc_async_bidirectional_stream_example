#!/bin/bash

set -ex

# yum groupinstall -y "Development Tools" "Development Libraries"
# yum groupinstall -y "Development Tools"

# CMake
n=$(cmake --version | grep "3." | wc -l)
if [ "$n" == "0" ]; then
    mkdir -p /tmp1/cmake
    pushd /tmp1/cmake
    if [ ! -f "cmake-3.20.1.zip" ]; then
        wget https://cmake.org/files/v3.20/cmake-3.20.1.zip
        unzip cmake-3.20.1.zip
    fi
    cd cmake-3.20.1
    ./bootstrap --parallel=32
    gmake -j 32
    gmake install
    /usr/local/bin/cmake --version
    yum remove cmake -y
    ln -sf /usr/local/bin/cmake /usr/bin/
    cmake --version
    popd
fi

# openssl
if [ ! -f ./dep/openssl/lib/libssl.a ]; then
    mkdir -p /tmp1/
    pushd /tmp1/
    if [ ! -d /tmp1/openssl ]; then
        git clone -b OpenSSL_1_1_1k https://github.com/openssl/openssl.git
    fi
    if [ ! -f /tmp1/openssl/my_build_out/lib/libssl.a ]; then
        cd openssl
        mkdir -p my_build_out
        rm -rf my_build_out/*
        my_build_out=$PWD/my_build_out
        ./config --prefix=$my_build_out --openssldir=$my_build_out
        make -j 32
        make install
    fi
    popd
    mkdir -p ./dep/openssl
    cp -rf /tmp1/openssl/my_build_out/* ./dep/openssl
fi

# gRPC CPP
if [ ! -f ./dep/grpc/lib/libgrpc.a ]; then
    mkdir -p /tmp1/
    pushd /tmp1/
    if [ ! -d /tmp1/grpc ]; then
        git clone -b v1.41.0 https://github.com/grpc/grpc.git
        pushd grpc
        git submodule update --init
        popd
    fi
    cd grpc
    mkdir -p cmake/build
    mkdir -p my_build_out
    rm -rf my_build_out/*
    my_build_out=$PWD/my_build_out
    cd cmake/build
    cmake -DCMAKE_INSTALL_PREFIX=$my_build_out \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_CXX_FLAGS="-fPIC" \
        -DCMAKE_C_FLAGS="-fPIC" \
        -DgRPC_SSL_PROVIDER="package" \
        -DOPENSSL_ROOT_DIR=/tmp1/openssl/ \
        ../..
    make -j 32
    make install
    popd
    mkdir -p ./dep/grpc
    cp -rf /tmp1/grpc/my_build_out/* ./dep/grpc
fi
