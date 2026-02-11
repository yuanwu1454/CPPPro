#pragma once
#include <ostream>

#include "UE4/TEnableIf.h"
#include <iostream>
// 第一步：定义判断「是否为指针类型」的 trait
template <typename T>
struct TIsPointer
{
    enum { Value = false };
};
// 特化：任意 T* 都是指针类型
template <typename T>
struct TIsPointer<T*>
{
    enum { Value = true };
};


// 第二步：重载函数，用 TEnableIf 区分
// 重载1：非指针类型（Predicate = !TIsPointer<T>::Value）
template <typename T>
typename TEnableIf<!TIsPointer<T>::Value, void>::Type
PrintValue(const T& Value)
{
    // UE_LOG(LogTemp, Log, TEXT("非指针值：%s"), *FString::FromInt(Value)); // 简化示例，仅适配数值
    std::cout << Value << std::endl;
}

// 重载2：指针类型（Predicate = TIsPointer<T>::Value）
template <typename T>
typename TEnableIf<TIsPointer<T>::Value, void>::Type
PrintValue(T Value)
{
    if (Value)
    {
        std::cout << (void*)Value<< *Value << std::endl;
    }
    else
    {
        std::cout << "empty ptr" << std::endl;
    }
}


// 基础使用

// 第一步：定义判断「是否为整数类型」的 trait（Unreal 风格）
template <typename T>
struct TIsInteger
{
    // 默认 false
    enum { Value = false };
};
// 特化：int32/int64 为整数类型
template <> struct TIsInteger<int32> { enum { Value = true }; };
template <> struct TIsInteger<int64> { enum { Value = true }; };



// 第二步：使用 TEnableIf 限制函数
// 仅当 T 是整数类型时，TEnableIf<...>::Type 存在，函数才会被实例化
template <typename T>
typename TEnableIf<TIsInteger<T>::Value, void>::Type
PrintInteger(const T& Value)
{
    std::cout <<"Value is "<<  Value << std::endl;
}