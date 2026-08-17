#include <iostream>
#include <stdlib.h>
#include <Date.h>

#include "01_basics/Basics.h"
#include "02_classes/Classes.h"
#include "03_containers/Containers.h"
#include "04_algorithms/Algorithms.h"
#include "05_templates/Templates.h"
#include "05_resources/Resources.h"
#include "06_oop/Oop.h"

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
    testBasics();
    testClasses();
    testContainers();
    testAlgorithms();
    testTemplates();
    testResources();
    testOop();

    // 测试 Date：构造、输出、加减法和日期间隔
    Date d1(1993, 10, 1);
    Date d2 = d1 + 80;
    cout << d1 << " + 80d = " << d2 << "\n";

    Date d3 = d2 - 80;
    cout << d2 << " - 80d = " << d3 << "\n";

    Date a(2026, 8, 1);
    Date b(2026, 8, 14);
    cout << b << " - " << a << " = " << b - a << " d\n";

    Date d4(2000, 1, 5);
    d4 -= 10;
    cout << "2000/01/05 -10d: " << d4 << "\n";

    cout << "All C++ Primer study tests passed.\n";
    return 0;
}
