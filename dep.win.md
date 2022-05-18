# Windows 依赖库编译


## 编译 openssl

| 编译工具 | 说明                                                                            |
| :------- | :------------------------------------------------------------------------------ |
| perl     | https://strawberryperl.com/download/5.32.1.1/strawberry-perl-5.32.1.1-64bit.msi |
| nmake    | Visual Studio 2019                                                              |

**编译过程**

打开`x64 Native Tools Command Prompt for VS 2019`控制台，执行以下语句：


```bat
git clone -b OpenSSL_1_1_1k https://github.com/openssl/openssl.git
cd openssl
mkdir my_build_out
perl Configure VC-WIN64-ARM no-shared --prefix=C:\tmp1\openssl\my_build_out
nmake
nmake install
```


## 编译 grpc

| 编译工具 | 说明                                                                                               |
| :------- | :------------------------------------------------------------------------------------------------- |
| cmake    | https://github.com/Kitware/CMake/releases/download/v3.21.0-rc1/cmake-3.21.0-rc1-windows-x86_64.msi |
| vs       | Visual Studio 2019                                                                                 |


编译过程：

```bat
git clone -b v1.41.0 https://github.com/grpc/grpc.git
cd grpc
git submodule update --init
mkdir my_build_out
mkdir cmake\build
cd cmake\build
cmake -DCMAKE_INSTALL_PREFIX=C:\tmp1\grpc\my_build_out ^
    -DCMAKE_BUILD_TYPE=Debug ^
    -DgRPC_SSL_PROVIDER="package" ^
    -DOPENSSL_ROOT_DIR=C:\tmp1\openssl ^
    ../..
```

用 vs 打开 cmake\build\grpc.sln 编译
