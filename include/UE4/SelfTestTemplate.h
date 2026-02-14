#pragma once
#include <iostream>

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
    static constexpr bool Value = __is_pod(T) ;
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
template<typename... Type>
struct TAnd;

template<bool LHS, typename ...RHS>
struct TAndValue
{
    static bool constexpr Value = TAnd<RHS...>::Value;
};

template<typename ...RHS>
struct TAndValue<false, RHS...>
{
    static bool constexpr Value = false;
};

template<typename LHS, typename... RHS>
struct TAnd<LHS, RHS...>:TAndValue<LHS::Value, RHS...>
{
};

template<>
struct TAnd<>
{
    static bool constexpr Value = true;
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