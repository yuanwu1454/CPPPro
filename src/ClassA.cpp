#include "ClassA.h"
#include "MyNs.h"

namespace MyNS {

    int svar = 100;

    void func() {
        cout << "func" << endl;
    }
}

namespace A2 {
    int v = 3;
}

// 修复：默认构造函数初始化ptr为合法空字符串，避免nullptr隐患
ClassA::ClassA() : value(0) {
    printf("默认构造函数\n");
    // 初始化ptr为包含'\0'的空字符串，而非nullptr
    ptr = new char[1];
    ptr[0] = '\0';
}

// 修复：用初始化列表初始化value，避免未初始化；NewRes依赖合法ptr
ClassA::ClassA(int InValue, const char* inPtr) : value(InValue) {
    printf("普通构造函数\n");
    // 先初始化ptr为合法空字符串，再调用NewRes
    ptr = new char[1];
    ptr[0] = '\0';
    NewRes(inPtr);
}

// 修复：移除错误的DelRes()调用，仅转移资源
ClassA::ClassA(ClassA&& a) noexcept {
    printf("移动构造函数\n");
    value = a.value;
    // 转移资源，无需释放新对象资源（新对象刚创建，无资源）
    ptr = a.ptr;
    a.ptr = nullptr;
    // 可选：用std::exchange更优雅
    // ptr = std::exchange(a.ptr, nullptr);
    // value = std::exchange(a.value, 0);
}

// 拷贝构造函数：逻辑正确，保留
ClassA::ClassA(const ClassA& a) {
    printf("拷贝构造函数\n");
    // 先初始化ptr为合法空字符串
    ptr = new char[1];
    ptr[0] = '\0';
    value = a.value;
    NewRes(a.ptr);
}

// 修复：增加自赋值打印，调试更友好
ClassA& ClassA::operator=(const ClassA& a) {
    printf("拷贝赋值函数调用\n");
    if (this != &a) {
        NewRes(a.ptr);
        value = a.value;
    }
    else {
        printf("拷贝赋值：自赋值，跳过\n");
    }
    return *this;
}

// 修复：移动赋值先释放自身资源，再转移
ClassA& ClassA::operator=(ClassA&& a) noexcept {
    printf("移动赋值函数调用\n");
    if (this != &a) {
        // 第一步：释放当前对象原有资源
        DelRes();
        // 第二步：转移对方资源
        value = a.value;
        ptr = a.ptr;
        // 第三步：对方置空，避免重复释放
        a.ptr = nullptr;
        a.value = 0;
    }
    else {
        printf("移动赋值：自赋值，跳过\n");
    }
    return *this;
}

ClassA::~ClassA() {
    DelRes(true);
    printf("classA 析构函数\n");
}
//
//bool ClassA::operator<(const ClassA& a) const
//{
//    return value < a.value;
//}
//
//bool ClassA::operator==(const ClassA& a) const
//{
//    return value == a.value;
//}

// 修复：printf格式化字符串增加分隔符，降低风险；优化打印逻辑
void ClassA::DelRes(bool bPrint) {
    if (bPrint) {
        // 修复：用%c或分开打印，避免%s接收nullptr的风险
        printf("begin del res: %s\n", ptr ? "exists ptr" : "ptr is nullptr");
    }
    if (ptr) {
        delete[] ptr;
        ptr = nullptr;
    }
}

// 逻辑正确，保留（NewRes内先DelRes，再分配资源）
void ClassA::NewRes(const char* InPtr) {
    DelRes();
    if (InPtr) {
        printf("classA 申请资源 %s\n", InPtr);
        int len = strlen(InPtr);
        ptr = new char[len + 1];
        strcpy_s(ptr, len + 1, InPtr);
    }
}