#include "MutableClass.h"
#include <iostream>
#include <mutex>
#include <string>
using namespace std;

// mutable 作用
// 直接作用：
// 1. const成员函数中，直接修改mutable成员变量
// 2. lamda函数中 使用mutable，可以修改值传递的副本
// mutable 不影响 非const成员函数


// 核心使用场景
// 场景 1：统计类成员函数的调用次数（如上面的例子）
// 这类计数器只是辅助信息，修改它不会改变对象的核心功能和核心数据，适合用 mutable 修饰。

// 场景 2：实现 “惰性求值 / 缓存”（最常用、最实用）
// 有些类的成员函数需要计算一个复杂结果，每次调用都计算会消耗大量性能。此时可以把计算结果缓存起来，下次调用直接返回缓存值，只有当缓存无效时才重新计算。
// 这个缓存变量就是辅助性的，适合用 mutable 修饰（即使在 const 函数中，也能更新缓存）。

// 场景 3：用于类内部的锁机制（多线程场景）
// 在多线程编程中，类的 const 成员函数也可能需要加锁来保证线程安全，此时锁对象需要被修改（调用 lock()、unlock()），因此锁对象必须用 mutable 修饰。

// mutable 的存在，本质上是为了解决 “const 关键字的语法严格性” 与 “实际业务逻辑的灵活性” 之间的矛盾，

class Person
{
private:
    string name;
    mutable int m_call_count=0;

    double m_radius; // 核心数据：半径（不允许 const 函数修改）
    mutable double m_cached_area; // 缓存的面积（辅助数据，mutable 修饰）
    mutable bool m_area_valid; // 缓存是否有效（辅助状态，mutable 修饰）

public:
    Person(string inName, double inRadius):name(inName),m_radius(inRadius)
    {
        m_area_valid = false;
    };
    string getName() const
    {
        m_call_count++;
        return name;
    }
    // 修改半径（非 const 函数，会让缓存失效）
    void setRadius(double radius) {
        m_radius = radius;
        m_area_valid = false; // 半径改变，缓存的面积无效了
    }

    double getArea() const
    {
        if (!m_area_valid)
        {
            m_cached_area = m_radius*m_radius;
            m_area_valid =true;
        }
        return m_cached_area;
    }
    
    int getCount(){return m_call_count;}
};

class SafeData
{
private:
    int m_data;
    mutable mutex m_mutex;
public:
    SafeData(int data):m_data(data){}
    int getData() const{
        lock_guard<mutex> lock(m_mutex);
        return m_data;
    }
    void setData(int data){
        lock_guard<mutex> lock(m_mutex);
        m_data = data;
    }
};

void MutableClass::Test()
{
    Person p("Bob",9);
    cout << p.getName() <<endl;
    cout << p.getCount() <<endl;
    cout << p.getArea() <<endl;
    cout << p.getArea() <<endl;

    int count = 1;
    auto f = [count]() mutable 
    {
        count++;
        cout << count<<endl;
    };
    f();
    
}
