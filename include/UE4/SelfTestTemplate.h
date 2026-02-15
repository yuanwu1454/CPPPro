#pragma once
#include <iostream>
#include <type_traits>
#include <vector>

// #include "UnrealTypeTraits.h"

// TIsSame
template <typename A, typename B>
struct TIsSame
{
    static constexpr bool Value = false;
};

template<typename T>
struct TIsSame<T, T>
{
    static constexpr bool Value = true;
};
//TEnableIf
template <bool bPredict, typename Result=void>
struct TEnableIf;

template<typename Result>
struct TEnableIf<true, Result>
{
    using Type=Result;
};


template<typename Result>
struct TEnableIf<false, Result>{};


template <typename T>
struct TIsInteger
{
    static constexpr bool Value = false;
};

template<>
struct TIsInteger<int>
{
    static constexpr bool Value = true;
};

template<>
struct TIsInteger<long>
{
    static constexpr bool Value = true;
};

// PrintValue
template<typename T>
typename TEnableIf<TIsInteger<T>::Value, void>::Type
PrintInteger(const T& value)
{
    std::cout <<"zxcv" << value <<std::endl;
}

// TRemoveReference
template <typename T>
struct TRemoveReference{
    using Type=T;
};

template<typename T>
struct TRemoveReference<T&>
{
    using Type=T;
};

template<typename T>
struct TRemoveReference<T&&>
{
    using Type=T;
};

// TTypeWrapper/TUnwrapType
template<typename T>
struct TTypeWrapper;

template<typename T>
struct TUnwrapType
{
    using Type = T;
};

template<typename T>
struct TUnwrapType<TTypeWrapper<T>>
{
    using Type=T;
};

template<typename T>
void print(const T& t)
{
    std::cout<< t<<std:: endl;
}

template<typename T>
void printKK(const T& t)
{
    std::cout<<"KK" << t<<std:: endl;
}


template<typename T>
struct A
{
    using RealT = typename TUnwrapType<T>::Type;
    void f(const RealT& t)
    {
        print(t);
    }
};

template<>
struct A<int>
{
    void f(const int& t)
    {
        printKK(t);
        A<TTypeWrapper<int>> a;
        a.f(t);
    }
};

// TIsPodType
template<typename T>
struct TIsPodType
{
    static constexpr bool Value = __is_pod(T);
};

// TChooseClass
template<bool bPredict, typename TrueClass, typename FalseClass>
struct TChooseClass;


template<typename TrueClass, typename FalseClass>
struct TChooseClass<true, TrueClass, FalseClass>
{
    using ResultType=TrueClass;
};

template<typename TrueClass, typename FalseClass>
struct TChooseClass<false, TrueClass, FalseClass>
{
    using ResultType=FalseClass;
};


// TIsSigned
template<typename T>
struct TIsSigned
{
    static constexpr bool Value = false;
};

template<> struct TIsSigned<int>{static constexpr bool Value = true;};
template<> struct TIsSigned<long>{static constexpr bool Value = true;};
template<> struct TIsSigned<short>{static constexpr bool Value = true;};

template<typename T>
struct TIsSigned<const T>
{
    static constexpr  bool Value = TIsSigned<T>::Value;
};


template<typename T>
struct TIsSigned<volatile T>
{
    static constexpr  bool Value = TIsSigned<T>::Value;
};

template<typename T>
struct TIsSigned<const volatile T>
{
    static constexpr  bool Value = TIsSigned<T>::Value;
};

// TAnd

template <typename ...Args>
struct TAnd;

template<bool LHS, typename ...RHS>
struct TAndValue
{
    static constexpr bool Value = TAnd<RHS...>::Value;    
};


template<typename ...RHS>
struct TAndValue<false, RHS...>
{
    static constexpr bool Value = false;
};


template<typename LHS, typename ...RHS>
struct TAnd<LHS, RHS...>:TAndValue<LHS::Value, RHS...>
{
};

template<>
struct TAnd<>
{
    static constexpr bool Value = false;
};


// 定义几个测试类型（带 value 静态常量）
struct TrueType { static constexpr bool Value = true; };
struct FalseType { static constexpr bool Value = false; };



// 外层类（可能作为模板参数传入）
struct MyClass {
    // 嵌套模板类（核心：MyNestedTemplate 是 MyClass 的嵌套模板）
    template <typename U>
    struct MyNestedTemplate {
        U value;
    };
};

template<typename T>
void test()
{
    typename T::template MyNestedTemplate<int> obj;
    obj.value = 3;
    std::cout << obj.value << std::endl;
}

// 默认推导，也就是传空时
template<typename T=std::string>
void f(T value="")
{
    std::cout << value<< std::endl;
}


// common_type_t

// 一、std::common_type的核心定义
// std::common_type是模板类，核心作用是推导一组类型经过隐式转换后能兼容的公共类型，其推导规则贴合 C++ 的隐式类型转换规则：
// 对数值类型：按 “提升规则” 推导（如char+int→int，int+double→double）；
// 对自定义类型：可通过特化std::common_type自定义推导规则；
// 支持 1 个或多个类型参数（C++17 起支持任意数量，C++11/14 至少需 2 个）。

// 推导两个参数的公共返回类型
template <typename T, typename U>
std::common_type_t<T, U> generic_max(T a, U b) {
    return (a > b) ? a : b;
}

template <typename... Ts>
std::vector<std::common_type_t<Ts...>> make_vector(Ts&&... args) {
    return {std::forward<Ts>(args)...};
}


// std::decay是<type_traits>头文件中的模板类，其作用是按照 C++ 函数参数传递的规则对类型进行 “退化”，具体包含以下 3 个核心行为：
// 移除类型的引用属性（左值引用 / 右值引用都被移除）；
// 移除类型的const/volatile 限定符；
// 将数组类型退化为对应的指针类型，将函数类型退化为函数指针类型。

template <typename T>
void func(T&& arg) {  // 万能引用
    // 无论传入什么类型，都退化到基础类型
    using RawType = std::decay_t<T>;
    RawType copy = arg;  // 安全拷贝，避免引用/数组等问题
}