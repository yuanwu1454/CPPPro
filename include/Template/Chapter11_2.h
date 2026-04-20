#pragma once
#include <iostream>
#include <type_traits>
#include <string>
#include <vector>

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


    // 当需要转发的不是函数参数、而是中间临时值时，如何用 auto&& + std::forward<decltype(val)> 实现零拷贝的完美转发。
    
    // 模拟 get()：返回右值（临时对象）
    std::string get(int x) { return std::string("test") + std::to_string(x); }

    // 模拟 set()：重载左值/右值版本
    inline void set(const std::string& s) { std::cout << "left version copy  " << s << std::endl; }
    inline void set(std::string&& s)      { std::cout << "right value version move" << s << std::endl; }
    
    template<typename T>
    void foo(T x) {
        auto&& val = get(x);
        set(std::forward<decltype(val)>(val));  // 触发右值版本（移动）
    }

    template<typename T>
    void foo2 (T&& t)  // T&& 是转发引用（不是右值引用！）
    {
        set(std::forward<T>(t));  // 完美转发：保持实参的左/右值属性
    }


    // 引用只是避免了「参数传递时的拷贝」，但如果函数内部要把参数存为新对象，值类别才决定是否拷贝。
    // 引用解决「参数传递的拷贝」，但值类别决定「对象构造的拷贝」—— 这就是为什么都是引用，却可能触发拷贝的根本原因。
    template<typename T>
    void foo3 (T&& x)  // T&& 是转发引用（不是右值引用！）
    {
        auto t = get(x);
        foo2(t);
    }

    // 当传入引用变量时，模板参数T会被推导为「被引用的原始类型」，而非引用类型本身
    // 默认推导的「引用丢失」问题：默认推导下，即使传入引用，模板也无法感知到 “引用” 这个属性，若模板逻辑依赖于 “是否是引用类型”，则会不符合预期；
    // 显式指定模板参数的「行为修正」问题：通过显式指定T为引用类型（如int&），可以强制模板感知到引用属性，但这也可能带来风险（模板可能未设计这种场景，导致错误 / 意外行为）。
    // 模板函数：检查模板参数T是否是引用类型
    template <typename T>
    void tmplParamIsReference(T param) {
        // 判断T是否是引用类型
        if (std::is_reference_v<T>) {
            std::cout << "T is a reference type" << std::endl;
        } else {
            std::cout << "T is NOT a reference type" << std::endl;
        }
    }

    template <typename T>
    void createContainer(T size) {
        // 若T是int&，则size是引用，无法直接作为vector的大小（vector大小需是无符号整数）
        std::vector<int> vec(size); 
    }

    // 有问题的模板容器：size参数是引用类型
    template <typename T>
    class BadContainer {
    private:
        // 改为const&：仅限制通过size_修改外部变量，不限制外部直接改
        T const& size_; 
        std::vector<int> data_;
    public:
        BadContainer(T const& size) : size_(size), data_(size) {}

        void print() {
            std::cout << "size_ = " << size_ << std::endl;
            // 仍会因size_被外部修改而越界
            for (int i = 0; i < size_; ++i) {
                std::cout << data_[i] << " ";
            }
        }
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
        {
            foo(10);  // 输出：右值版本（移动）: test10
            foo3(20);
        }
        {
            int i = 10;
            int& r = i; // 引用变量r

            // 场景1：默认推导（未显式指定T）
            tmplParamIsReference(r); // 传入引用变量r，T被推导为int（非引用）
            tmplParamIsReference(i); // 传入普通变量i，T被推导为int（非引用）

            // 场景2：显式指定T为int&（强制引用类型）
            tmplParamIsReference<int&>(r); // T是int&（引用），行为改变
            tmplParamIsReference<int&>(i); // 即使传入普通i，T也被强制为int&（引用）
        }
        {
            int s = 5;
            // 显式指定T为int&，触发模板实例化错误
            createContainer<int&>(s); 
        }
        {
            int s = 3;
            BadContainer<int> container(s); // size_绑定外部变量s

            // 外部修改s，容器完全不知情
            s = 10; 
            
            // 打印时，容器会尝试访问10个元素，但实际只有3个→数组越界崩溃
            container.print(); 
        }
    }
}