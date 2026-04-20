#!/bin/bash

# 1. 进入项目根目录
cd "$(dirname "$0")"

# 2. 如果没有 build 文件夹，就创建
if [ ! -d "build" ]; then
    mkdir build
fi

# 3. 进入 build
cd build

# 4. 生成 Makefile（关键！必须执行 cmake）
cmake ..

# 5. 编译
make -j4

# 6. 运行程序
./cpp_demo