#pragma once
#include <iostream>
#include <vector>

namespace Chapter5
{

    template<typename T>
    void printFirstElement(T t)
    {
        typename T::iterator x = t.begin();
        std::cout <<"printFirstElement" << *x <<std::endl;
    }

    struct Calculator
    {
        template<typename T>
        T add(T a, T b){return a+b;}

        template<typename U>
        class Nested
        {
        public:
            Nested(U v):value(v){}
            U value;
            void print()
            {
                std::cout << value <<std::endl;
            }
        };
    };


    template<typename T, template<typename Elem, typename Alloc = std::allocator<Elem>> class Container>
    struct MyCollection
    {
        Container<T> container;
        void add(T val)
        {
            container.push_back(val);
        }
        void print()
        {
            for(auto& ele: container)
            {
                std::cout << ele << " ";
            }
            std::cout << endl;
        }
    };


    template<typename X>
    class XContainer
    {
    public:
        X value;
        XContainer(X v):value(v){};
    };

    
    template<typename U, typename X>
    class UContainer
    {
    public:
        U u_val;
        X x_val;
        UContainer(U u,X x):x_val(x),u_val(u){};
        void print()
        {
            std::cout << x_val.value << u_val <<std::endl;
        }
    };

    template<typename T, template<typename U, typename X> class Uc>
    class TContainer
    {
    public:
        Uc<T, XContainer<float>> inner;
        TContainer(T v1, float v2):inner(v1, XContainer<float>(v2)){};
        void print()
        {
            inner.print();
        }
    };


    template<typename T>
    T getDefaultValue()
    {
        return T{};
    }

    // const  // 只读：保证函数不会修改数组内容，更安全
    // T      // 数组元素类型（比如char）
    // (&val) // val是一个引用（不是指针！）
    // [N]    // 引用的对象是“长度为N的T类型数组”
    template<typename T, size_t N>
    void printString(const T (&val)[N])
    {
        std::cout<<val << N <<endl;
    }


    // 接收“长度为5的int数组”的引用（固定长度）
    template<typename T, size_t N>
    void printAnyArray(const T (&arr)[N])
    {
        cout << " size " << sizeof(arr)/sizeof(arr[0]) << " sizeN " << N  <<" type " << typeid(T).name() << endl;
        for (const auto& elem : arr) {
            cout << &elem << " ";
        }
    }

    // 指针的引用：修改外部指针的指向
    inline void allocateInt(int*& ptr) {
        ptr = new int(100); // 动态分配内存，ptr指向新地址
    }
    inline void Test()
    {
        {
            std::vector<int> vec = {1, 2, 3};
            printFirstElement(vec); // 输出 1
        }
        {
            Calculator c;
            std::cout << c.add(2,3) <<std::endl;
            Calculator::Nested<int> t{6};
            t.print();
            Calculator::Nested<std::string> str("zxvxcv123132");
            str.print();
        }
        {
            MyCollection<int, std::vector> vecCol1;
            vecCol1.add(5);
            vecCol1.add(6);
            vecCol1.print();
            // 使用 list 作为底层容器
            MyCollection<int, std::list> listColl;
            listColl.add(3);
            listColl.add(4);
            listColl.print(); // 输出 3 4
        }
        {
            std::cout << getDefaultValue<int>() << std::endl;    // 输出 0
            std::cout << getDefaultValue<double>() << std::endl; // 输出 0
            std::cout << (getDefaultValue<int*>() == nullptr) << std::endl; // 输出 1（true）
        }
        {
            printString("xzvc");
            printString("xzvcsaasfdasf");
        }
        {
            int arr1[5] = {1,2,3,4,5};
            printAnyArray(arr1);
            string sarr[2] = {"apple", "banana"};
            printAnyArray(sarr);
            char str[6] = "hello";
            printAnyArray(str);

            int arr2D[3][4] = {{1,2,3,4}, {5,6,7,8}, {9,10,11,12}};
            printAnyArray(arr2D); 
        }

        {
            int* ptr = nullptr;
            allocateInt(ptr);
            std::cout << *ptr <<std::endl;
        }
    }
}
