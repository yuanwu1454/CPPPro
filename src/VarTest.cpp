#include "VarTest.h"
#include <iostream>
#include <cstdlib>
#include <csignal>
#include <cstring>
#ifdef _WIN32
#include <windows.h> // Windows系统头文件
#else
#include <unistd.h>  // Linux系统头文件
#include <sys/mman.h>
#endif


// 栈：地址通常是高地址，且地址值会随函数调用快速变化；
// 堆：地址介于栈和静态区之间，由malloc/new分配，无固定地址范围但可通过分配函数标记；
// 静态区：地址是低地址，可修改，生命周期全程；
// 常量区：地址也是低地址（和静态区接近），但具备只读属性（修改会触发异常）。

using namespace std;

// 全局变量（静态区），用于获取静态区地址范围参考
static int static_var = 10;
// 全局常量（常量区），用于获取常量区地址范围参考
static const int const_static_var = 20;

// 检测地址是否为只读（常量区特征）
bool is_read_only(const void* addr) {
#ifdef _WIN32
    // Windows：通过VirtualQuery获取内存页属性
    MEMORY_BASIC_INFORMATION mbi;
    VirtualQuery(addr, &mbi, sizeof(mbi));
    // PAGE_READONLY = 只读, PAGE_EXECUTE_READ = 执行+只读
    return (mbi.Protect == PAGE_READONLY || mbi.Protect == PAGE_EXECUTE_READ);
#else
    // Linux：通过mmap获取内存页属性
    int prot = mprotect((void*)((size_t)addr & ~(sysconf(_SC_PAGESIZE)-1)), 1, PROT_READ);
    if (prot == 0) {
        // 尝试写入，判断是否只读
        volatile char* p = (volatile char*)addr;
        char temp = *p;
        // 捕获段错误信号，避免程序崩溃
        signal(SIGSEGV, [](int) { exit(1); });
        *p = temp; // 尝试修改
        return false;
    }
    return true;
#endif
}

// 核心判断函数：返回变量所属内存区域
string get_memory_region(const void* addr) {
    // 1. 先判断栈：栈地址 > 静态区/常量区地址
    const void* static_addr = &static_var;
    if ((size_t)addr > (size_t)static_addr * 2) { // 栈地址通常远大于静态区
        return "栈 (Stack)";
    }

    // 2. 判断常量区：只读属性
    if (is_read_only(addr)) {
        return "常量区 (Constant Area)";
    }

    // 3. 判断静态区：低地址+可修改
    if ((size_t)addr < (size_t)static_addr * 1.5) { // 静态区地址范围
        return "静态区 (Static Area)";
    }

    // 4. 剩余为堆
    return "堆 (Heap)";
}

void VarTest::Test()
{
    // 测试栈变量
    int stack_var = 30;
    cout << "stack_var 地址:" << &stack_var 
         << " 所属区域:" << get_memory_region(&stack_var) << endl;

    // 测试堆变量
    int* heap_var = new int(40);
    cout << "heap_var 地址:" << heap_var 
         << " 所属区域:" << get_memory_region(heap_var) << endl;

    // 测试静态区变量
    cout << "static_var 地址:" << &static_var 
         << " 所属区域:" << get_memory_region(&static_var) << endl;

    // 测试常量区变量
    cout << "const_static_var 地址:" << &const_static_var 
         << " 所属区域:" << get_memory_region(&const_static_var) << endl;

    // 测试字符串常量（常量区）
    const char* str_const = "hello";
    cout << "str_const 地址:" << str_const 
         << " 所属区域:" << get_memory_region(str_const) << endl;

    // 测试static const变量（常量区）
    static const int sc_var = 50;
    cout << "sc_var 地址:" << &sc_var 
         << " 所属区域:" << get_memory_region(&sc_var) << endl;

    delete heap_var;
}
