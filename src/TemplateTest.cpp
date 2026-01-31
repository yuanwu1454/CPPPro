#include "TemplateTest.h"
#include <iostream>
#include "vector"
#include "map"
using namespace std;

template<typename T>
using Vec = vector<T>;

template<typename T>
using StrMap = map<string, T>;

// 模版
// 模版别名，模版函数，模版类，模版成员函数
// 变量模版
// 模版特化，模版参数包
// 模板实例化（Template Instantiation）

// 优化手段：
// 容易造成代码膨胀


// 优点：
// 1. 冗余代码少
// 2. 编译期检查
// 3. 只付出你使用的成本，不付出你不用的成本
// 缺点：
// 1. 调试难
// 2. 学习难度高
// 3. 容易造成代码膨胀
// 4. 编译时间长,影响开发效率
// 
// 场景1：通用常量（不同类型的圆周率）
template <typename T>
const T PI = T(3.14159265358979323846);

// 场景2：通用全局变量（记录不同类型的最大值）
template <typename T>
T GlobalMaxValue = T(0);


void printArgs()
{
    cout << "参数打印完毕" <<endl;
}

// typename... Args 模版参数包
// Args... Rest 函数参数包
// Rest... 参数包展开
// ... 参数包展开运算符

template<typename T, typename ... Args>
void printArgs(const T& First, Args... Rest)
{
    cout << First<< " ";
    printArgs(Rest...);
}


void printContactString(string& str)
{
    str = str+"\n";
}

template<typename T, typename ... Args>
void printContactString(string& str, const T& First, Args... Rest)
{
    str += First;
    printContactString(str, Rest...);
}

void TemplateTest::Test()
{

    // 模版实例化
    cout << maxValue(5,6) <<endl;
    cout << maxValue(3.14, 9.8) <<endl;
    string s1 = "asdf";
    string s2 = "qewrr";
    cout << maxValue(s1, s2) <<endl;

    cout<<T1::maxValue(4,5)<<endl;
    cout<<T1::maxValue(3.14,5.28)<<endl;
    cout<<T1::maxValue(s1,s2)<<endl;
    // inline 内联关键字
    // 函数频繁调用也会有性能开销
    // 短小精悍，且频繁的函数最好用 inline 来声明
    // 函数多重定义 也可以用inline 来解决。允许函数在多个编译单元中存在
    // inline 是否生效由编译期决定
    // 类内定义的成员函数， 默认是inline。

    MyContiner<int> P(10);
    P.Print();
    cout << P.Add(20) <<endl;
    MyContiner<string> S("xzcvxcv");
    S.Print();
    S.TT();
    cout << S.Add("opopo") <<endl;


    Vec<int> intVec = {1,2,3};
    for (int val: intVec)
    {
        cout << val << " ";
    }
    cout << endl;

    // 使用嵌套模板别名
    StrMap<double> scoreMap;
    scoreMap["Player1"] = 95.5;
    scoreMap["Player2"] = 88.0;
    cout << "Player1 " << scoreMap["Player1"] << endl;


    // 使用double类型的PI
    cout << "double  PI" << PI<double> << endl;
    // 使用float类型的PI
    cout << "float  PI" << PI<float> << endl;
    // 使用int类型的PI
    cout << "int PI" << PI<int> << endl;

    // 给int类型的GlobalMaxValue赋值
    GlobalMaxValue<int> = 1000;
    cout << "int" << GlobalMaxValue<int> << endl;

    // 给double类型的GlobalMaxValue赋值
    GlobalMaxValue<double> = 9999.99;
    cout << "double" << GlobalMaxValue<double> << endl;


    printArgs(100, 3.14, "Hello Variadic Template", true);

    string str="";
    printContactString(str, "zxv", "werqwr", "erq");
    cout << str;
    MyArray<int, 10> a;
    a.SetValue(1,4);
}