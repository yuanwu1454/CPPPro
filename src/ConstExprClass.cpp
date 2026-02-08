#include "ConstExprClass.h"
#include <iostream>
#include <vector>
using namespace  std;


// 三、constexpr 的优势
// 性能提升：编译期计算完成，运行期无需再计算，减少运行时开销；
// 类型安全：编译器会检查值是否能在编译期确定，提前发现错误；
// 支持编译期分支：结合 if constexpr（C++17），可以实现编译期条件判断，进一步优化代码。

// C++11 风格：仅一条 return 语句
constexpr int square(int x) {
    return x * x;
}

// C++14 风格：支持循环和分支
constexpr int factorial(int n) {
    if (n <= 1) return 1;
    int res = 1;
    for (int i = 2; i <= n; ++i) {
        res *= i;
    }
    return res;
}

class Point {
public:
    // constexpr 构造函数：必须初始化所有成员，且函数体为空（C++11）
    constexpr Point(int x_, int y_) : x(x_), y(y_) {}
    
    // constexpr 成员函数：获取编译期计算的成员值
    constexpr int get_x() const { return x; }
    constexpr int get_y() const { return y; }
    
private:
    int x, y;
};


// 定义一个 constexpr 函数
constexpr static int add(int a, int b) {
    return a + b;
}

void ConstExprClass::Test()
{
    {
        // 1. 定义编译期常量（变量）
        // 正确：编译期就能确定值
        constexpr int max_num = 100;
        // 正确：编译期可计算（3+5=8）
        constexpr int sum = 3 + 5;
        const int sum2 = 3+5;

        // 对比 const：const 可以运行期初始化
        int a = 20;
        const int b = a; // 合法（b 只读，但值在运行期确定）
    
        cout << "max_num: " << max_num << endl;
        cout << "sum: " << sum << endl;
        cout << "b: " << b << endl;
        
    }

    {
        // 2. 定义编译期函数
        cout << "f :" << factorial(5)<<endl;
        int arr[factorial(4)];
        int a = 3;
    }

    {
        //3. 修饰类 / 构造函数（C++11 起）
        // 编译期创建 Point 对象
        constexpr Point p(3, 4);
        // 编译期获取成员值
        constexpr int x = p.get_x();  // x = 3
        constexpr int y = p.get_y();  // y = 4
    }

    
    // 如何区分一个 constexpr 变量 / 函数的结果是编译期计算的，还是运行期计算的
    {
        // 场景 1：编译期计算（合法）
        constexpr int compile_val = add(2, 3); // 编译期确定值=5
        int arr[compile_val]; // 数组大小必须编译期确定，合法
    
        // 场景 2：运行期计算（若强行用于编译期场景会报错）
        int a = 2, b = 3;
        int runtime_val = add(a, b); // 运行期计算（参数是运行期变量）
        // int arr2[runtime_val]; // 编译报错！runtime_val 是运行期值，无法确定数组大小
    
        cout << "compile_val " << compile_val << endl;
        cout << "runtime_val " << runtime_val << endl;
    }

    {
        // 验证 1：编译期计算（static_assert 合法）
        constexpr int c_val = add(2, 3);
        static_assert(c_val == 5, "编译期计算错误"); // 编译通过，说明是编译期值
    
        // 验证 2：运行期计算（static_assert 报错）
        int a = 2, b = 3;
        int r_val = add(a, b);
        // static_assert(r_val == 5, "运行期计算错误"); // 编译报错！r_val 不是编译期常量
    }
}
