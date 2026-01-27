#include "ClassPtr.h"
#include <iostream>
using namespace std;
void Person::Test(){

    // 1. 定义指向 Person 类的 int 成员变量的指针（类成员指针）
    int Person::*p_age = &Person::age; // 指向 Person::age
    // 2. 定义指向 Person 类的 string 成员变量的指针
    string Person::*p_name = &Person::name; // 指向 Person::name

    // 3. 创建类的对象
    Person p1("AAA", 20);
    Person p2("BBB", 25);

    // 4. 通过类成员指针访问对象的成员（必须绑定对象）
    // 语法：对象.*类成员指针  或  对象指针->*类成员指针
    cout << "p1's name：" << p1.*p_age << endl; // 输出 20
    cout << "p2's name：" << p2.*p_name << endl; // 输出 李四

    Person* p_ptr = &p1;
    cout << "p1's name：" << p_ptr->*p_name << endl; // 输出 张三

   // 1. 定义指向 Person 类的成员函数的指针
    // 语法：返回值 (类名::*指针名)(参数列表) = &类名::函数名;
    int (Person::*p_add)(int, int) = &Person::add;
    int (Person::*p_sub)(int, int) = &Person::sub;
    // const 成员函数指针需要匹配 const 限定
    int (Person::*p_mul)(int, int) const = &Person::mul;

    // 2. 创建对象，调用成员函数
    // 语法：(对象.*指针)(参数)  或  (对象指针->*指针)(参数)
    cout << "3+5=" << (p1.*p_add)(3, 5) << endl; // 输出 8
    cout << "8-2=" << (p1.*p_sub)(8, 2) << endl; // 输出 6
    cout << "4*6=" << (p1.*p_mul)(4, 6) << endl; // 输出 24
}
