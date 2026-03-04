#include "Function.h"

#include <functional>

namespace MyFunction
{

    // 普通函数
    int add(int a, int b) {
        return a + b;
    }

    int multiply(int a, int b) {
        return a * b;
    }

    class Calculator {
    public:
        int add(int a, int b) { // 成员函数
            return a + b;
        }

        // 仿函数（重载()运算符）
        int operator()(int a, int b) {
            return a * b;
        }

        std::function<int(int,int)> f;
    };
    // 模拟异步任务：执行完后调用回调函数
    void async_task(int data, std::function<void(int)> callback) {
        // 模拟耗时操作
        std::this_thread::sleep_for(std::chrono::seconds(1));
        int result = data * 2;
        // 执行回调
        callback(result);
    }

    // 返回一个包装了lambda的std::function
    std::function<int()> create_func_bad() {
        int temp = 100; // 局部变量，函数结束后销毁
        // 引用捕获temp，但temp会随函数返回销毁
        std::function<int()> func = [&temp]() {
            return temp; // 未定义行为：访问已销毁的变量
        };
        return func;
    }

    
    void test()
    {
        // 场景 1：存储和调用普通函数 / 函数指针
        {
            // 1. 存储普通函数
            std::function<int(int, int)> func = add;
            std::cout << "add(3,4) = " << func(3, 4) << std::endl; // 输出 7

            // 2. 动态切换可调用对象
            func = multiply;
            std::cout << "multiply(3,4) = " << func(3, 4) << std::endl; // 输出 12

            // 3. 结合函数指针
            int (*fp)(int, int) = add;
            func = fp;
            std::cout << "func via fp: " << func(5, 6) << std::endl; // 输出 11
        }
        // 存储和调用 lambda 表达式
        {
            // 1. 存储无捕获的 lambda
            std::function<void()> print_hello = []() {
                std::cout << "Hello, std::function!" << std::endl;
            };
            print_hello(); // 输出 Hello, std::function!

            // 2. 存储有捕获的 lambda（核心场景）
            int base = 10;
            std::function<int(int)> add_base = [base](int x) {
                return x + base;
            };
            std::cout << "add_base(5) = " << add_base(5) << std::endl; // 输出 15

            // 3. 实战：用 std::function 作为容器元素，存储不同逻辑的 lambda
            std::vector<std::function<int(int, int)>> ops;
            ops.push_back([](int a, int b) { return a + b; });
            ops.push_back([](int a, int b) { return a - b; });
            ops.push_back([](int a, int b) { return a * b; });

            for (const auto& op : ops) {
                std::cout << op(6, 2) << " "; // 输出 8 4 12
            }
            std::cout << std::endl;
        }
        {
            Calculator calc;

            // 1. 存储类的成员函数（必须绑定实例）
            // 方式1：用 std::bind
            std::function<int(int, int)> mem_func = std::bind(&Calculator::add, &calc, 
                                                              std::placeholders::_1, 
                                                              std::placeholders::_2);
            std::cout << "mem_func(2,3) = " << mem_func(2, 3) << std::endl; // 输出 5

            // 方式2：用 lambda（更推荐，可读性更高）
            std::function<int(int, int)> mem_func_lambda = [&calc](int a, int b) {
                return calc.add(a, b);
            };
            std::cout << "mem_func_lambda(4,5) = " << mem_func_lambda(4, 5) << std::endl; // 输出 9

            // 2. 存储仿函数
            std::function<int(int, int)> functor = calc;
            std::cout << "functor(3,4) = " << functor(3, 4) << std::endl; // 输出 12
        }

        {
            // 定义回调逻辑
            std::function<void(int)> on_task_complete = [](int res) {
                std::cout << "异步任务完成，结果：" << res << std::endl;
            };

            // 启动异步任务，传入回调
            std::cout << "启动异步任务..." << std::endl;
            async_task(100, on_task_complete);

            // 等待任务结束
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
        {
                auto bad_func = create_func_bad();
                std::cout << bad_func() << std::endl; // 结果随机/程序崩溃
        }
        {
            int global_like_var = 200; // 生命周期覆盖整个main函数
            // 引用捕获这个变量，完全安全
            std::function<int()> func = [&global_like_var]() {
                global_like_var += 10; // 还能修改原变量（这是引用的优势）
                return global_like_var;
            };

            std::cout << func() << std::endl; // 输出 210
            std::cout << global_like_var << std::endl; // 输出 210（原变量被修改）

            // 即使把func传给其他函数，只要global_like_var还在，就没问题
            auto call_func = [](std::function<int()> f) {
                std::cout << f() << std::endl; // 输出 220
            };
            call_func(func);
            std::cout << global_like_var << std::endl; // 输出 220
        }
        {
            int a = 10;
            // 值捕获 + mutable：修改的是副本，不影响原变量
            std::function<void()> func1 = [a]() mutable {
                a += 5;
                std::cout << "func1内的a：" << a << std::endl; // 输出 15
            };
            func1();
            std::cout << "原变量a：" << a << std::endl; // 输出 10（未变）

            // 引用捕获：修改的是原变量，无需mutable
            std::function<void()> func2 = [&a]() {
                a += 5;
                std::cout << "func2内的a：" << a << std::endl; // 输出 15
            };
            func2();
            std::cout << "原变量a：" << a << std::endl; // 输出 15（已变）
        }
    }
}
