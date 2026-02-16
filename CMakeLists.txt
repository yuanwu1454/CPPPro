# CMake 最低版本要求
cmake_minimum_required(VERSION 3.10)

# 工程名称和语言：改为 CXX（C++），同时兼容 C（因为 Lua 是 C 库）
project(CPPDemo CXX C)

# 设置 C++ 语言标准（适配 .cpp 文件）
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -------------------------- 工具函数：自动生成IDE目录分组（核心修复层级） --------------------------
# 功能：根据文件的相对路径，在IDE中创建对应的虚拟目录层级
function(assign_source_group)
    foreach(_source IN ITEMS ${ARGN})
        if (IS_ABSOLUTE "${_source}")
            file(RELATIVE_PATH _source_rel "${CMAKE_SOURCE_DIR}" "${_source}")
        else()
            set(_source_rel "${_source}")
        endif()
        # 替换路径分隔符为IDE分组的分隔符（VS用\\，其他用/）
        string(REPLACE "/" "\\" _source_group "${_source_rel}")
        # 提取目录部分作为分组名
        get_filename_component(_source_group "${_source_group}" DIRECTORY)
        # 为文件分配分组
        source_group("${_source_group}" FILES "${_source}")
    endforeach()
endfunction(assign_source_group)


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


# 为所有文件分配IDE目录分组（核心：还原层级）
assign_source_group(
    ${SRC_FILES} 
    ${HEADER_FILES} 
    ${MD_FILES}
)

# 可选：添加头文件目录（如果有include目录）
include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/src)
