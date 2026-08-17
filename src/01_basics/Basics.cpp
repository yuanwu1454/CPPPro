#include "Basics.h"

#include <cassert>
#include <string>

namespace {
int add(const int& left, const int& right)
{
    return left + right;
}

bool isLeapYear(int year)
{
    return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
}
}

void testBasics()
{
    // const 对象：初始化后不能再次修改，适合表示固定数据。
    const int days = 31;
    int value = 9;

    // 引用是对象的别名，修改 reference 就是在修改 value。
    int& reference = value;

    // auto 根据初始化表达式推导变量类型，这里推导为 int。
    auto sum = add(reference, days);

    // assert 用于验证表达式；表达式为 false 时程序中止。
    assert(sum == 40);

    // 函数封装条件判断；闰年规则同时演示逻辑运算和取模运算。
    assert(isLeapYear(2024));
    assert(!isLeapYear(2100));

    // std::string 是标准库字符串类，size() 返回字符数量。
    assert(std::string("C++").size() == 3);
}
