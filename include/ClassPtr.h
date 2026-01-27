#pragma once
#include <string>

using namespace  std;
// 类成员指针
class Person {
    
public:
    std::string name;
    int age;
    Person(string n, int a) : name(n), age(a) {}

    int add(int a, int b) { return a + b; }
    int sub(int a, int b) { return a - b; }
    // const 成员函数
    int mul(int a, int b) const { return a * b; }
    static void Test();
};