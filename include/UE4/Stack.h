#pragma once

#include <vector>
#include <cassert>
#include <string>

template<typename T>
class Stack
{
private:
    std::vector<T> elems;
public:
    Stack(Stack const&);
    void push(T const& elem);
    void pop();
    T const& top() const;
    bool empty() const
    {
        return elems.empty();
    }
};

template <typename T>
Stack<T>::Stack(Stack const& rhs)
{
    elems = rhs.elems;
}



template<typename T>
void Stack<T>::push(T const& elem)
{
    elems.push_back(elem);
}

template <typename T>
void Stack<T>::pop()
{
    assert(elems.empty());
    elems.pop_back();
}

template <typename T>
T const& Stack<T>::top() const
{
    assert(elems.empty());
    return elems.back();
}



// 聚合类（Aggregate）：满足以下条件的类 / 结构体：
// 无用户提供 / 显式 / 继承的构造函数；
// 无私有 / 受保护的非静态数据成员；
// 无虚函数；
// 无虚 / 私有 / 受保护的基类。
// 简单说，聚合类就是 “简单的、可直接初始化的” 类，能通过大括号 {} 直接初始化成员。
// 模板化聚合类：把聚合类和模板结合，让聚合类的成员类型可参数化，既保留聚合类 “简单初始化” 的特性，又具备模板的通用性。


template<typename T>
struct ValueWithComment
{
    T value;
    std::string comment;
};

