#include "UE4/Delegate.h"
#include <iostream>
#include <list>
#include "Test.h"
#define USE_SELF_TEST

#ifdef USE_SELF_TEST
#include "UE4/SelfTestTemplate.h"
#include "UE4/Stack.h"
#include "UE4/Chapter5.h"
#include "Template/declval.h"
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
        // auto vec = make_vector(1, 2.5f, 3.14);
        // for (auto v : vec) {
        //     std::cout << v << " ";  // 输出：1 2.5 3.14
        // }
    }

    {
        // auto p = std::make_pair(a, std::ref(b));  
        // 底层实现等价于：std::pair<std::decay_t<decltype(a)>, std::decay_t<decltype(std::ref(b))>>
    }

    {
        ValueWithComment<int> vc1;
        vc1.value = 42;
        vc1.comment = "initial value (int)";
        std::cout << "vc1: " << vc1.value << " - " << vc1.comment << std::endl;
        
        ValueWithComment<double> vc2{3.14, "pi (double)"};
        std::cout << "vc2: " << vc2.value << " - " << vc2.comment << std::endl;
    }

    {
        using IntStack=Stack<int>;
        IntStack intStackInst;
        intStackInst.push(6);
        // std::cout << intStackInst.top() <<endl;
        using StringStack=Stack<std::string>;
        StringStack StringStackInst;
        StringStackInst.push("zxcv");
        // StringStackInst.printOn(std::cout);
        std::cout << StringStackInst;
        std::cout << intStackInst;
    }

    {
        printSize(MyString{}); // 编译通过，输出 Size: 5
        // std::cout << std::true_type::value<<endl;
        // std::cout << std::false_type::value<<endl;
        // printSize(NoSizeType{}); // 触发断言：error: static assertion failed: T must have size() member function!
    }

    {
        Stack<int*> ptrStack; // stack of pointers (special implementation)
        ptrStack.push(new int{42});
        std::cout << *ptrStack.top();
        delete ptrStack.pop();
    }

    {
        printMul(1,"xzcv",4);
    }
    {
        // printFold("123",2,3.5f, 'a');
    }

    {
        std::vector<int> vec = {1, 2, 3};
        printFirstElement(vec); // 输出 1
    }
    {
        Calculator c;
        std::cout << c.add(2,3) <<std::endl;
        Calculator::Nested<int> t{6};
        t.print();
        Calculator::Nested<std::string> str("zxvxcv123132");
        str.print();
    }
    {
        MyCollection<int, std::vector> vecCol1;
        vecCol1.add(5);
        vecCol1.add(6);
        vecCol1.print();
        // 使用 list 作为底层容器
        MyCollection<int, std::list> listColl;
        listColl.add(3);
        listColl.add(4);
        listColl.print(); // 输出 3 4
    }
    {
        std::cout << getDefaultValue<int>() << std::endl;    // 输出 0
        std::cout << getDefaultValue<double>() << std::endl; // 输出 0
        std::cout << (getDefaultValue<int*>() == nullptr) << std::endl; // 输出 1（true）
    }
    {
        printString("xzvc");
        printString("xzvcsaasfdasf");
    }
    {
        int arr1[5] = {1,2,3,4,5};
        printAnyArray(arr1);
        string sarr[2] = {"apple", "banana"};
        printAnyArray(sarr);
        char str[6] = "hello";
        printAnyArray(str);

        int arr2D[3][4] = {{1,2,3,4}, {5,6,7,8}, {9,10,11,12}};
        printAnyArray(arr2D); 
    }

    {
        int* ptr = nullptr;
        allocateInt(ptr);
        std::cout << *ptr <<std::endl;
    }

    {
        // 推导 const MyType 的 getVal() 返回类型（和非const版本一致，但逻辑不同）
        using ConstRet = decltype(declval<const MyType>().getVal());
        static_assert(is_same_v<ConstRet, int>, "类型不匹配");
    
        // 推导 MyType& 的 val 成员类型
        using RefValT = decltype(declval<MyType&>().val);
        static_assert(is_same_v<RefValT, int>, "类型不匹配");
    }

    {
        // 推导成员类型 DataType
        // 场景1：推导嵌套类型 → 直接用 类名::嵌套类型，无需declval
        using DataT = AbstractClass::DataType;
        static_assert(is_same_v<DataT, vector<int>>, "嵌套类型推导错误");
    
        // 推导成员变量 max_val 的类型
        using MaxValT = decltype(declval<AbstractClass>().max_val);
        static_assert(is_same_v<MaxValT, const int>, "类型不匹配");
    }

    {
        // 推导 getName() 的返回类型
        using NameRet = decltype(declval<NoDefaultCtor>().getName());
        static_assert(is_same_v<NameRet, string>, "类型不匹配"); // 编译期断言
    
        // 推导 add(int, int) 的返回类型
        using AddRet = decltype(declval<NoDefaultCtor>().add(0, 0));
        static_assert(is_same_v<AddRet, int>, "类型不匹配");
    }
    {
        // vector 和 string 都有 size()，返回 size_t → true
        cout << HasSizeFunc<vector<int>>::value << endl;  // 1
        cout << HasSizeFunc<string>::value << endl;       // 1
    
        // int 没有 size() → false
        cout << HasSizeFunc<int>::value << endl;          /
    }
}
