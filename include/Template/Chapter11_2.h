#pragma once
#include <iostream>
#include <type_traits>

// . 什么是 Type Traits？
// Type traits 是 C++11 及以后标准库（<type_traits> 头文件）提供的一套模板工具，核心作用是：
// 查询类型属性：判断一个类型是否是指针 / 数组 / 类、是否可拷贝、是否为 const 等；
// 修改类型属性：将类型转为 const/volatile、移除指针 / 引用、提取函数返回值类型等；
// 泛型适配：让模板代码根据类型的特性执行不同逻辑（比如编译期分支）。
// 它们的本质是编译期计算的模板元函数，结果通常通过 ::value（布尔值）或 ::type（修改后的类型）暴露。

// 你想了解 C++ 中的 std::addressof<>() 函数模板，核心是理解它解决的问题 ——即使类型重载了 operator&（取地址运算符），
// 也能正确获取对象 / 函数的实际内存地址，这在泛型编程（比如智能指针、通用工具函数）中尤为重要。


namespace Chapter11_2_NS
{
    
    // 辅助函数：根据类型是否可拷贝，选择拷贝或移动
    template <typename T>
    void copy_or_move(T& dest, T src) {
        // C++17 可直接用 if constexpr（编译期分支）
        if constexpr (std::is_copy_constructible<T>::value) {
            dest = src; // 拷贝
            std::cout << "Used copy for type: " << typeid(T).name() << std::endl;
        } else {
            dest = std::move(src); // 移动
            std::cout << "Used move for type: " << typeid(T).name() << std::endl;
        }
    }
    
    // 辅助函数：打印类型名（简化版，实际可通过编译器扩展实现）
    template <typename T>
    void print_type_name(const char* name) {
        std::cout << name << ": " << typeid(T).name() << std::endl;
    }


    // 定义一个重载了 operator& 的类
    class SmartLikeClass {
    private:
        int value;
    public:
        SmartLikeClass(int v) : value(v) {}

        // 重载取地址运算符，返回一个"假地址"（模拟智能指针的场景）
        void* operator&() const {
            std::cout << "Overloaded operator& called! " << std::endl;
            // 返回一个无关的地址（比如全局变量的地址）
            static int dummy = 0;
            return &dummy;
        }

        // 暴露真实值（仅用于验证）
        int getValue() const { return value; }
    };
    
    
    inline void Test()
    {
        {
            // 1. 判断基础类型特性
            std::cout << "int is integral: " << std::is_integral<int>::value << std::endl;       // 1 (true)
            std::cout << "double is integral: " << std::is_integral<double>::value << std::endl; // 0 (false)
    
            // 2. 判断指针/引用
            using T = const int&;
            std::cout << "T is const: " << std::is_const<T>::value << std::endl;                 // 0（引用本身无 const，const 修饰的是 int）
            std::cout << "T is reference: " << std::is_reference<T>::value << std::endl;         // 1
    
            // 3. 判断类类型
            struct MyClass {};
            std::cout << "MyClass is class: " << std::is_class<MyClass>::value << std::endl;     // 1
            std::cout << "MyClass is trivial: " << std::is_trivial<MyClass>::value << std::endl; // 1（空结构体是平凡类型）
        }
        {
            // 1. 移除引用/指针/const
            using T1 = const int&;
            using T2 = std::remove_reference<T1>::type;       // const int
            using T3 = std::remove_const<T2>::type;           // int
            print_type_name<T1>("const int&");                // 输出：const int&: int const&
            print_type_name<T2>("remove_reference<T1>");      // 输出：remove_reference<T1>: int const
            print_type_name<T3>("remove_const<T2>");          // 输出：remove_const<T2>: int
    
            // 2. 添加指针/const
            using T4 = std::add_pointer<T3>::type;            // int*
            using T5 = std::add_const<T4>::type;              // const int*
            print_type_name<T4>("add_pointer<T3>");           // 输出：add_pointer<T3>: int*
            print_type_name<T5>("add_const<T4>");             // 输出：add_const<T4>: int const*
        }
        {
            // 1. 可拷贝类型（int）
            int a = 10, b = 0;
            copy_or_move(b, a);
            std::cout << "b = " << b << std::endl; // 输出：b = 10
    
            // 2. 不可拷贝类型（std::unique_ptr）
            std::unique_ptr<int> p1(new int(20)), p2;
            copy_or_move(p2, std::move(p1)); // 注意：unique_ptr 不可拷贝，需先 move
            std::cout << "*p2 = " << *p2 << std::endl; // 输出：*p2 = 20
        }
        
        {
            SmartLikeClass obj(42);

            // 1. 直接用 & 取地址：调用重载的 operator&，得到假地址
            void* fake_addr = &obj;
            std::cout << "Address via &obj:    " << fake_addr << std::endl;

            // 2. 用 std::addressof 取地址：绕过重载，得到真实地址
            void* real_addr = std::addressof(obj);
            std::cout << "Address via addressof: " << real_addr << std::endl;
        }
    }
}