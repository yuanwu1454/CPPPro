#include "UnionTest.h"
#include <iostream>
using namespace std;
// union
// union 的整体大小不是所有成员大小之和，而是其最大成员的大小
// union 是一种用户自定义数据类型，它的所有成员共享同一块连续的内存空间，而非像 struct 那样各成员拥有独立内存。
union MyUnion
{
    // 4字节
    int i;
    // 8字节
    double d;
    // 1字节
    char c;
};

struct MyStruct {
    char c;    // 对齐值1，占用1字节
    int i;     // 对齐值4，需要填充3个空字节，才能让起始地址是4的整数倍
    double d;  // 对齐值8，起始地址已是8的整数倍，占用8字节
};


// 内存对齐：
// 目的： 提高 CPU 访问内存的效率
// 内置类型的对齐值：通常等于其自身大小（如 char=1，int=4，double=8，32/64 位系统略有差异，可通过 alignof() 函数获取准确值）。
// 自定义类型（struct/union）的对齐值：等于其所有成员中最大的对齐值。
// 对齐规则：
// 每个成员的起始地址，必须是[该成员对齐值]的整数倍
// 整个自定义类型的总大小，必须是该类型对齐值的整数倍（不足则在末尾填充）。

// 指针大小
// 32位 4字节 64位 8字节
// 指针对齐值
// 32位 4字节 64位 8字节


// 自定义类型：大小5字节，对齐值8
struct alignas(8) MyType {
    char data[5];
};

struct MyType2 {
    char data[5];
};

// 定义 union
union MyUnion2 {
    MyType t;  // 大小5，对齐值8（最大，决定union对齐值）
    char c;    // 大小1，对齐值1
};


#pragma pack(4) // 强制最大对齐值为4
struct PackedStruct {
    char c;
    int* p; // 指针大小仍为8，对齐值被限制为4
};


// 提高 CPU 访问内存的效率
void UnionTest::Test()
{
    MyUnion u;
    cout << "Myunion size is " << sizeof(u) <<endl;
    cout << "i address is " <<  (void*)&u.i<<endl;
    cout << "d address is " <<  (void*)&u.d<<endl;
    cout << "c address is " <<  static_cast<void*>(&u.c)<<endl;
    
    u.i = 100;
    cout  << u.i << endl;
    cout  << u.d << endl;

    u.d = 3.14159;
    cout << u.d << endl;
    cout << u.i << endl;

    cout << alignof(int) <<endl;
    cout << alignof(double) <<endl;
    cout << alignof(char) <<endl;
    cout << alignof(long long) <<endl;
    cout << alignof(void*) <<endl;
    cout << alignof(int&) <<endl;


    cout << "MyStruct align value is " << alignof(MyStruct) << endl;
    cout << "MyStruct size value is " << sizeof(MyStruct) << endl;
    cout << "MyType align value is " << alignof(MyType) << endl;
    cout << "MyType size value is " << sizeof(MyType) << endl;
    cout << "MyType data size value is " << sizeof(MyType::data) << endl;    
    cout << "MyType2 align value is " << alignof(MyType2) << endl;
    cout << "MyType2 size value is " << sizeof(MyType2) << endl;
    
}
