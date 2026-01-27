#pragma once
#include <iostream>
using namespace  std;

// 构造函数
// 拷贝构造函数
// 默认拷贝构造函数的缺点
// 移动构造函数
// static_cast, dynamic_cast, const_cast
// shared,unique,weak
// new,delete, malloc, free

namespace my_namespace
{
    extern int a;
    class Vector
    {
    public:
        Vector():x(0),y(0){cout << "vec default ctor" <<endl;}
        Vector(int inX, int inY):x(inX), y(inY){cout << "vec ctor" <<endl;}
        Vector(const Vector& v)
        {
            x=v.x;
            y=v.y;
            cout<<"copy ctor" <<endl;
        }
        Vector(Vector&& v) noexcept
        {
            x = move(v.x);
            y = move(v.y);
        }
        Vector& operator=(const Vector& v)
        {
            if (this == &v)
                return *this;
            cout << "copy assign func " <<endl;
            x = v.x;
            y = v.y;
            return *this;
        }

        Vector& operator=(Vector&& v) noexcept{
            cout << "move assign func " <<endl;
            x = move(v.x);
            y = move(v.y);
            return *this;
        }
        ~Vector()
        {
            cout << "desctructor" <<endl;
        }

        bool operator>(const Vector& v) const
        {
            if(x !=v.x)return x>v.x;
            return y>v.y;
        }
        bool operator==(const Vector& v) const
        {
            return x == v.x && y == v.y;
        }
        bool operator!=(const Vector& v) const
        {
            return !(*this==v);
        }
        bool operator<(const Vector& v) const
        {
            return v>*this;
        }
        bool operator<=(const Vector& v) const
        {
            return !(v<*this);
        }

        bool operator>=(const Vector& v) const
        {
            return !(*this>v);
        }

        friend ostream& operator<<(ostream& os, const Vector& v);
        friend istream& operator>>(istream& is, Vector& v);

    private:
        int x;
        int y;
    };

    inline ostream& operator<<(ostream& os, const Vector& v)
    {
        os << "v.x " << v.x << " v.y" << v.y <<endl;
        return os;
    }


    inline istream& operator>>(istream& is, Vector& v)
    {
        is >> v.x >> v.y;
        return is;
    }

    void testFree()
    {
        int* p = new int;
        int* parr = new int[5];
        void* memory = malloc(sizeof(int));
        int* pi = new(memory) int;
        delete[] parr;
        {
            int (*pa)[8] = new int[5][8];
            // 使用示例：赋值+访问
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 8; j++) {
                    pa[i][j] = i * 8 + j; // 正常赋值
                    cout << pa[i][j] << " ";
                }
                cout << endl;
            }

            delete[] pa;
        }

        {
            int* pa[8];
            for(int i =0;i< 8;i++)
            {
                pa[i] = new int[5];
            }
            pa[0][0] = 100; 
            cout << pa[0][0] << endl;
            
            for (int i = 0; i < 8; i++) {
                delete[] pa[i];
            }
        }
    }
}


