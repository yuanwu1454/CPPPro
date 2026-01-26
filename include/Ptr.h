#pragma once


// const int a = 1; // 
// int a = 1; 
// 会导致报错， 定义放到头文件里面会造成多重定义错误，因为一个cpp文件可能会同时包含多个 int a = 1,导致多重定义报错。
// 即便加了头文件保护 ，也会导致报错，而且是在链接时进行报错。
// 普通全局变量 有外部链接属性、
// extern const int a; 具有外部链接信息， 会找到 const int a 的位置/
// const 在c++中具有外部链接  
//提升编译 / 运行效率
class Ptr
{
public:
	static void AddressTest1();
	static void PrintAddress(const int& v);
	static void Func();
	static void NewFunc();
	static void CharTest();
};


namespace MyNS {
	extern int k;
}