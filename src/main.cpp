#include <iostream>
#include "Ptr.h"
#include "ClassA.h"
#include "MyNs.h"
using namespace std;
// 构造函数
// 拷贝构造函数
// 默认拷贝构造函数的缺点
// 移动构造函数
// 非 const 版本拷贝构造函数
// noexcept 的作用


void AddressTest();
void ClassTest();
void ExeFunc(void* func);

int global_num = 10;
int global_num2 = 100;
class Base {
public:
    Base() { cout << "Base 构造函数" << endl; }
    ~Base() { cout << "Base 析构函数" << endl; }
};

class Derived : public Base {
public:
    Derived() {
        cout << "Derived 构造函数" << endl; 
    }
    ~Derived() { 
        cout << "Derived 析构函数" << endl; 
    }
};

class DDerived : public Derived {
public:
    DDerived() {
        cout << "DDerived 构造函数" << endl;
    }
    ~DDerived() {
        cout << "DDerived 析构函数" << endl;
    }
};
namespace A2 {
    extern int v;
    extern int p;
    int k = 4;
}

extern int a;
//static 关键字 
int main()
{

    cout << A2::k << endl;
    cout << A2::v << endl;
    cout << A2::p << endl;

    MyNS::func();
    cout << MyNS::svar << endl;
    cout << MyNS::k << endl;
    //DDerived* p = new DDerived();
    //Base* p = new DDerived();
    //shared_ptr<Base> p2(p);
    //shared_ptr<Base> p = make_shared<DDerived>();

    //Base* p = new Derived();
    //delete p;
    //Ptr::PrintAddress(global_num);
    //Ptr::PrintAddress(global_num2);
    //Ptr::Func();
    //Ptr::NewFunc();

    //Ptr::AddressTest1();
    //AddressTest();
    return 0;
}

void AddressTest() {
    int v = 10;
    int* p = &v;
    printf("ptr address is %p\n", p);
    printf("ptr address is %p\n", &p);
    printf("ptr address is %p\n", (void*)v);
}

void ClassTest() {
    // 构造函数
    ClassA a(10, "zxcvzxcv");

    // 拷贝构造函数
    ClassA b = a;

    // 先普通构造函数
    ClassA c(10, "zxcvzxcv");
    // 赋值运算符重载调用
    c = c;


    printf("\n\n开始测试移动构造函数\n\n");
    ClassA d(45, "qwerqwer");
    // 移动构造函数
    ClassA e = std::move(d);

}

  