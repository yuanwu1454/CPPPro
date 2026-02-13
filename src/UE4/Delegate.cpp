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
}
