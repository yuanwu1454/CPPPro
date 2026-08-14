#include <iostream>
#include <stdlib.h>
#include <Date.h>
using namespace std;

// Date 重载 cout 重载 cin，构造函数，析构函数
// Complex 复数 重载
// 分数 / 有理数 Fraction：f1 * f2
// 向量、矩阵：vec1 + vec2、mat1 * mat2
// 坐标、点、尺寸类
// 排序重载 <
// 一元负号 -obj（取负） 复数，分数，向量
int main()
{
    // 测试1：1993‑10‑01 +80天
    Date d1(1993, 10, 1);
    Date d2 = d1 + 80;
    std::cout << d1 << " + 80d = " << d2 << "\n";

    // 测试2：日期减去天数
    Date d3 = d2 - 80;
    std::cout << d2 << " - 80d = " << d3 << "\n";

    // 测试3：两个日期相减，得到间隔天数
    Date a(2026, 8, 1);
    Date b(2026, 8, 14);
    long long diff = b - a;
    std::cout << b << " - " << a << " = " << diff << " d\n";

    // 测试 -=
    Date d4(2000, 1, 5);
    d4 -= 10;
    std::cout << "2000/01/05 -10d:" << d4 << "\n";
    
    return 0;
}
