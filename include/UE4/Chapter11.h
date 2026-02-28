#pragma once
//
// 在 C++ 中，有几种类型非常适合用作回调：它们既可以作为函数调用参数传递，也能通过 f(...) 语法直接调用：
// ・函数指针类型（Pointer-to-function types）
// ・重载了 operator() 的类类型（有时也称为函数对象 / 仿函数（functors）），包括 lambda 表达式
// ・拥有 “可转换为函数指针 / 函数引用” 的转换函数的类类型
// 这些类型统称为函数对象类型（function object types），而该类型的取值即为函数对象（function object）

#include <iostream>
#include <vector>
#include <utility>
#include <functional>
#include <type_traits> // for std::is_same<> and invoke_result<>

namespace Chapter11
{
    template<typename Iter, typename Callable>
    void foreach (Iter current, Iter end, Callable op)
    {
        while (current != end) { //aslong as not reached the end
            op(*current);
            // call passed operator for current element
            ++current;
        }
    }

    // a function to call:
    void func(int i)
    {
        std::cout << "func() called for: " << i << "\n";
    }
    // a function object type (for objects that can be used as functions):
    class FuncObj {
    public:
        void operator() (int i) const { //Note: const member function
            std::cout << "FuncObj::op() called for: " << i << "\n";
        }
    };


    template<typename Iter, typename Callable, typename... Args>
    void foreach (Iter current, Iter end, Callable op, Args const&... args)
    {
        while (current != end) {
            std::invoke(op,
            args...,
            *current);
            ++current;
        }
    }
    
    class MyClass {
        public:
            void memfunc(int i) const {
                std::cout << "MyClass::memfunc() called for: " << i << "\n";
            }
    };


    // 利用RAII处理收尾逻辑的辅助类
    struct CallFinalizer {
        ~CallFinalizer() {
            // 析构时执行调用结束的日志（可观测行为）
            std::cout << "Callable execution finished (RAII cleanup)\n";
        }
    };

    template <typename Callable, typename... Args>
    decltype(auto) safe_wrap(Callable&& callable, Args&&... args) {
        // 声明RAII对象：无论返回值是否为void，析构时都会执行收尾逻辑
        CallFinalizer finalizer;

        // 无需临时变量存储返回值，直接调用并转发
        return std::invoke(std::forward<Callable>(callable), 
                           std::forward<Args>(args)...);
    }

    // 测试1：返回void的可调用体
    void void_func() {
        std::cout << "void_func executed\n";
    }

    // 测试2：返回引用的可调用体
    std::ostream& ref_func(std::ostream& os) {
        return os << "ref_func executed\n";
    }
    
    inline void Test()
    {
        {
            std::vector<int> primes = { 2, 3, 5, 7, 11, 13, 17, 19 };
            foreach(primes.begin(), primes.end(), // range
            func);// function as callable (decays to pointer)
            foreach(primes.begin(), primes.end(), // range
            &func);// function pointer as callable
            foreach(primes.begin(), primes.end(), // range
            FuncObj());// function object as callable
            foreach(primes.begin(), primes.end(), // range
            [] (int i) {
            // lambda as callable
            std::cout << "lambda called for: " << i << "\n";
            });
        }

        {
            std::vector<int> primes = { 2, 3, 5, 7, 11, 13, 17, 19 };
            // pass lambda as callable and an additional argument:
            foreach(primes.begin(), primes.end(),
            // elements for 2nd arg of lambda
            [](std::string const& prefix, int i) { // lambda to call
                    std::cout << prefix << i << "\n";
                },
            "- value: ");
            // 1st arg of lambda
            // call obj.memfunc() for/with each elements in primes passed as argument
            MyClass obj;
            foreach(primes.begin(), primes.end(), // elements used as args
            &MyClass::memfunc,// member function to call
            obj);
            // object to call memfunc() fo
        }
        {
            safe_wrap(void_func);
            safe_wrap(ref_func, std::cout);
        }
    }
}