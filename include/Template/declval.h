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

    // 模板元函数：判断 T 是否有 size() 成员，且返回类型为 size_t
    template<typename T>
    struct HasSizeFunc {
    private:
        // 重载1：匹配有 size() 且返回 size_t 的类型（优先匹配）
        template<typename U>
        static true_type test(decltype(declval<U>().size())*);
    
        // 重载2：匹配所有其他类型
        template<typename U>
        static false_type test(...);
    public:
        static constexpr bool value = decltype(test<T>(nullptr))::value;
    };

    // 无默认构造的类型
    struct NoDefaultCtor {
        NoDefaultCtor(double) {} // 只有double参数的构造
        string getName() const { return "test"; }
        int add(int a, int b) { return a + b; }
    };
    inline void Test()
    {
        {

            using retTye = decltype(declval<MyType>().getVal());
            static_assert(is_same_v<retTye, int>, "not match");
            // 推导 const MyType 的 getVal() 返回类型（和非const版本一致，但逻辑不同）
            // using ConstRet = decltype(declval<const MyType>().getVal());
            // static_assert(is_same_v<ConstRet, int>, "类型不匹配");
    
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
            cout << HasSizeFunc<int>::value << endl;         
        }
    }
}
