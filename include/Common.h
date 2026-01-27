#include <iostream>
using namespace  std;
// 辅助模板：递归解析类型（核心逻辑）
template <typename T>
void print_type_detail() {
    // 步骤1：处理指针本身的 const/volatile（先解析指针修饰）
    if constexpr (is_const_v<T>) {
        print_type_detail<remove_const_t<T>>(); // 先解析去掉 const 后的类型
        cout << " const"; // 追加指针本身的 const
        return;
    }
    // 步骤2：处理指针类型（解析指向的类型）
    if constexpr (is_pointer_v<T>) {
        print_type_detail<remove_pointer_t<T>>(); // 解析指针指向的类型
        cout << "*"; // 追加指针标识
        return;
    }
    // 步骤3：处理指向类型的 const/volatile
    if constexpr (is_const_v<remove_pointer_t<T>>) {
        // 这里是兼容旧逻辑，实际步骤1已处理，可省略
    }
    // 步骤4：基础类型
    if constexpr (is_same_v<T, int>) {
        cout << "int";
    } else if constexpr (is_same_v<T, float>) {
        cout << "float";
    } else if constexpr (is_same_v<T, char>) {
        cout << "char";
    }
    // 可扩展其他基础类型（如 double、bool 等）
}

template <typename T>
void print_type(const char* var_name) {
    cout << var_name << " 的类型：";
    print_type_detail<T>();
    cout << endl;
}