#!/bin/bash

set -ex

# yum groupinstall -y "Development Tools" "Development Libraries"
# yum groupinstall -y "Development Tools"

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
