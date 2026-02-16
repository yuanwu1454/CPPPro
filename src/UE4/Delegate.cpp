#include "UE4/Delegate.h"
#include <iostream>

#include "Test.h"
#define USE_SELF_TEST

#ifdef USE_SELF_TEST
#include "UE4/SelfTestTemplate.h"
#include "UE4/Stack.h"
#else
#include "UE4/TypeWrapper.h"
#include "UE4/UnrealTypeTraits.h"
#include "UE4/TEnableIfUse.h"
#endif

void Delegate::Test()
{
    {
        std::cout << TIsSame<int,float>::Value <<std::endl;
        std::cout << TIsSame<int,int>::Value <<std::endl;        
    }


    {
        PrintInteger(4);
    }

    {
        TRemoveReference<int>::Type a1 = 4;
        std::cout<< a1<< std::endl;
    }

    {
        A<int> c;
        c.f(9);
    }

    {
        std::cout<< TIsPodType<int>::Value << std::endl;
    }

    {
        std::cout << TAnd<>::Value << std::endl; // 输出 1
        std::cout << TAnd<TrueType, FalseType>::Value << std::endl;
        std::cout << TAnd<TrueType, TrueType>::Value << std::endl;
        std::cout << TAnd<TrueType, TrueType, FalseType, TrueType>::Value << std::endl;
    }

    {
        test<MyClass>(); // 输出 100
    }

    {
        f(1);
        f();
    }

    {
        int x = 10;
        double y = 3.14;
        // 返回值类型是double，符合隐式转换规则
        auto res = generic_max(x, y);
        std::cout << "res = " << res << " value : " << typeid(res).name() << std::endl;
    }

    {
        // 元素类型推导为double（int + float + double的公共类型）
        auto vec = make_vector(1, 2.5f, 3.14);
        for (auto v : vec) {
            std::cout << v << " ";  // 输出：1 2.5 3.14
        }
    }

    {
        // auto p = std::make_pair(a, std::ref(b));  
        // 底层实现等价于：std::pair<std::decay_t<decltype(a)>, std::decay_t<decltype(std::ref(b))>>
    }

    {
        // 1. 显式指定模板参数，声明对象
        ValueWithComment<int> vc1;
        vc1.value = 42;
        vc1.comment = "initial value (int)";
        std::cout << "vc1: " << vc1.value << " - " << vc1.comment << std::endl;

        // 2. 也可以用大括号直接初始化（聚合类特性）
        ValueWithComment<double> vc2{3.14, "pi (double)"};
        std::cout << "vc2: " << vc2.value << " - " << vc2.comment << std::endl;
    }
}
