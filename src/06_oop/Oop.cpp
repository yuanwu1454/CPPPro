#include "Oop.h"

#include <cassert>
#include <memory>
#include <utility>
#include <vector>

namespace {
class Shape {
public:
    virtual ~Shape() {}
    virtual int area() const = 0;
};

class Rectangle : public Shape {
public:
    // 普通构造函数：直接使用宽和高创建一个新对象。
    Rectangle(int width, int height) : width_(width), height_(height) {}

    // 拷贝构造函数：从已有对象复制出一个独立对象。
    Rectangle(const Rectangle& other)
        : width_(other.width_), height_(other.height_) {}

    // 移动构造函数：从临时对象转移资源或状态，避免不必要的复制。
    // 本例成员是 int，移动和拷贝效果相同；复杂资源类中差异才明显。
    Rectangle(Rectangle&& other) noexcept
        : width_(other.width_), height_(other.height_)
    {
        other.width_ = 0;
        other.height_ = 0;
    }

    // 拷贝赋值：对象已经存在，把另一个对象的值复制过来。
    Rectangle& operator=(const Rectangle& other)
    {
        if (this != &other) {
            width_ = other.width_;
            height_ = other.height_;
        }
        return *this;
    }

    // 移动赋值：对象已经存在，接收另一个对象转移过来的状态。
    Rectangle& operator=(Rectangle&& other) noexcept
    {
        if (this != &other) {
            width_ = other.width_;
            height_ = other.height_;
            other.width_ = 0;
            other.height_ = 0;
        }
        return *this;
    }

    int area() const override
    {
        return width_ * height_;
    }

    int width() const
    {
        return width_;
    }

    int height() const
    {
        return height_;
    }

private:
    int width_;
    int height_;
};
}

void testOop()
{
    // 基类指针可以指向派生类对象，统一管理不同的 Shape。
    std::vector<std::unique_ptr<Shape> > shapes;
    shapes.emplace_back(new Rectangle(4, 5));
    shapes.emplace_back(new Rectangle(2, 3));

    // virtual 触发运行时多态，实际调用 Rectangle::area()。
    assert(shapes[0]->area() == 20);
    assert(shapes[1]->area() == 6);

    // 构造函数：对象从无到有。
    Rectangle original(4, 5);
    assert(original.area() == 20);

    // 拷贝构造：用已有对象初始化新对象，两个对象彼此独立。
    Rectangle copied(original);
    assert(copied.area() == 20);
    assert(copied.width() == original.width());

    // 移动构造：用临时对象初始化新对象；适合转移动态内存等资源。
    Rectangle moved(Rectangle(6, 7));
    assert(moved.area() == 42);

    // 拷贝赋值：两个对象都已存在，复制右侧对象的状态。
    Rectangle copyAssigned(1, 1);
    copyAssigned = original;
    assert(copyAssigned.area() == 20);

    // 移动赋值：两个对象都已存在，转移右侧对象的状态。
    Rectangle moveAssigned(1, 1);
    moveAssigned = Rectangle(8, 9);
    assert(moveAssigned.area() == 72);
}
