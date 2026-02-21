#pragma once
#include <iostream>
#include <utility>

namespace Chapter6
{
    inline void process(int& x){std::cout << "process left value" << std::endl;}
    inline void process(int&& x){std::cout << "process right value" << std::endl;}
    template<typename T>
    void forwarder(T&& param)
    {
        process(std::forward<T>(param));
    }


    class MyClass {
    public:
        MyClass(int) {
            std::cout << "default constructor int\n";
        }

        // 隐藏
        template <
            typename T,
            typename = std::enable_if_t<!std::is_same_v<std::decay_t<T>, MyClass>>
        >

        // typename = 实际上就是 利用了默认值的写法
        // 例如 typename = true_type::value_type
        MyClass(T&& arg) {
            std::cout << "perfect constructor T&&\n";
        }
        
        // 手动定义拷贝构造
        MyClass(const MyClass&) {
            std::cout << "copy constructor\n";
        }

        // 手动定义移动构造
        MyClass(MyClass&&) noexcept {
            std::cout << "move constructor\n";
        }

    };

    
    inline void Test()
    {
        {
            forwarder(5);
            int x = 5;
            forwarder(x);
            forwarder(std::move(x));
        }
        {
            MyClass a(10); 
            MyClass b(a);  
            MyClass c(std::move(a)); 
        }
    }
}
