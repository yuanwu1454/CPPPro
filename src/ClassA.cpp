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

ClassA::ClassA() : value(0) {
    printf("classA default ctor \n");
    ptr = new char[1];
    ptr[0] = '\0';
}

ClassA::ClassA(int InValue, const char* inPtr) : value(InValue) {
    printf("classA ctor \n");
    ptr = new char[1];
    ptr[0] = '\0';
    NewRes(inPtr);
}

ClassA::ClassA(ClassA&& a) noexcept {
    printf("move ctor \n");
    value = a.value;
    ptr = a.ptr;
    a.ptr = nullptr;
    // ptr = std::exchange(a.ptr, nullptr);
    // value = std::exchange(a.value, 0);
}

ClassA::ClassA(const ClassA& a) {
    printf("copy ctor\n");
    ptr = new char[1];
    ptr[0] = '\0';
    value = a.value;
    NewRes(a.ptr);
}

ClassA& ClassA::operator=(const ClassA& a) {
    if (this != &a) {
        NewRes(a.ptr);
        value = a.value;
    }
    else {
        printf("move \n");
    }
    return *this;
}

ClassA& ClassA::operator=(ClassA&& a) noexcept {
    printf("copy assign\n");
    if (this != &a) {
        DelRes();
        value = a.value;
        ptr = a.ptr;
        a.ptr = nullptr;
        a.value = 0;
    }
    else {
        printf("same value\n");
    }
    return *this;
}

ClassA::~ClassA() {
    DelRes(true);
    printf("classA dest\n");
}


bool ClassA::operator<(const ClassA& a) const
{
    return value < a.value;
}

bool ClassA::operator==(const ClassA& a) const
{
    return value == a.value;
}

void ClassA::Test()
{
    // 
    // ClassA a(10, "zxcvzxcv");
    //
    //
    // ClassA b = a;
    //
    // 
    // ClassA c(10, "zxcvzxcv");
    // 
    // ClassA d(45, "qwerqwer");
    // 
    // ClassA e = std::move(d);

}

void ClassA::DelRes(bool bPrint) {
    if (bPrint) {
        printf("begin del res: %s\n", ptr ? "exists ptr" : "ptr is nullptr");
    }
    if (ptr) {
        delete[] ptr;
        ptr = nullptr;
    }
}
void ClassA::NewRes(const char* InPtr) {
    DelRes();
    if (InPtr) {
        int len = strlen(InPtr);
        ptr = new char[len + 1];
        strcpy_s(ptr, len + 1, InPtr);
    }
}