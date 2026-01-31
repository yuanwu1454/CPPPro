#pragma once
#include "Common.h"
#include <string>
using namespace  std;

template<typename T>
T maxValue(T a, T b)
{
    return a>b?a:b;
}

template<>
inline string maxValue(string a, string b)
{
    return a.length()>b.length()?a:b;
}


class TemplateTest
{
public:
    static void Test();
};


template<typename T>
class MyContiner
{
public:
    MyContiner(T inData):data(inData){}
    void Print() const;
    T Add(T a);
private:
    T data;
};

template <typename T>
void MyContiner<T>::Print() const
{
    cout << "data" << data <<endl;
}

template <typename T>
T MyContiner<T>::Add(T a)
{
    data = data + a;
    return data;
}


// 这就叫做模版特化
template<>
class MyContiner<string>
{
public:
    MyContiner(string inData):data(inData){}
    void Print() const;
    void TT() const;
    string Add(string a);
private:
    string data;
};

inline void MyContiner<string>::Print() const
{
    cout<< "data " <<data << " len " <<data.length()<<endl;
}

inline void MyContiner<string>::TT() const
{
    cout << "TTT" <<endl;
}

inline string MyContiner<string>::Add(string a)
{
    data.append(a);
    return data;
}

class T1
{
public:
    template<typename T>
    static T maxValue(T a, T b){return a >b?a:b;}
};

template<>
inline string T1::maxValue(string a, string b)
{
    return a.length()>b.length()?a:b;
}


template<typename T, size_t N>
class MyArray
{
private:
    T arr[N];
public:
    void SetValue(size_t idx, T value)
    {
        arr[idx] = value;
    }
};