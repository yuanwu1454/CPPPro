#pragma once

#include <iostream>
#include "stdio.h"
using namespace std;

class ClassA {
public:
	ClassA();
	ClassA(int InValue, const char* inPtr);
	ClassA(ClassA&& a) noexcept;
	ClassA(const ClassA& a);
	// 拷贝赋值构造函数
	ClassA& operator=(const ClassA& a);
	// 移动赋值构造函数
	ClassA& operator=(ClassA&& a) noexcept;
	~ClassA();

	// 本质上所有的>,<.==,<=,>=,!= 都可以通过== 与 < 来判别
	// 函数后面 const 表示 不会改变对象。 
	//bool operator<(const ClassA& a)const;
	//bool operator==(const ClassA& a)const;
	//bool operator!=(const ClassA& rhs) const {
	//	return !(*this == rhs);
	//}
	//bool operator>(const ClassA& rhs) const {
	//	return rhs < *this; 
	//}
	//// 重载 <=：复用 <
	//bool operator<=(const ClassA& rhs) const {
	//	return !(*this > rhs); // a <= b 等价于 !(a > b)
	//}
	//// 重载 >=：复用 <
	//bool operator>=(const ClassA& rhs) const {
	//	return !(*this < rhs); // a >= b 等价于 !(a < b)
	//}

	//friend bool operator==(const int& value, const ClassA& rhs);
	//friend bool operator!=(const int& value, const ClassA& rhs);
	//friend bool operator<(const int& value, const ClassA& rhs);
	//friend bool operator<(const ClassA& lhs,const int& value);
	friend ostream& operator <<(ostream& os, const ClassA& rhs);
	friend istream& operator>>(istream& is, ClassA& p);

protected:
	void DelRes(bool bPrint=false);
	void NewRes(const char* InPtr);
private:
	int value;
	char* ptr=nullptr;
};


//bool operator==(const int& value, const ClassA& rhs) {
//	return value == rhs.value;
//}
//
//bool operator!=(const int& value, const ClassA& rhs) {
//	return !(value == rhs);
//}
//
//// 非成员函数比较 优势就是对称比较 跨类型比较 容易支持
//// 感觉最好还是  直接使用成员函数更好一点 具有封装性
//bool operator<(const int& value, const ClassA& rhs) {
//	return value < rhs.value;
//}
//
//bool operator<(const ClassA& lhs, const int& value){
//	return lhs.value < value;
//}

inline ostream& operator<<(ostream& os, const ClassA& rhs)
{
	os << "姓名：" << rhs.value;
	if (rhs.ptr) {
		os << "ptr" << *rhs.ptr;
	}
	return os;
}

inline istream& operator>>(istream& is, ClassA& p)
{
	is >> p.value >> p.ptr;
	return is;

}
