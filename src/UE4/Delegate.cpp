#include "UE4/Delegate.h"

#include "UE4/TypeWrapper.h"
#include "UE4/UnrealTypeTraits.h"
#include "UE4/TEnableIfUse.h"

void Delegate::Test()
{
    // TThing<int> TempThing;
    // TempThing.f(3);
    //
    // std::cout << TIsSame<int, float>::Value << std::endl;
    // std::cout << TIsSame<int, int>::Value << std::endl;
    // X<int,int> x;
    // x.c = 3;

    int32 Num = 123;
    
    PrintValue(Num); // 输出：非指针值：123
    
    PrintValue(&Num); // 输出：指针值：0x...，指向的内容：123
    
    int32* NullPtr = nullptr;
    PrintValue(NullPtr); // 输出：空指针
}
