#include "Decltype.h"
#include <iostream>
#include <vector>
using namespace  std;
// 出现的原因：
// 1. 对于简单变量，你可以手动写类型，但对于复杂表达式（比如函数返回值、模板中的泛型类型），手动推导类型容易出错且不灵活；
// 2. 模板编程中，泛型类型的推导（比如 T 和 U 运算后的类型）缺乏统一、简洁的方式；
// 3. C++11 引入了自动类型推导的 auto，但 auto 只能推导变量的类型，无法 “提取” 任意表达式的类型（比如想定义一个和某个表达式类型相同的变量，或声明函数返回值）。
// 是什么
// 编译器分析并返回一个表达式的编译期类型，不会执行这个表达式（仅做类型推导）。

// decltype 真正起作用是 编译期
// auto 的核心作用是让编译器在编译时，根据变量的初始化表达式推导变量的类型，
// typeid 打印类型名 / 类型判断 运行时

// auto 和 decltype 的核心区别不在 “是否编译期”，而在推导规则：
// auto 简化声明（忽略引用 /const），decltype 精准查询（保留所有类型属性）；
// C++ 中所有类型推导（auto/decltype/ 模板类型推导）都是编译期行为，这是 C++ 静态类型的本质决定的。



template<typename T, typename U>
auto add(T a, U b)->decltype(a+b)
{
    return a+b;
}

string get_str() {
    return "hello decltype";
}


void Decltype::Test()
{
    {
        // 1. 推导普通变量类型
        int x = 5;
        decltype(x) y = 10; // y 的类型是 int
        cout << typeid(y).name() << endl; // 输出：int（不同编译器可能显示略有差异）

        // 2. 推导字面量类型
        decltype(3.14) pi = 3.14159; // pi 的类型是 double
        decltype('a') ch = 'b'; // ch 的类型是 char
    }

    // 如果表达式是单纯的变量 / 标识符，推导结果和变量的实际类型完全一致（包括 const、引用）；
    // 如果表达式是带运算的复杂表达式（比如 x + y），推导结果是表达式的 “值类型”（失去引用属性）。
    {
        // 2. 推导复杂表达式类型（保留引用 /const 属性）
        const int a = 10;
        int b = 20;
        int& ref_b = b;

        // 1. 推导单纯变量（保留 const）
        decltype(a) c = 15; // c 的类型是 const int
        // c = 20; // 报错！因为 c 是 const int，不能修改

        // 2. 推导引用变量（保留引用）
        decltype(ref_b) d = b; // d 的类型是 int&（引用）
        d = 30;
        cout << b << endl; // 输出 30（d 是 b 的引用，修改 d 就是修改 b）

        // 3. 推导复杂表达式（失去引用/const）
        decltype(a + b) e = 30; // a+b 是 int 类型（const 被去掉）
        e = 40; // 正常运行
        cout << e << endl; // 输出 40
    }

    {
        // 3. 结合 auto 推导函数返回值（尾置返回类型）
        // 测试不同类型的参数
        auto res1 = add(10, 20); // res1 是 int
        auto res2 = add(3.14, 5); // res2 是 double
        auto res3 = add('a', 1); // res3 是 int（字符 'a' 转成 ASCII 码 97，加 1 得 98）

        cout << res1 << endl; // 30
        cout << res2 << endl; // 8.14
        cout << res3 << endl; // 98
    }
    {
        decltype(get_str()) str = get_str(); // str 的类型是 string
        cout << str << endl; // 输出：hello decltype
    }
}
