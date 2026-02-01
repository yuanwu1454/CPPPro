#include "ClassPtr.h"
#include <iostream>
using namespace std;


// 类成员指针的用法：
// 1. 动态选择访问类的不同成员变量
using Callback = int(Person::*)(int, int);

// 2. 通用打印工具函数：打印任意类对象的任意成员变量
template <typename ClassType, typename MemType>
void printClassMember(const ClassType& obj, MemType ClassType::*memPtr, const string& memName) {
    cout << memName <<  " : " << obj.*memPtr << endl;
}

// 3. 实现「回调函数」（尤其是类成员函数作为回调）

void PrintPersonInfo(Person& person, Callback ptr, int a, int b)
{
    cout << person.age<<endl;
    cout << (person.*ptr)(a, b) << endl;
}


// string Person::*staticNamePtr = &Person::name;
// int Person::*staticAgePtr = &Person::age;

string Person::*Person::staticNamePtr = &Person::name;
int Person::*Person::staticAgePtr = &Person::age;
int Person::sv = 7;

int xadd(int a, int b)
{
    int sum = a+b;
    cout<< sum <<endl;
    return a+b;
}

typedef  int (*pAddPtr)(int, int);
using AddFunc = int (*)(int, int);


void Person::Test()
{
    string Person::*ptr = &Person::name;
    // ::* 不是一个整体运算符号，作用域解析 和指针声明的两个书写
    Person p1("Bob", 10);
    // .* 是一个整体运算符
    cout << p1.*ptr <<endl;

    Person* cptr = &p1;
    // ->* 是一个整体运算肤
    cout << cptr->*ptr <<endl;

    cout << p1.*(Person::staticNamePtr) <<endl;

    auto ptr3 = &Person::name;
    cout << p1.*ptr3 <<endl;

    int (*pAdd)(int, int) = &xadd;
     pAdd(5,7);

    {
        int(Person::*addPtr)(int,int) = &add;
        int(Person::*subPtr)(int,int) = &sub;
        int(Person::*mulPtr)(int,int) = &mul;
        // p1.*addPtr(5,6) error
        cout << (p1.*addPtr)(5,6)<<endl;
        cout << (p1.*mulPtr)(5,6)<<endl;
        cout << (p1.*subPtr)(5,6)<<endl;
    }
    {

        
        // 1. 定义指向 Person 类的成员函数的指针
        // 语法：返回值 (类名::*指针名)(参数列表) = &类名::函数名;
        int (Person::*p_add)(int, int) = &Person::add;
        int (Person::*p_sub)(int, int) = &Person::sub;
        // const 成员函数指针需要匹配 const 限定
        int (Person::*p_mul)(int, int) = &Person::mul;

        
        Person p1("AAA", 20);
        // 常量对象（或常量对象引用）只能访问 const 修饰的成员变量和 const 修饰的成员函数，
        PrintPersonInfo(p1, p_mul, 4,6);
        PrintPersonInfo(p1, p_sub, 4,6);
        PrintPersonInfo(p1, p_add, 4,6);
        
        printClassMember(p1, &Person::name, "姓名");
        printClassMember(p1, &Person::age, "年龄");

    }
    
}
