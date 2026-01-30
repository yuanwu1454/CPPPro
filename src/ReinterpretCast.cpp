#include "ReinterpretCast.h"
#include <cstdint>
#include <iostream>
using namespace std;

struct NetworkPacket {
    uint16_t cmd;   // 2字节命令码
    uint32_t len;   // 4字节长度
    char data[10];  // 10字节数据
};


void func() { std::cout << "func called" << std::endl; }


class MyClass {
private:
    int secret = 100;
};


// 私有继承std::string，复用其功能但对外隐藏
class LoggedString : private std::string {
public:
    // 只暴露需要的接口，并添加日志逻辑
    void append(const char* s) {
        std::string::append(s); // 直接调用基类的append
    }

    // 暴露获取长度的接口，加日志
    size_t length() const {
        return std::string::length(); // 调用基类的length
    }

    // 禁止对外暴露std::string的其他接口（如operator[]）
};


// 基础图形类（库内部）
class Shape {
protected:
    int x, y; // 坐标（保护成员）
    public:
    void setPos(int x_, int y_) { x = x_; y = y_; }
};

// 保护继承Shape：库内部的中间类
class RectangularShape : protected Shape {
protected:
    int width, height;
public:
    void setSize(int w, int h) { width = w; height = h; }
    // 能访问Shape的x、y
    void move(int dx, int dy) { x += dx; y += dy; }
};

// 库用户继承RectangularShape
class MyRectangle : public RectangularShape {
public:
    // 能访问RectangularShape的width、height，也能访问Shape的x、y（因为是保护继承）
    void printInfo() {
        std::cout << "pos:" << x << "," << y << std::endl;
        std::cout << "size:" << width << "," << height << std::endl;
    }
};



// 应用层几乎不使用，建议关注少一点
void ReinterpretCast::Test()
{
    // 指针与整数的相互转换（底层地址操作）
    {
        // pointer 与 int的相互转换
        int *p = new int(100);
        uintptr_t addr = reinterpret_cast<uintptr_t>(p);
        cout << "point addr is " <<hex<<  addr << endl;

        // volatile uint32_t* gpio_reg = reinterpret_cast<volatile uint32_t*>(0x1000);
        // *gpio_reg = 1;

        int* q= reinterpret_cast<int*>(addr);
        cout <<dec<< *q << endl;
    }

    {
        //场景 2：无继承关系的指针 / 引用强制转换（内存布局重解释）
        char buffer[16] = {0x01, 0x00, 0x0a, 0x00, 0x00, 0x00, 'h', 'e', 'l', 'l', 'o'};
        NetworkPacket* pkt = reinterpret_cast<NetworkPacket*>(buffer);
        std::cout << pkt->cmd << std::endl;   // 输出1（0x0001）
        std::cout << pkt->len << std::endl;     // 输出10（0x0000000a）
        std::cout << pkt->data << std::endl;   // 输出hello
        
    }


    {
        // 把函数指针转成void*（存储到回调表）
        void* func_ptr = reinterpret_cast<void*>(func);
        // 恢复函数指针并调用（需保证类型完全匹配）
        using FuncType = void(*)();
        FuncType f = reinterpret_cast<FuncType>(func_ptr);
        f(); // 输出func called
    }

    // 场景 3：绕过类型系统的特殊底层操作（极少用）
    // 比如在调试、性能分析工具中，需要访问对象的私有成员（仅调试 / 测试场景，生产环境绝对禁止）：
    {
        // 调试场景：强制访问私有成员（仅示例，生产环境禁止）
        MyClass obj;
        // 假设secret是第一个成员，直接取对象地址转成int*
        int* secret_ptr = reinterpret_cast<int*>(&obj);
        std::cout << *secret_ptr << std::endl; // 输出100（依赖类的内存布局）
    }

    {
        // 可以直接调用 loggedString的构造函数， 然后内部会触发string的构造函数
        // 虽然外部 无法直接触发string的构造函数，但是间接触发
        LoggedString s;
        s.append("hello"); // 正常调用，带日志
        cout <<"私有继承举例" << s.length() << endl;
    }

    {
        cout << "保护继承举例" <<endl;
        MyRectangle rect;
        // rect.setPos(10, 20); // 编译错误：Shape的setPos被保护继承后变为protected，对外不可见
        rect.setSize(100, 50); // 正常：RectangularShape的setSize是public
        rect.move(5, 5); // 正常：RectangularShape的move是public
        rect.printInfo(); // 正常：能访问x、y、width、height

    }
}
