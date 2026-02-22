#pragma once
#include <iostream>
#include <vector>
#include <chrono>
#include <type_traits>
// 要点 1：测试模板时使用不同长度的字符串字面量
// 解释：字符串字面量（如"abc"、"12345"）的类型是const char[N]（N 为长度 + 1），不同长度的字符串字面量类型不同，测试模板时用不同长度能暴露类型推导的问题。

// 要点 2：值传递的模板参数会退化，引用传递不会
// 退化（decay）：数组→指针、函数→函数指针、顶层 const/volatile 被移除；
// 值传递参数会触发退化，引用传递则保留原始类型（如数组的长度信息）。

// 要点 3：std::decay<> 可让引用传递的模板参数退化
// 解释：std::decay<T>是类型萃取工具，能模拟值传递的退化规则，即使参数是引用传递，也能得到退化后的类型。

// 要点 4：std::cref ()/std::ref () 让值传递模板接收引用参数
// std::ref()：包装左值为引用包装器（std::reference_wrapper）；
// std::cref()：包装 const 左值为 const 引用包装器；
// 模板参数声明为值传递时，用这两个函数可间接传递引用，避免拷贝大对象。

// 要点 5：值传递模板参数简单但性能未必最优
// 解释：值传递语法简单，但对于大对象（如大字符串、自定义类），值传递会触发拷贝，性能差；引用传递可避免拷贝，但语法稍复杂。

// 要点 6：返回值通常值传递（模板参数可能无法直接作为返回类型）
// 解释：返回值优先值传递（移动语义会优化拷贝）；若模板参数是引用类型，直接返回会导致问题，需退化后返回。

// 要点 7：性能关键时必须实测，别依赖直觉
// 解释：直觉认为 “引用一定比值快”，但小对象（如 int、char）的值传递可能比引用快（引用需解引用，有开销），必须实测验证。

// 总结
// 类型退化：值传递模板参数会退化（数组→指针），引用传递不退化，std::decay可手动触发退化；
// 引用包装器：std::ref/std::cref能让值传递模板间接接收引用参数，避免大对象拷贝；
// 性能选择：模板参数优先值传递（简单），仅在大对象、不可拷贝等场景用引用；返回值优先值传递，需用std::decay处理引用类型；
// 性能验证：小对象值传递可能更快，性能关键时必须实测，不能依赖直觉。

namespace Chapter7
{
    template<typename T>
    void passByValue(T param)
    {
        std::cout << "value type is " << typeid(T).name() <<std::endl;
    }
    template<typename T>
    void passByReference(T& param)
    {
        std::cout << "value type is " << typeid(T).name() <<std::endl;
    }

    template<typename T>
    void passByReferenceWithDecay(const T& param)
    {
        std::cout << "init " << typeid(T).name() << std::endl;
        std::cout << "decay " << typeid(std::decay_t<T>).name() << std::endl;
    }

    // 小对象：int
    int smallNum = 5;

    // 值传递（1亿次）
    template <typename T>
    void passSmallByValue(T param) {
        (void)param;
    }

    // 引用传递（1亿次）
    template <typename T>
    void passSmallByReference(const T& param) {
        (void)param;
    }


    // 错误示例：返回引用类型（模板参数T是引用）
    template <typename T>
    T badReturn(T param) {
        return param; // 若T是int&，返回值是int&，可能返回局部变量引用（未定义行为）
    }

    // 正确示例：用decay退化后值传递返回
    template <typename T>
    typename std::decay_t<T> goodReturn(T param) {
        return param; // 无论T是啥类型，都退化后值传递返回
    }

    
    inline void Test()
    {
        {
            // 值传递的模板参数会退化，引用传递不会
            const char ptr[5] = "abce";
            passByValue(ptr);
            passByReference(ptr);
        }
        {
            const char str[5] = "test";
            passByReferenceWithDecay(str); // T推导为const char[5]，decay后为const char*
        }

        // 要点 7：性能关键时必须实测，别依赖直觉
        // 解释：直觉认为 “引用一定比值快”，但小对象（如 int、char）的值传递可能比引用快（引用需解引用，有开销），必须实测验证。
        {
            // 计时值传递
            auto start1 = std::chrono::high_resolution_clock::now();
            for (long long i = 0; i < 100000000; ++i) {
                passSmallByValue(smallNum);
            }
            auto end1 = std::chrono::high_resolution_clock::now();
            auto dur1 = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1).count();
            
            auto start2 = std::chrono::high_resolution_clock::now();
            for (long long i = 0; i < 100000000; ++i) {
                passSmallByReference(smallNum);
            }
            auto end2 = std::chrono::high_resolution_clock::now();
            auto dur2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2).count();
    
            std::cout << "value cost time is  " << dur1 << "ms" << std::endl;
            std::cout << "reference cost time is " << dur2 << "ms" << std::endl;
        }

        {
            int num = 10;
            int& ref = num;
    
            // badReturn(ref)：T推导为int&，返回int&，但param是值传递的副本，返回其引用→未定义行为
            // std::cout << badReturn(ref) << std::endl; // 可能崩溃/输出随机值

            // goodReturn(ref)：T推导为int&，decay后为int，值传递返回10
            std::cout << goodReturn(ref) << std::endl; // 输出10
        }
    }
}
