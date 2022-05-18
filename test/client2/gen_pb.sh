#!/bin/bash

set -x

CUR_PATH=$(pwd)

which protoc-gen-go
if [ "$?" != "0" ]; then
    go install google.golang.org/protobuf/cmd/protoc-gen-go@latest
fi
which protoc-gen-go-grpc
if [ "$?" != "0" ]; then
    go install google.golang.org/grpc/cmd/protoc-gen-go-grpc@latest
fi

${CUR_PATH}/../../dep/grpc/bin/protoc -I${CUR_PATH}/../../proto --go_out=${CUR_PATH} --go-grpc_out=${CUR_PATH} ${CUR_PATH}/../../proto/*.proto
