#include "UniquePtr.h"
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// 独占所有权：资源只有一个所有者，且不需要共享（这是最核心的前提）；
// 零开销要求：不接受 shared_ptr 的引用计数开销（如高性能场景、嵌入式开发）；
// 自动安全释放：需要 RAII 机制避免内存 / 资源泄漏（尤其是异常场景）；
// 语义明确性：需要通过 unique_ptr 明确告知代码阅读者 “这个资源是独占的”。
// 拷贝构造函数与赋值重载给删除了
// 自定义测试类
class MyClass {
public:
    MyClass(int val) : value(val) {
        std::cout << "MyClass construct:" << value << std::endl;
    }
    ~MyClass() {
        std::cout << "MyClass destruct:" << value << std::endl;
    }
    void print() {
        std::cout << "value:" << value << std::endl;
    }
private:
    int value;
};

// 返回动态创建的字符串对象
std::unique_ptr<std::string> createCustomString(const std::string& prefix, int num) {
    // 拼接字符串
    std::string content = prefix + std::to_string(num);
    // make_unique 避免直接 new，更安全
    return std::make_unique<std::string>(content);
}

// 接收 unique_ptr 并使用（传值：所有权转移；传引用：不转移）
void useString(const std::unique_ptr<std::string>& str_ptr) {
    if (str_ptr) { // 检查指针是否为空
        std::cout << "use string:" << *str_ptr << std::endl;
    }
}

// 测试类
class Item {
public:
    Item(int id) : id_(id) {
        std::cout << "Item " << id_ << " ctor" << std::endl;
    }
    ~Item() {
        std::cout << "Item " << id_ << " dest" << std::endl;
    }
    int getId() const { return id_; }
private:
    int id_;
};

namespace UniquePtrSpace
{
    void Test()
    {
        {
            // 方式1：直接初始化（C++11 及以上）
            std::unique_ptr<MyClass> ptr1(new MyClass(10));
            ptr1->print(); // 调用成员函数，和裸指针用法一致

            // 方式2：make_unique（C++14 推荐，更安全）
            auto ptr2 = std::make_unique<MyClass>(20);
            ptr2->print();

            // 禁止拷贝（编译报错），体现独占性
            // std::unique_ptr<MyClass> ptr3 = ptr1; 

            // 允许移动（所有权转移）
            std::unique_ptr<MyClass> ptr4 = std::move(ptr1);
            if (ptr1 == nullptr) { // ptr1 已失去所有权，变为空
                std::cout << "ptr1 is empty" << std::endl;
            }
            ptr4->print(); // ptr4 接管对象

            // 手动释放（一般不需要，除非提前释放）
            ptr4.reset(); 
            if (ptr4 == nullptr) {
                std::cout << "ptr4 is released" << std::endl;
            }
        }

        {
            // 接收函数返回的 unique_ptr，接管所有权
            auto str_ptr = createCustomString("num_", 100);
            useString(str_ptr); // 传引用，不转移所有权

            // 重置指针（提前释放）
            str_ptr.reset(new std::string("reassign"));
            useString(str_ptr);
        }

        {
            // 容器存储 unique_ptr
            std::vector<std::unique_ptr<Item>> item_list;

            // 添加元素（必须用 std::move，因为 unique_ptr 不可拷贝）
            for (int i = 1; i <= 3; ++i) {
                item_list.push_back(std::make_unique<Item>(i));
            }

            // 遍历并使用元素
            for (const auto& ptr : item_list) {
                std::cout << "Item ID " << ptr->getId() << std::endl;
            }

            // 删除指定元素（容器会析构对应的 unique_ptr，自动释放内存）
            item_list.erase(item_list.begin() + 1); // 删除第二个元素（id=2）
            std::cout << "delete id=2 " << std::endl;

            // 清空容器（所有剩余元素都会被析构）
            item_list.clear();
        }
        {
            // 管理动态数组（注意数组语法：std::unique_ptr<int[]>）
            std::unique_ptr<int[]> arr_ptr(new int[5]{1, 2, 3, 4, 5});

            // 访问数组元素
            for (int i = 0; i < 5; ++i) {
                std::cout << arr_ptr[i] << " "; // 用 [] 访问，和普通数组一致
            }
            std::cout << std::endl;

            // 重置数组（自动释放原数组）
            arr_ptr.reset(new int[3]{10, 20, 30});
            for (int i = 0; i < 3; ++i) {
                std::cout << arr_ptr[i] << " ";
            }
            std::cout << std::endl;
        }
    }
}
