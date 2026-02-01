#pragma once
#include <string>

using namespace  std;
// 类成员指针
class Person {
    
public:
    std::string name;
    int age;
    Person(string n, int a) : name(n), age(a)
    {
        namePtr = &Person::name;
        agePtr = &Person::age;
    }
    string Person::*namePtr = nullptr;
    int Person::*agePtr = nullptr;

    int add(int a, int b) { return a + b; }
    int sub(int a, int b) { return a - b; }
    // const 成员函数
    int mul(int a, int b) { return a * b; }
    static void Test();
    static string Person::*staticNamePtr;
    static int Person::*staticAgePtr;
    static int sv;
};