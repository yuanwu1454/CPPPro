@echo off
chcp 65001 > nul 2>&1  # 设置编码为 UTF-8，避免中文乱码
setlocal enabledelayedexpansion

echo ==============================
echo 开始清理并重新构建工程
echo ==============================

:: 1. 删除当前目录下的 build 文件夹（包含所有子文件/子文件夹）
if exist "build" (
    echo [1/3] 正在删除 build 文件夹...
    rd /s /q "build" > nul 2>&1  # /s 删除目录及子项，/q 静默删除（无确认）
    if !errorlevel! equ 0 (
        echo [1/3] build 文件夹删除成功
    ) else (
        echo [1/3] 警告：build 文件夹删除失败（可能被占用）
    )
) else (
    echo [1/3] 未找到 build 文件夹，跳过删除步骤
)

:: 2. 重新创建 build 文件夹
echo [2/3] 正在创建 build 文件夹...
md "build" > nul 2>&1
if exist "build" (
    echo [2/3] build 文件夹创建成功
) else (
    echo [2/3] 错误：build 文件夹创建失败！
    pause
    exit /b 1
)

:: 3. 进入 build 目录，执行 cmake 生成工程（默认使用系统默认编译器）
echo [3/3] 正在执行 cmake 生成工程文件...
cd /d "build" || (
    echo [3/3] 错误：无法进入 build 目录！
    pause
    exit /b 1
)

:: 核心 cmake 命令（可根据你的需求修改，比如指定编译器/生成器）
cmake ..
if !errorlevel! equ 0 (
    echo [3/3] cmake 工程生成成功！
) else (
    echo [3/3] 错误：cmake 工程生成失败！
    pause
    exit /b 1
)

echo ==============================
echo 工程构建流程完成
echo ==============================
pause
endlocal