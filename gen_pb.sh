#!/bin/bash

set -ex

CUR_PATH=$(pwd)

mkdir -p ${CUR_PATH}/src/proto

./dep/grpc/bin/protoc -I${CUR_PATH}/proto --grpc_out=${CUR_PATH}/src/proto --plugin=protoc-gen-grpc=${CUR_PATH}/dep/grpc/bin/grpc_cpp_plugin ${CUR_PATH}/proto/*.proto
./dep/grpc/bin/protoc -I${CUR_PATH}/proto --cpp_out=${CUR_PATH}/src/proto ${CUR_PATH}/proto/*.proto
