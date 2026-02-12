#include <iostream>

#include "AutoClassTest.h"
#include "Ptr.h"
#include "ClassA.h"
#include "ClassPtr.h"
#include "MyNs.h"
#include "ConstCastTest.h"
#include "ConstExprClass.h"
#include "Decltype.h"
#include "StaticCast.h"
#include "ReinterpretCast.h"
#include "TemplateTest.h"
#include "Test.h"
#include "FuncPtrTest.h"
#include "LamdaTest.h"
#include "UnionTest.h"
#include "MutableClass.h"
#include "VarTest.h"
#include "UE4/Delegate.h"
using namespace std;

// ctor，destructor,copy ctor,move ctor, copy assign, move assign 
// static_cast, dynamic_cast, const_cast, reinterpret_cast
// shared,unique,weak,auto
// new,delete, malloc, free
// virtual,override, volatile, using,final
// namespace, class, struct
// volatile, const, restrict, mutable, static, register【基本弃用】, thread_local 
// 内存大小与对齐
// auto,decltype,nullptr,initialize_list,tuple
// enum, union
// using,typedef
// #define, const
// string,vector,array,pair,map,set
// lvalues, rvalues
// template
// func ptr,using,typedef
// protected inheritance， private inheritance【composition 备选项】
// callbackstd::function + std::bind 或 lambda
// operator()
// constexpr, iterator,const_iterator
void AddressTest();
void ClassTest();
void ExeFunc(void* func);

int global_num = 10;
int global_num2 = 100;
extern int a;
//static 关键字 
int main()
{

    // ConstCastTest::Test();
    // StaticCast::Test();
    // ReinterpretCast::Test();
    // TemplateTest::Test();
    // Person::Test();
    // FuncPtrTest::Test();
    // LamdaTest::Test();
    // UnionTest::Test();
    // MutableClass::Test();
    // AutoClassTest::Test();
    // Decltype::Test();
    // ConstExprClass::Test();
    // VarTest::Test();
    Delegate::Test();
    // cout << my_namespace::a<<endl;
    // cout << A2::k << endl;
    // cout << A2::v << endl;
    // cout << A2::p << endl;
    //
    // MyNS::func();
    // cout << MyNS::svar << endl;
    // cout << MyNS::k << endl;
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
    // PrintInteger(5);
    
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

}

  