#include "Templates.h"

#include <array>
#include <cassert>
#include <string>

namespace {
template <typename T>
T maxValue(const T& left, const T& right)
{
    return left > right ? left : right;
}

template <typename T>
class Box {
public:
    explicit Box(const T& value) : value_(value) {}

    const T& value() const
    {
        return value_;
    }

private:
    T value_;
};

template <typename T, std::size_t Size>
std::size_t arraySize(const T (&)[Size])
{
    return Size;
}
}

void testTemplates()
{
    // 函数模板：编译器根据实参推导 T，生成对应类型的函数。
    assert(maxValue(3, 5) == 5);
    assert(maxValue(std::string("cpp"), std::string("primer")) == "primer");

    // 类模板：同一个类可以保存不同类型的数据，保持类型安全。
    Box<int> number(42);
    Box<std::string> text("C++ Primer");
    assert(number.value() == 42);
    assert(text.value() == "C++ Primer");

    // 非类型模板参数：数组长度在编译期作为模板参数传入。
    int values[4] = {1, 2, 3, 4};
    assert(arraySize(values) == 4);

    // 标准库容器本身也是模板，array 的元素类型和长度都由模板参数决定。
    std::array<int, 3> fixedValues{{1, 2, 3}};
    assert(fixedValues.size() == 3);
}
