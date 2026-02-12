#pragma once


template<typename A, typename B>	struct TIsSame			{ enum { Value = false	}; };
template<typename T>				struct TIsSame<T, T>	{ enum { Value = true	}; };

// 通用模版
template<typename A, typename B>
struct X
{
    A a;
    B b;
};

// 偏特化 【函数模版 不支持，结构体与类模版 支持】
template<typename T>
struct X<T, T>
{
    T a;
    T b;
};


// 全特化
template<>
struct X<int, int>
{
    int a;
    int b;
    int c;
};

template <typename T>
struct TIsPODType 
{ 
    enum { Value = __is_pod(T) };
};

template <typename T> struct TRemoveReference      { typedef T Type; };
template <typename T> struct TRemoveReference<T& > { typedef T Type; };
template <typename T> struct TRemoveReference<T&&> { typedef T Type; };