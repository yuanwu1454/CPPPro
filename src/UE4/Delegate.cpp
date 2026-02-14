#include "UE4/Delegate.h"
#include <iostream>

#include "Test.h"
#define USE_SELF_TEST

#ifdef USE_SELF_TEST
#include "UE4/SelfTestTemplate.h"
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
        // 测试1：空参数 → true
        std::cout << TAnd<>::Value << std::endl; // 输出 1
        std::cout << TAnd<TrueType, FalseType>::Value << std::endl;
        std::cout << TAnd<TrueType, TrueType>::Value << std::endl;
        std::cout << TAnd<TrueType, TrueType, FalseType, TrueType>::Value << std::endl;
    }

    {
        test<MyClass>(); // 输出 100
    }
}
