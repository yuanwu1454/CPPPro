#include "AutoClassTest.h"
#include <iostream>
#include <vector>
using namespace  std;

// 模板变量，类型依赖模板参数
template <typename T, typename U>
auto func(T a, U b) { return a + b; }

// C++14 decltype(auto)（精准推导类型，保留所有限定符）

// 能用 auto 就用 auto（现代 C++ 开发的最佳实践），除非需要显式指定类型来限制变量范围。

void AutoClassTest::Test()
{
    // todo
    {
        auto a = 100;
        auto b = 3.14;
        auto c = "hello";
        auto d = vector<int>{1,3,5};

        cout << typeid(a).name() <<endl;
        cout << typeid(b).name() <<endl;
        cout << typeid(c).name() <<endl;
        cout << typeid(d).name() <<endl;
    }

    {
        // 场景 1：简化 STL 迭代器的声明（最经典的用法）
        // 场景 2：简化复杂的函数返回值 / 模板类型
        // 场景 3：配合范围 for 循环（C++11），简化遍历
        // 场景 4：避免类型匹配错误
        vector<int> v = {1,2,3,4};
        // vector<int>::iterator it  = v.begin();
        auto it = v.begin();

        for(auto x : v)
        {
            cout << x<< " ";
        }
        cout << endl;
        auto res = func(10, 3.14);
        cout << res<<endl;
    }

    {
        int n = sizeof(int); // 虽然能编译，但类型不匹配（size_t -> int），存在隐式转换风险
        // auto n = sizeof(int); // 编译器直接推导为size_t，无转换风险，类型完全匹配
        cout << "sizeof int is " <<n <<endl; 
    }

    {
        // 无法退到数组类型
        int arr[5] = {1,2,3,4,5};
        auto x = {1,2,3,4,5};
    }
    {

        // 核心区别：
        // 顶层 const：修饰变量 / 对象本身，“自己不能改”，赋值 / 推导时可忽略；
        // 底层 const：修饰指针 / 引用指向的内容，“指向的东西不能改”，赋值 / 推导时必须保留；
        // 关键场景：
        // 指针：T* const 是顶层，const T* 是底层；
        // 引用：只有底层 const（const T&），无顶层 const；
        // 赋值：顶层 const 不影响兼容，底层 const 要求 “const 属性向下兼容（非 const→const）”；
        // 推导：顶层 const 被忽略，底层 const 被保留；
        // 记忆口诀：
        // 看 const 的位置：const 在 * 左边 → 底层 const（管内容）；const 在 * 右边 → 顶层 const（管指针）；
        // 无指针 / 引用时，const 都是顶层 const（比如 const int a）。

        const int a = 10;
        auto b = a; // b是int（丢弃顶层const，因为b是新变量，可修改）

        b = 20; // 正确

        decltype(auto) c  = a;
        // c = 20;

        const int* p = &a;
        auto q = p; // q是const int*（保留底层const，因为指针指向的对象是const的）
        // *q = 20; // 报错，指向的对象是const的

        auto& r = a; // r是const int&（引用会保留所有const限定）
        // r = 20; // 报错

        auto p2 = &a;
        // *p2 = 5;//报错
    }
}
