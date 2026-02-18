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
    Stack()=default;
    Stack(Stack const&);
    void push(T const& elem);
    void pop();
    T const& top() const;
    bool empty() const
    {
        return elems.empty();
    }
    void printOn(std::ostream& strm) const
    {
        // 使用 T const& 更直观一点 const 修饰的是T
        // 例如 T const* 表示修饰的就是值
        // 还有 就是T* const 表示修饰的就是指针
        for (T const& elem: elems)
        {
            strm<<elem<<" ";
        }
        strm<<endl;
    }
    friend std::ostream& operator<< (std::ostream& strm,
    Stack<T> const& s) {
            s.printOn(strm);
            return strm;
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
    assert(!elems.empty());
    elems.pop_back();
}

template <typename T>
T const& Stack<T>::top() const
{
    assert(!elems.empty());
    return elems.back();
}

template<typename T>
class Stack<T*> {
private:
    std::vector<T*> elems; // elements
    public:
    void push(T*); // push element
    T* pop(); // pop element
    T* top() const; // return top element
    bool empty() const { // return whether the stack is empty
        return elems.empty();
    }
};
template<typename T>
void Stack<T*>::push (T* elem)
{
    elems.push_back(elem); // append copy of passed elem
}
template<typename T>
T* Stack<T*>::pop ()
{
    assert(!elems.empty());
    T* p = elems.back();
    elems.pop_back(); // remove last element
    return p; // and return it (unlike in the general case)
}
template<typename T>
T* Stack<T*>::top () const
{
    assert(!elems.empty());
    return elems.back(); // return copy of last element
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

// 检查T是否有size()成员函数（返回值可转换为size_t）
template <typename T>
struct has_size_member {
private:
    // 重载1：如果T有size()，匹配这个版本（返回std::true_type）
    template <typename U>
    // 为啥不返回 true_type 而是返回 true_type{} C++ 的返回类型推导规则要求这里必须是一个 “表达式”，而不是类型本身
    // decltype(int) c; error
    // decltype(int{}) c; ok
    static auto check(int) -> decltype(std::declval<U>().size(), std::true_type{});
    // 重载2：否则匹配这个版本（返回std::false_type）
    template <typename U>
    // 因为这个函数永远不会被 “实际调用”，只需要让编译器做 “类型推导”，不需要函数体。
    static std::false_type check(...);
public:
    static constexpr bool value = decltype(check<T>(0))::value;
};

// 模板中检查约束
template <typename T>
void printSize(const T& obj) {
    static_assert(has_size_member<T>::value, "T must have size() member function!");
    std::cout << "Size" << obj.size() << std::endl;
}

    
struct MyString {
    size_t size() const { return 5; }
};

struct NoSizeType {};


// 或者定义一个 单参数的终止条件
// template<typename T>
// void printMul(T arg)
// {
//     std::cout << arg<<std::endl;
// }

template<typename T, typename ...Args>
void printMul(T first, Args... args)
{
    std::cout << first<<" ";
    // if (sizeof... (args) > 0 ) error
    // 用运行时的 if 判断代替了编译期的递归终止函数，导致参数包为空时编译器找不到匹配的函数；
     if constexpr (sizeof...(args) > 0)
    {
        printMul(args...);        
    }
}

// template<typename... Types>
// void printFold (Types const&... args)
// {
//     (std::cout << ... << args) << '\n';
// }