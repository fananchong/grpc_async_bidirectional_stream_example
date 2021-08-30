@echo off

set CUR_PATH=%~dp0
set OUT_PATH=%CUR_PATH%test

if not exist %OUT_PATH% mkdir %OUT_PATH%
del /q %OUT_PATH%

%CUR_PATH%..\..\dep\grpc\bin\protoc.exe -I%CUR_PATH%..\..\proto --go_out=plugins=grpc:%OUT_PATH% --plugin=%CUR_PATH%  %CUR_PATH%..\..\proto\*.proto
