#pragma once
#include <iostream>
#include <vector>

template<typename T>
void printFirstElement(T container)
{
    typename T::iterator x =  container.begin();
    std::cout << *x <<std::endl;
}

struct Calculator
{
    template<typename T>
    T add(T a, T b){return a+b;}

    template<typename U>
    class Nested
    {
    public:
        Nested(U v):value(v){}
        U value;
        void print()
        {
            std::cout << value <<std::endl;
        }
    };
};


template<typename T, template<typename Elem, typename Alloc = std::allocator<Elem>> class Container>
struct MyCollection
{
    Container<T> container;
    void add(T val)
    {
        container.push_back(val);
    }
    void print()
    {
        for(auto& ele: container)
        {
            std::cout << ele << " ";
        }
        std::cout << endl;
    }
};


// 基础模板（单原料模具）
template<typename X>
class XContainer {
public:
    X value;
    XContainer(X v) : value(v) {}
};

// 双原料模具
template<typename U, typename X>
class UContainer {
public:
    U u_val;
    X x_val;
    UContainer(U u, X x) : u_val(u), x_val(x) {}
    void print() {
        std::cout << "U" << u_val << " X" << x_val.value << std::endl;
    }
};


template<typename T, template<typename U, typename X> class Uc>
class TContainer{
public:
    Uc<T, XContainer<float>> inner;
    TContainer(T v1, float v2):inner(v1, XContainer<float>(v2)){};
    void print()
    {
        inner.print();
    }
};

template<typename T>
T getDefaultValue()
{
    T a = T{};
    return a;
}

// const  // 只读：保证函数不会修改数组内容，更安全
// T      // 数组元素类型（比如char）
// (&val) // val是一个引用（不是指针！）
// [N]    // 引用的对象是“长度为N的T类型数组”
template<typename T, size_t N>
void printString(const T (&val)[N])
{
    std::cout<<val << N <<endl;
}


// 接收“长度为5的int数组”的引用（固定长度）
template<typename T, size_t N>
void printAnyArray(const T (&arr)[N]) {
    cout << " size " << sizeof(arr)/sizeof(arr[0]) << " sizeN " << N  <<" type " << typeid(T).name() << endl;
    for (const auto& elem : arr) {
        cout << &elem << " ";
    }
    cout << endl;
}

// 指针的引用：修改外部指针的指向
inline void allocateInt(int*& ptr) {
    ptr = new int(100); // 动态分配内存，ptr指向新地址
}
