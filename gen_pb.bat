@echo off

set CUR_PATH=%~dp0
set OUT_PATH=%CUR_PATH%src\proto

if not exist %OUT_PATH% mkdir %OUT_PATH%
del /q %OUT_PATH%

%CUR_PATH%dep\grpc\bin\protoc.exe -I%CUR_PATH%\proto --grpc_out=%OUT_PATH% --plugin=protoc-gen-grpc=%CUR_PATH%dep\grpc\bin\grpc_cpp_plugin.exe %CUR_PATH%\proto\*.proto
%CUR_PATH%dep\grpc\bin\protoc.exe -I%CUR_PATH%\proto --cpp_out=%OUT_PATH% %CUR_PATH%\proto\*.proto
