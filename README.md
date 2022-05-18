# grpc_async_bidirectional_stream_example

gRPC C++ 异步双向流例子


## 依赖

- gcc 7 以上
    ```shell
    yum install -y centos-release-scl
    scl enable devtoolset-7 bash
    ```
    或者
    ```shell
    yum install -y centos-release-scl
    source /opt/rh/devtoolset-7/enable
    ```

- 第 3 方库
    ```shell
    ./dep.linux.sh
    ```

## 编译

```shell
./build.linux.sh
```


## 例子包含功能

- 异步一元函数处理
- 异步双向流处理
- 支持多线程
- 支持同个流处理内，发送 N 次消息





