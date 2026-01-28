#include "ConstCastTest.h"
#include <string>
#include <iostream>
using namespace  std;
class MyString {
private:
    char* data;
    int length;
public:
    // 构造函数
    MyString(const char* str) {
        length = strlen(str);
        data = new char[length + 1];
        strcpy_s(data, length+1, str);
    }

    // 析构函数
    ~MyString() {
        delete[] data;
    }

    // const 版本：核心逻辑
    const char& operator[](int index) const {
        if (index < 0 || index >= length) {
            static char err_char = '\0';
            return err_char;
        }
        return data[index];
    }

    // 非 const 版本：复用 const 版本逻辑
    char& operator[](int index) {
        // 步骤1：将 *this 转为 const MyString&，调用 const 版本
        // 步骤2：用 const_cast 移除返回值的 const 引用限定
        return const_cast<char&>(
            static_cast<const MyString&>(*this)[index]
        );
    }

    // 获取长度
    int getLength() const {
        return length;
    }
};

void ConstCastTest::Test()
{
    {
        MyString str("hello");
        // 非 const 版本：修改值
        str[0] = 'H';
        cout << "修改后：";
        for (int i = 0; i < str.getLength(); i++) {
            cout << str[i];
        }
        cout << endl; // 输出：Hello
        
        // const 版本：只读
        const MyString c_str("world");
        cout << "const 版本" << c_str[2] << endl;
        // cout << "const 版本：" << c_str[2] << endl; // 输出：r
        // c_str[2] = 'x'; // 报错，const 版本不能修改
        
        // 越界测试
        cout << str[10] << endl; // 输出：索引越界！（换行）
    }
    {
        int a = 100;
        int v = 200;
        const int* const p = &a;
        // error 指针指向的值无法修改
        // *p = *p + 1;
        // error 指针不可更改
        // p = &v;
        // const int* p 与 int const* p 表示的都是指针指向的值不可修改
    }
}


namespace MyNS
{
    int kvar =7;
}