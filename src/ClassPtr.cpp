#include "ClassPtr.h"
#include <iostream>
using namespace std;
// std::function + std::bind 或 lambda 表达式可以更优雅地处理类成员回调，但底层依然依赖成员函数指针的逻辑，在一些老旧项目或高性能场景中，仍会直接使用成员函数指针

// 类成员指针的用法：
// 1. 动态选择访问类的不同成员变量
using Callback = int(Person::*)(int, int);

// 2. 通用打印工具函数：打印任意类对象的任意成员变量
template <typename ClassType, typename MemType>
void printClassMember(const ClassType& obj, MemType ClassType::*memPtr, const string& memName) {
    cout << memName << "：" << obj.*memPtr << endl;
}

// 3. 实现「回调函数」（尤其是类成员函数作为回调）


void PrintPersonInfo(Person& person, Callback ptr, int a, int b)
{

    cout << person.age<<endl;
    cout << (person.*ptr)(a, b) << endl;
}
//
// void PrintPersonInfo(const Person* person, Callback ptr, int a, int b)
// {
//     
//     cout << (person->*ptr)(a, b) << endl;
// }

void Person::Test()
{
    // 1. 定义指向 Person 类的 int 成员变量的指针（类成员指针）
    int Person::*p_age = &Person::age; // 指向 Person::age
    // 2. 定义指向 Person 类的 string 成员变量的指针
    string Person::*p_name = &Person::name; // 指向 Person::name

    // 1. 定义指向 Person 类的成员函数的指针
    // 语法：返回值 (类名::*指针名)(参数列表) = &类名::函数名;
    int (Person::*p_add)(int, int) = &Person::add;
    int (Person::*p_sub)(int, int) = &Person::sub;
    // const 成员函数指针需要匹配 const 限定
    int (Person::*p_mul)(int, int) = &Person::mul;


    
    {
 
        // 3. 创建类的对象
        Person p1("AAA", 20);
        Person p2("BBB", 25);

        // 4. 通过类成员指针访问对象的成员（必须绑定对象）
        // 语法：对象.*类成员指针  或  对象指针->*类成员指针
        cout << p1.*p_age << endl; // 输出 20
        cout << "p2's name" << p2.*p_name << endl; // 输出 李四

        Person* p_ptr = &p1;
        cout << "p1's name" << p_ptr->*p_name << endl; // 输出 张三

        // 2. 创建对象，调用成员函数
        // 语法：(对象.*指针)(参数)  或  (对象指针->*指针)(参数)
        cout << "3+5=" << (p1.*p_add)(3, 5) << endl; // 输出 8
        cout << "8-2=" << (p1.*p_sub)(8, 2) << endl; // 输出 6
        cout << "4*6=" << (p1.*p_mul)(4, 6) << endl; // 输出 24
    }

    {
        Person p1("AAA", 20);
        // 常量对象（或常量对象引用）只能访问 const 修饰的成员变量和 const 修饰的成员函数，
        PrintPersonInfo(p1, p_mul, 4,6);
        PrintPersonInfo(p1, p_sub, 4,6);
        PrintPersonInfo(p1, p_add, 4,6);
        
        printClassMember(p1, &Person::name, "姓名");
        printClassMember(p1, &Person::age, "年龄");

    }
}
