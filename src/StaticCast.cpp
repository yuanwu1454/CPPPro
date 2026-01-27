#include "StaticCast.h"
#include "Common.h"
enum class Fruit
{
    Apple = 3,
    Banana
};


class NoVirtual
{
    
public:

    // 基类
    class Base {};
    // 子类
    class Derived : public Base {};
};

class Virtual
{
public:

    // 基类（必须有虚函数，否则无法使用dynamic_cast）
    class Base {
    public:
        virtual void show() { cout << "Base class" << endl; }
    };

    // 子类1
    class Derived1 : public Base {
    public:
        void show() override { cout << "Derived1 class" << endl; }
        void func1() { cout << "Derived1 unique function" << endl; }
    };

    // 子类2
    class Derived2 : public Base {
    public:
        void show() override { cout << "Derived2 class" << endl; }
    };
};


void StaticCast::Test()
{
    cout << "StaticCast Begin" <<endl;
    // static_cast 提前拦截， 不是可有可无
    // 1. 第一层：显式标注，提升可读性（你感知到的 “强化展示”）
    // 2. 第二层：编译期检查，拦截非法转换（核心价值）
    // 3. 第三层：标准化转换行为，适配 C++ 的类型系统
    {
        int a = 1;
        float v = static_cast<float>(a);
        int c = static_cast<int>(Fruit::Apple);
        cout << "v:" << v <<endl;
        cout << "c:" << c <<endl;
    }

    {
        int s = 4;
        // 生成了一个新的变量  地址与s 不一样
        const int p = static_cast<const int>(s);
        // p = 6; 无法赋值

        cout << (void*)(&s) << endl;
        cout << (void*)(&p) << endl;        
    }

    {
        
        const int a = 10;
        // warnning
        // int* p = (int*)&a; // C风格转换：能强制去掉const，编译通过（但运行时修改会UB）
        // error
        // int* p2 = static_cast<int*>(&a); // 编译直接报错！static_cast 拒绝const→非const
        // （去掉const需要用 const_cast，这是C++的明确约束）
    }

    {
        // 基类指针 指向子类指针
        // 不需要多态
        NoVirtual::Derived d;
        NoVirtual::Derived* dptr = &d;
        NoVirtual::Base* bp1 = static_cast<NoVirtual::Base*>(dptr);
        NoVirtual::Base* bp2 = static_cast<NoVirtual::Base*>(&d);
    }

    {
        // 可以将void* 转化成任意 指针
        void* void_ptr = nullptr;
        int* int_ptr = static_cast<int*>(void_ptr);
        char* char_ptr = static_cast<char*>(void_ptr);
    }

    {
        // dynamic_cast 继承体系
        // 运行时转化
        // 可转化 指针和引用 但是无法转化 值类型
        // 必须有虚函数的类， 可检测，
        // 向下转型(父类->子类，兄弟类)

        // 场景1：合法的向下转型（父类指针实际指向子类）
        Virtual::Base* b1 = new Virtual::Derived1();
        Virtual::Derived1* d1 = dynamic_cast<Virtual::Derived1*>(b1);
        if (d1 != nullptr) { // 转换成功，指针非空
            d1->func1(); // 安全调用子类独有的函数
        }

        // 场景2：非法的向下转型（父类指针指向父类本身）
        Virtual::Base* b2 = new Virtual::Base();
        Virtual::Derived1* d2 = dynamic_cast<Virtual::Derived1*>(b2);
        if (d2 == nullptr) { // 转换失败，指针为空
            cout << "dynamic_cast error" << endl;
        }

        // 场景3：交叉转型（兄弟类之间）
        Virtual::Base* b3 = new Virtual::Derived1();
        Virtual::Derived2* d3 = dynamic_cast<Virtual::Derived2*>(b3);
        if (d3 == nullptr) {
            cout << "error" << endl;
        }

        // 释放内存
        delete b1;
        delete b2;
        delete b3;
    }
    {
        // 场景1：合法的引用转换（基类引用实际绑定子类对象）
        Virtual::Derived1 d;
        Virtual::Base& b_ref = d; // 基类引用绑定子类对象
        try {
            Virtual::Derived1& d_ref = dynamic_cast<Virtual::Derived1&>(b_ref); // 转换成功
            d_ref.show(); // 安全调用子类独有函数
        } catch (const bad_cast& e) {
            cout << "convert err " << e.what() <<endl;
        }

        // 场景2：非法的引用转换（基类引用绑定基类对象）
        Virtual::Base b;
        Virtual::Base& b_ref2 = b;
        try {
            Virtual::Derived1& d_ref2 = dynamic_cast<Virtual::Derived1&>(b_ref2); // 转换失败，抛异常
            d_ref2.show();
        } catch (const bad_cast& e) {
            cout << "convert err " << e.what() <<endl;
        }
    }

}
