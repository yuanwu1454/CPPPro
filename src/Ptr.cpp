#include "Ptr.h"
#include "ClassA.h"
#include<iostream>
#include <cstdlib>
using namespace std;

extern int global_num;

namespace A2 {

    int p = 4;
}
namespace MyNS {
    int k;
}

void Ptr::AddressTest1()
{
    {
        int a = 10;
        int* p = &a;
        int** pp = &p;

        // a = 10
        cout << "a = " << a << endl;
        // *p = 10
        cout << "*p = " << *p << endl;
        // **pp = 10
        cout << "**pp = " << **pp << endl;
        // 打印p指针的地址 也就是 printf("p = %p", p)
        cout << "p = " << (void*)p << endl;
        // 打印p指针的地址 也就是 printf("&a = %p", p)
        cout << "&a = " << (void*)&a << endl;
        // 打印pp指针的地址 也就是 printf("pp = %p", pp)
        cout << "pp = " << (void*)pp << endl;
        // 打印pp指针的地址 也就是 printf("&p = %p", pp)
        cout << "&p = " << (void*)&p << endl;

        *p = 20;
        cout << "修改后 a = " << a << endl;

        **pp = 30;
        cout << "再次修改后 a = " << a << endl;
    }

    {
        int arr[5] = { 1,2,3,4,5 };
        int* p = arr;
        int(*p2)[5] = &arr;

        cout << *p << endl;       // 输出1
        cout << *(p + 2) << endl;   // 输出3
        cout << p[3] << endl;     // 输出4
        cout << &arr[0] << endl;  // 输出p printf("%p", p)
        cout << arr << endl;      // 输出p printf("%p", p)
        cout << &arr << endl;     // 输出？printf("%p", &p)
        cout << *(arr) << endl;      // 输出p printf("%p", p)
        cout << *(arr+1) << endl;      // 输出p printf("%p", p)
        cout << *(&arr+1) << endl;     // 输出？printf("%p", &p)

    }

    {
        cout << "----------------------------------------" << endl;
        int arr[5] = { 1,2,3,4,5 };
        int* p1 = arr;          // 类型：int*，指向首元素
        cout << "p1 = " << (void*)p1 << endl;
        cout << "*p1 = " << *p1 << endl;
        int(*p2)[5] = &arr;    // 类型：int (*)[5]，指向整个数组

        // 打印地址值（初始相同）
        cout << "arr = " << (void*)arr << endl;
        cout << "&arr = " << (void*)&arr << endl;

        // 打印+1后的地址（体现类型差异）
        cout << "arr+1 = " << (void*)(arr + 1) << endl;  // 偏移4字节（1个int）
        cout << "&arr+1 = " << (void*)(&arr + 1) << endl;// 偏移20字节（5个int）
    }

    {
        int arr[2][3] = { {1,2,3}, {4,5,6} };
        int(*p)[2][3] = &arr;
        int(*p2)[3] = arr;
        int* p1 = arr[0];
        int* p3 = &arr[0][0];
    }
    {
        //const int* p; 值不变
        //int const * p; 值不变
        //int* const p; 指针不变
        //const int* const p; 值不变 指针也不变
    }
}

void Ptr::PrintAddress(const int& v)
{
    printf("%d\n", v);
    printf("%p\n", &v);
    cout << (void*)v << endl;
    cout << (void*)(&v) << endl;
}

void Ptr::Func()
{
    PrintAddress(global_num);
}


void Ptr::NewFunc() {

    {
        int* p1 = new int;
        delete p1;
    }

    {
        int* p2 = new int(10);
        delete p2;
    }

    {
        int* p3 = new int[5];
        delete[] p3;
    }

    {
        int(* p4) = new int[5];
        delete[] p4;
    }

    {
        int(*p)[6] = new int[5][6];
        delete[] p;
    }

    {
        int(*p)[6][7] = new int[5][6][7];
        delete[] p;
    }

    //{
    //    int** p = new int* [5];
    //    for (int i = 0; i < 5; i++) {
    //        p[i] = new int[5];
    //    }

    //    //delete[] p; // error
    //    for (int i = 0; i < 5; i++) {
    //        delete[] p[i];
    //    }
    //    delete[] p;
    //}

    {
        int var = 5;
        int var2 = 10;
        const int var3 = 8;
        // int* cp = &var3; error 无法直接指向常量
        // *cp = 10;

        // 指向常量的指针
        const int* p = &var;
        p = &var2;
        cout << var << endl;
        cout << *p << endl;
        //const int* const p2 = &var;
        int* const p2 = &var;
        *p2 = 10;
        cout << var << endl;
    }
    {
        // 错误示例1：多维数组的错误申请/释放
        int** p = new int* [5]; // 先申请5个指针
        for (int i = 0; i < 5; i++) {
            p[i] = new int[5]; // 每个指针指向5个int
        }
        //delete[] p; // 仅释放了外层的指针数组，内层的5个数组内存泄漏！
        // 正确释放方式：先释放内层，再释放外层
        for (int i = 0; i < 5; i++) {
            delete[] p[i];
        }
        delete[] p;
    }

    {
        void* memory = malloc(4);
        if (!memory) {
            printf("内存分配失败\n");
        } else{
            int* p = new(memory)int(5);
            cout << *p << endl;
            free(memory);
        }
    }




    //int* p = new int;
    //int* p2 = new int(10);
    //cout << (void*)p << endl;
    //cout << (void*)p2 << endl;
    //cout << *p2 << endl;
    //cout << *p << endl;
    //*p = 5;
    //cout << *p << endl;
    //delete p;
    //delete p2;

    //int* arr = new int[5];
    //for (int i = 0; i < 5; i++) {
    //    *(arr + i) = i;
    //}
    //for (int i = 0; i < 5; i++) {
    //    cout << *(arr + i) <<  endl;
    //}

    //delete[] arr;

     // 1. 先用 malloc 分配一块原始内存（堆上）
    printf("size:%d\n", sizeof(ClassA));
    void* rawMem = malloc(sizeof(ClassA));
    if (rawMem == nullptr) {
        cerr << "内存分配失败" << endl;
    }
    else {
        ClassA* aPtr = new (rawMem) ClassA(10, "this is 10");
        aPtr->~ClassA();
        free(rawMem);
    }
}

void Ptr::CharTest()
{
    char* ptr = nullptr;
    const char* ptrs = "zxcvxzcv";
    int len = strlen(ptrs);
    ptr = new char[len + 1];
    strcpy_s(ptr, len + 1, ptrs);
    cout << ptr << endl;
    delete[] ptr;
}
