#pragma once
namespace MyNS {
    // 声明变量（告诉编译器：变量svar在其他文件定义）
    extern int svar;

    // 声明函数（告诉编译器：函数func()在其他文件定义）
    void func();
}
