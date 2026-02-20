#pragma once

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