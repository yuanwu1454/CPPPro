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
	ClassA& operator=(const ClassA& a);
	ClassA& operator=(ClassA&& a) noexcept;
	~ClassA();
	
	bool operator<(const ClassA& a)const;
	bool operator==(const ClassA& a)const;
	bool operator!=(const ClassA& rhs) const {
		return !(*this == rhs);
	}
	bool operator>(const ClassA& rhs) const {
		return rhs < *this; 
	}
	bool operator<=(const ClassA& rhs) const {
		return !(*this > rhs); 
	}
	bool operator>=(const ClassA& rhs) const {
		return !(*this < rhs); 
	}

	friend bool operator==(const int& value, const ClassA& rhs);
	friend bool operator!=(const int& value, const ClassA& rhs);
	friend bool operator<(const int& value, const ClassA& rhs);
	friend bool operator<(const ClassA& lhs,const int& value);
	friend ostream& operator <<(ostream& os, const ClassA& rhs);
	friend istream& operator>>(istream& is, ClassA& p);

	static void Test();
	
protected:
	void DelRes(bool bPrint=false);
	void NewRes(const char* InPtr);
private:
	int value;
	char* ptr=nullptr;
};


inline bool operator==(const int& value, const ClassA& rhs) {
	return value == rhs.value;
}

inline bool operator!=(const int& value, const ClassA& rhs) {
	return !(value == rhs);
}

inline bool operator<(const int& value, const ClassA& rhs) {
	return value < rhs.value;
}

inline bool operator<(const ClassA& lhs, const int& value){
	return lhs.value < value;
}

inline ostream& operator<<(ostream& os, const ClassA& rhs)
{
	os << " value is " << rhs.value;
	if (rhs.ptr) {
		os << " ptr is " << *rhs.ptr;
	}
	return os;
}

inline istream& operator>>(istream& is, ClassA& p)
{
	is >> p.value >> p.ptr;
	return is;

}
