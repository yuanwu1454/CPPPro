#pragma once
#include <iostream>
#include <vector>


template <typename T>
void printFirstElement(T& container) {
    // 错误写法：T::iterator 是依赖于 T 的嵌套类型，必须加 typename
    // T::iterator it = container.begin();
    
    // 正确写法：用 typename 告诉编译器 T::iterator 是一个类型
    typename T::iterator it = container.begin();
    std::cout <<std::endl << "XXXX" << *it << std::endl;
}


class Calculator
{
public:
    template<typename T>
    T add(T a, T b)
    {
        return a+b;
    }
    template<typename U>
    class Nested
    {
    public:
        U Value;
        Nested(U v):Value(v){}
        void print(){std::cout<<Value<<std::endl;}
    };
};

template<typename T, template<typename Elem, typename Alloc = std::allocator<Elem>> class Container>
struct MyCollection
{
    Container<T> data;
public:
    void add(const T& val){data.push_back(val);}
    void print()
    {
        for(const auto& ele : data)
        {
            std::cout<< ele << " ";
        }
        std::cout<< std::endl;
    }
};

//4. 零初始化（Zero Initialization）
// 模板中处理内置类型（如 int、double）时，确保未初始化的变量被初始化为 0（而非随机值），避免未定义行为。
template<typename T>
T getDefaultValue()
{
    T val{};
    return val;
}


template<typename T, std::size_t N>
void printString(const T(&str)[N])
{
    std::cout << "String: " << str << ", Length: " << N-1 << std::endl;
}
