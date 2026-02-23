#pragma once

namespace DeclvalSpace
{
    // 在不创建对象的前提下，“模拟” 出某个类型的对象（或引用），用于推导类型 / 获取成员类型，尤其适用于没有默认构造函数的类型。
    struct MyType {
        int val;
        int getVal() { return val; }
        int getVal() const { return val * 2; } // const 版本
    };

    // 纯虚类：无法实例化（不能创建对象）
    class AbstractClass {
    public:
        virtual void func() = 0;
        using DataType = vector<int>;
        const int max_val = 100;
    };

    template<typename T>
    struct HasSizeFunc
    {
    private:
        template<typename U>
        static true_type test(decltype(&U::size));
        // 这样写也可以？
        // static true_type test(decltype(declval<U>().size())*);
        
        template<typename U>
        static false_type test(...);
    public:
        constexpr static bool Value = decltype(test<T>(nullptr))::value;
    };
    

    // 无默认构造的类型
    struct NoDefaultCtor {
        NoDefaultCtor(double) {} // 只有double参数的构造
        string getName() const { return "test"; }
        virtual int add(int a, int b) = 0;
    };

    
    inline void Test()
    {
        {
            // test MyType getVal const 方法的返回类型是否一致
            using type = decltype(declval<MyType&>().getVal());
            static_assert(std::is_same_v<type, int>, "type is not int");
            // test MyType getVal 方法的返回类型是否一致
            using type = decltype(declval<const MyType>().getVal());
            static_assert(std::is_same_v<type, int>, "type is not int");
        }

        {
            // 推导成员类型 DataType
            // 场景1：推导嵌套类型 → 直接用 类名::嵌套类型，无需declval
            using DataType = AbstractClass::DataType;
            static_assert(std::is_same_v<DataType, vector<int>>, "not same");
    
            // 推导成员变量 max_val 的类型
            using MaxValType = decltype(declval<AbstractClass>().max_val);
            static_assert(std::is_same_v<MaxValType, const int>, "not same");
        }
        

        {
            // 推导 getName() 的返回类型
            using MaxValType = decltype(declval<NoDefaultCtor>().getName());
            // 推导 add(int, int) 的返回类型
            using MaxValType2 = decltype(declval<NoDefaultCtor>().add(1,1));
        }
        {
            // vector 和 string 都有 size()，返回 size_t → true
            std::cout << HasSizeFunc<vector<int>>::Value;
            // int 没有 size() → false
            std::cout << HasSizeFunc<int>::Value;
        }
    }
}
