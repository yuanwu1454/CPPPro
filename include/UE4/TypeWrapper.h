#pragma once
#include <iostream>



// 这正是TTypeWrapper最核心的设计巧思 —— 本质就是给同一基础类型（比如 int）“造一个新的模板参数形态”
// 让编译器能同时区分 “特化版本” 和 “主模板版本”，从而实现：对同一类型，既能调用专属的特化逻辑，又能调用通用的主模板逻辑，还不会触发递归。
template <typename T>
struct TTypeWrapper;

template <typename T>
struct TUnwrapType
{
    typedef T Type;
};

template <typename T>
struct TUnwrapType<TTypeWrapper<T>>
{
    typedef T Type;
};

template<typename  T>
void DoSomething(T t)
{
    std::cout <<"DoSomething " << t <<std::endl;
}

template<typename  T>
void DoSomethingElseFirst(T t)
{
    std::cout <<"DoSomethingElseFirst " << t <<std::endl;
}

// #define REC 1

#ifdef REC
// Before
template <typename T>
struct TThing
{
    void f(T t)
    {
        DoSomething(t);
    }
};
 
template <>
struct TThing<int>
{
    void f(int t)
    {
        DoSomethingElseFirst(t);
        f(t); // 会导致无限递归，但是编译期无法察觉
    }
};
#else
// After
template <typename T>
struct TThing
{
     // typename 告知 TUnwrapType<T>::Type 是一个 类型
     // typedef 起别名 
     typedef typename TUnwrapType<T>::Type RealT;

     void f(RealT t)
     {
        std::cout <<typeid(t).name() << std::endl;
        DoSomething(t);
     }
};

template <>
struct TThing<int>
{
 void f(int t)
 {
         DoSomethingElseFirst(t);
         // TThing<TTypeWrapper<int>>::f(t); // works 不注释就无法工作

        // f(t);

         TThing<TTypeWrapper<int>> TempThing;
     // 特化成这个样子 
     // template <typename TTypeWrapper<int>>
     // struct TThing
     // {
     //     // typename 告知 TUnwrapType<T>::Type 是一个 类型
     //     // typedef 起别名 
     //     typedef typename TUnwrapType<TTypeWrapper<int>>::Type RealT;
     //
     //     void f(RealT t) // int
     //     {
     //         std::cout <<typeid(t).name() << std::endl;
     //         DoSomething(t);
     //     }
     // };
     TempThing.f(t); 
 }
};
#endif


