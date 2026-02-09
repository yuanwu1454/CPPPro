# CMake 最低版本要求
cmake_minimum_required(VERSION 3.10)

# 工程名称和语言：改为 CXX（C++），同时兼容 C（因为 Lua 是 C 库）
project(CPPDemo CXX C)

# 设置 C++ 语言标准（适配 .cpp 文件）
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# -------------------------- 2. 构建自己的工程 --------------------------


# 递归查找src目录下所有.cpp/.c文件（包含所有子目录）
file(GLOB_RECURSE SRC_FILES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)


# 递归查找src目录下所有.md文件（包含所有子目录）
file(GLOB_RECURSE MD_FILES
	${CMAKE_SOURCE_DIR}/book/*.md
)


file(GLOB_RECURSE HEADER_FILES ${CMAKE_SOURCE_DIR}/include/*.h ${CMAKE_SOURCE_DIR}/include/*.hpp)

# 添加可执行文件（你的主程序）
add_executable(cpp_demo ${SRC_FILES} ${HEADER_FILES} ${MD_FILES})

# 可选：添加头文件目录（如果有include目录）
include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/src)
