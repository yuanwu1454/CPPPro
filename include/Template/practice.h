#pragma once
#include <assert.h>
#include <string>
namespace Practice
{

    // 编写一个模板函数 maxValue，能够接收任意两个同类型的参数，返回其中的较大值。要求支持整数、浮点数、字符串（按字典序比较）等类型。 
    // 模板类 Array：封装固定大小的数组
    // 定义一个模板类 Array，用于封装一个固定大小的数组。要求实现以下功能：
    // 构造函数初始化数组大小；
    // 重载 [] 运算符，用于访问数组元素；
    // 成员函数 size() 返回数组的大小；
    // 成员函数 print() 打印数组所有元素。

    template<typename T>
    void swapValues(T& a, T& b)
    {
        if(&a == &b ){return;}
        T t;
    }
    
    inline void Test(){
    }
}
