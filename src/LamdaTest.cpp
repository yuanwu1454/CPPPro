#include "LamdaTest.h"
#include <iostream>
#include <functional>
using namespace std;
using namespace std::placeholders;
// 仿函数（重载 operator()）
class MulFunctor {
public:
    int operator()(int x, int y) const {
        return x * y;
    }
    int kk(int x, int y)
    {
        return x*y;
    }
};

int add_func(int x, int y)
{
    return x+y;
}

// 传常量引用，本身不能修改外部引用的值
void execute(const function<int(int,int)>& f)
{
    cout << f(3,4) <<endl;
}


// 传引用 会修改外部
void execute(function<int(int,int)>& f)
{
    cout << f(3,4) <<endl;
}

// 传值 本身会拷贝一份
// void execute(function<int(int,int)> f)
// {
//     cout << f(3,4) <<endl;
// }

// lamda
// Lambda 表达式本质是一个匿名的仿函数（编译器会为其生成一个匿名类，并重载 operator()）。
// 按值捕获的变量，Lambda 内部持有副本，默认不可修改（mutable 仅修改副本）；按引用捕获的变量，修改会影响外部原变量（需注意变量生命周期，避免悬垂引用）。
// 当 Lambda 没有捕获任何外部变量（[]）时，可以隐式转换为对应的函数指针；一旦捕获了变量，就无法转换为函数指针（此时需要用 std::function 包装）。

// std::function
// 类型安全：相比函数指针，std::function 提供了更强的类型检查，编译期就能发现函数签名不匹配的错误。
// 通用性：可以包装几乎所有可调用对象，包括捕获了变量的 Lambda（这是函数指针做不到的）。
// 可空性：默认构造的 std::function 是空的，调用空的 std::function 会抛出 std::bad_function_call 异常，可通过 !func 判断是否有效。
// 有轻微性能开销：因为是包装器，内部有间接调用，性能略低于直接调用原始可调用对象（绝大多数场景下可忽略）。


// std::bind 返回的是一个未指定类型的可调用对象（编译器生成的匿名类型），通常用 auto 接收，或用 std::function 包装（方便作为参数传递、存储）。
// 占位符的编号对应 “新可调用对象” 的参数顺序，与原函数的参数顺序无关，可用于调整参数顺序。
// 绑定类成员函数时，必须传递类的实例（或指针），因为类成员函数的第一个隐含参数是 this 指针。
// C++14 及以后，很多 std::bind 的场景可以被带捕获的 Lambda 表达式替代，Lambda 更直观、可读性更强，因此 std::bind 的使用场景有所减少，但在一些需要动态绑定参数的场景下仍有用处。


// 普通函数：计算 x + y + z
int sum_3(int x, int y, int z) {
    return x + y + z;
}

class MyClass {

public:
    MyClass(int inNum):num(inNum){}
    int multiply(int a, int b) {
        return a * b * num;
    }
    void setNum(int inNum){num = inNum;}
    int getNum(){return num;}
    void kk()const{};
private:
    int num;
};

void LamdaTest::Test()
{
    int a = 3;
    int b = 5;
    auto add = [=](int c) { return a+b+c;};
    cout << add(4) <<endl;
    auto addref = [&](int c){return a+b+c;};
    cout << addref(4) <<endl;
    std::function<int(int)> addFunc = add;
    cout << MulFunctor()(5,6)<<endl;
    // normal function
    function<int(int,int)> f = add_func;
    // 仿函数
    function<int(int,int)> f2 = MulFunctor();
    // 仿函数
    function<int(int,int)> f3 = [](int a,int b)
    {
        return  a+b;
    };

    cout << f3(6,7) << endl;
    
    execute(f);
    MulFunctor mf;
    cout << mf(4,5) <<endl;

    auto sum2 = bind(sum_3,_1,_2,100);
    cout << sum2(4,6) <<endl;


    std::function<int(int)> func = std::bind(sum_3, _1, 50, 50);
    std::cout << "Func sum " << func(100) << std::endl; // 输出：Func sum: 200

    MyClass obj(20);
    // auto mulobj = bind(&MyClass::multiply, &obj, 10, _1);
    // cout <<"xzcv" << mulobj(3,6,7,8) << endl;

    auto changeMyClass =[obj](int val) mutable
    {
        obj.setNum(val);
        cout << obj.getNum() <<endl;
    };
    changeMyClass(30);
    cout << obj.getNum() <<endl;
    
}
